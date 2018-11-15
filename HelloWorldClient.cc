//
// Copyright (C) 2012 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include <inttypes.h>
#include <sysexits.h>
#include <unistd.h>

#include <memory>
#include <string>
#include <vector>

#include <base/bind.h>
#include <base/command_line.h>
#include <base/logging.h>
#include <base/macros.h>
#include <base/strings/string_split.h>
#include <base/threading/platform_thread.h>
#include <brillo/daemons/daemon.h>
#include <brillo/flag_helper.h>

#include "HelloWorldClient.h"
#include "HelloWorldClient_impl.h"


using std::string;
using std::unique_ptr;
using std::vector;
using hello_world::HelloStatus;
using hello_world::HelloWorldClient;

namespace  {

// Constant to signal that we need to continue running the daemon after
// initialization.
const int kContinueRunning = -1;

// The ShowStatus request will be retried `kShowStatusRetryCount` times at
// `kShowStatusRetryInterval` second intervals on failure.
const int kShowStatusRetryCount = 30;
const int kShowStatusRetryIntervalInSeconds = 2;


class mHelloWorldClient : public brillo::Daemon {
 public:
  mHelloWorldClient(int argc, char** argv) : argc_(argc), argv_(argv) {
  }

  ~mHelloWorldClient() override = default;

 protected:
  int OnInit() override {
    int ret = Daemon::OnInit();
    if (ret != EX_OK) return ret;

    client_ = hello_world::HelloWorldClient::CreateInstance();

    if (!client_) {
      LOG(ERROR) << "HelloWorldService not available.";
      return 1;
    }

    // We can't call QuitWithExitCode from OnInit(), so we delay the execution
    // of the ProcessFlags method after the Daemon initialization is done.
    base::MessageLoop::current()->task_runner()->PostTask(
        FROM_HERE,
        base::Bind(&::mHelloWorldClient::ProcessFlagsAndExit,
                   base::Unretained(this)));
    return EX_OK;
  }

 private:
  // Show the status of the hello engine in stdout.
  bool ShowStatus();

  // Return whether we need to reboot. 0 if reboot is needed, 1 if an error
  // occurred, 2 if no reboot is needed.
  int GetNeedReboot();

  // Main method that parses and triggers all the actions based on the passed
  // flags. Returns the exit code of the program of kContinueRunning if it
  // should not exit.
  int ProcessFlags();

  // Processes the flags and exits the program accordingly.
  void ProcessFlagsAndExit();

  // Copy of argc and argv passed to main().
  int argc_;
  char** argv_;

  // Library-based client
  unique_ptr<hello_world::HelloWorldClient> client_;

  // Pointers to handlers for cleanup
  vector<unique_ptr<hello_world::StatusHelloHandler>> handlers_;

  DISALLOW_COPY_AND_ASSIGN(mHelloWorldClient);
};

class ExitingStatusHelloHandler : public hello_world::StatusHelloHandler {
 public:
  ~ExitingStatusHelloHandler() override = default;

  void IPCError(const string& error) override;
};

void ExitingStatusHelloHandler::IPCError(const string& error) {
  LOG(ERROR) << error;
  exit(1);
}

class WatchingStatusHelloHandler : public ExitingStatusHelloHandler {
 public:
  ~WatchingStatusHelloHandler() override = default;

  void HandleStatusHello(int64_t last_checked_time,
                          double progress,
                          HelloStatus current_operation,
                          const string& new_version,
                          int64_t new_size) override;
};

void WatchingStatusHelloHandler::HandleStatusHello(
    int64_t last_checked_time, double progress, HelloStatus current_operation,
    const string& new_version, int64_t new_size) {
  LOG(INFO) << "Got status hello:";
  LOG(INFO) << "  last_checked_time: " << last_checked_time;
  LOG(INFO) << "  progress: " << progress;
  LOG(INFO) << "  current_operation: "
            << hello_world::internal::HelloStatusToString(current_operation);
  LOG(INFO) << "  new_version: " << new_version;
  LOG(INFO) << "  new_size: " << new_size;
}



bool mHelloWorldClient::ShowStatus() {
  int64_t last_checked_time = 0;
  double progress = 0.0;
  HelloStatus current_op;
  string new_version;
  int64_t new_size = 0;

  int retry_count = kShowStatusRetryCount;
  while (retry_count > 0) {
    if (client_->GetStatus(&last_checked_time, &progress, &current_op,
                           &new_version, &new_size)) {
      break;
    }
    if (--retry_count == 0) {
      return false;
    }
    LOG(WARNING) << "Will try " << retry_count << " more times!";
    base::PlatformThread::Sleep(
        base::TimeDelta::FromSeconds(kShowStatusRetryIntervalInSeconds));
  }

  printf("LAST_CHECKED_TIME=%" PRIi64
         "\nPROGRESS=%f\nCURRENT_OP=%s\n"
         "NEW_VERSION=%s\nNEW_SIZE=%" PRIi64 "\n",
         last_checked_time, progress, hello_world::internal::HelloStatusToString(current_op),
         new_version.c_str(), new_size);

  return true;
}

int mHelloWorldClient::GetNeedReboot() {
  int64_t last_checked_time = 0;
  double progress = 0.0;
  HelloStatus current_op;
  string new_version;
  int64_t new_size = 0;

  if (!client_->GetStatus(&last_checked_time, &progress, &current_op,
                          &new_version, &new_size)) {
    return 1;
  }

  if (current_op == HelloStatus::UPDATED_NEED_REBOOT) {
    return 0;
  }

  return 2;
}

class HelloWaitHandler : public ExitingStatusHelloHandler {
 public:
  explicit HelloWaitHandler(bool exit_on_error,
                             hello_world::HelloWorldClient* client)
      : exit_on_error_(exit_on_error), client_(client) {}

  ~HelloWaitHandler() override = default;

  void HandleStatusHello(int64_t last_checked_time,
                          double progress,
                          HelloStatus current_operation,
                          const string& new_version,
                          int64_t new_size) override;

 private:
  bool exit_on_error_;
  hello_world::HelloWorldClient* client_;
};

void HelloWaitHandler::HandleStatusHello(int64_t /* last_checked_time */,
                                           double /* progress */,
                                           HelloStatus current_operation,
                                           const string& /* new_version */,
                                           int64_t /* new_size */) {
  if (exit_on_error_ && current_operation == HelloStatus::IDLE) {
    int last_attempt_error;

    if (client_)
     client_->GetLastAttemptError(&last_attempt_error);

    LOG(ERROR) << "Hello failed, current operation is "
               << hello_world::internal::HelloStatusToString(current_operation)
               << ", last error code is " << last_attempt_error << "("
               << last_attempt_error << ")";
    exit(1);
  }
  if (current_operation == HelloStatus::UPDATED_NEED_REBOOT) {
    LOG(INFO) << "Hello succeeded -- reboot needed.";
    exit(0);
  }
}

int mHelloWorldClient::ProcessFlags() {
  DEFINE_string(app_version, "", "Force the current app version.");
  DEFINE_string(channel, "",
                "Set the target channel. The device will be powerwashed if the "
                "target channel is more stable than the current channel unless "
                "--nopowerwash is specified.");
  DEFINE_bool(check_for_hello, false, "Initiate check for hellos.");
  DEFINE_string(
      cohort_hint, "", "Set the current cohort hint to the passed value.");
  DEFINE_bool(follow, false,
              "Wait for any hello operations to complete."
              "Exit status is 0 if the hello succeeded, and 1 otherwise.");
  DEFINE_bool(interactive, true, "Mark the hello request as interactive.");
  DEFINE_string(omaha_url, "", "The URL of the Omaha hello server.");
  DEFINE_string(p2p_hello, "",
                "Enables (\"yes\") or disables (\"no\") the peer-to-peer hello"
                " sharing.");
  DEFINE_bool(powerwash, true,
              "When performing rollback or channel change, "
              "do a powerwash or allow it respectively.");
  DEFINE_bool(reboot, false, "Initiate a reboot if needed.");
  DEFINE_bool(is_reboot_needed, false,
              "Exit status 0 if reboot is needed, "
              "2 if reboot is not needed or 1 if an error occurred.");
  DEFINE_bool(block_until_reboot_is_needed, false,
              "Blocks until reboot is "
              "needed. Returns non-zero exit status if an error occurred.");
  DEFINE_bool(reset_status, false, "Sets the status in hello_world to idle.");
  DEFINE_bool(rollback, false,
              "Perform a rollback to the previous partition. The device will "
              "be powerwashed unless --nopowerwash is specified.");
  DEFINE_bool(can_rollback, false,
              "Shows whether rollback partition "
              "is available.");
  DEFINE_bool(show_channel, false, "Show the current and target channels.");
  DEFINE_bool(show_cohort_hint, false, "Show the current cohort hint.");
  DEFINE_bool(show_p2p_hello, false,
              "Show the current setting for peer-to-peer hello sharing.");
  DEFINE_bool(show_hello_over_cellular, false,
              "Show the current setting for hellos over cellular networks.");
  DEFINE_bool(status, false, "Print the status to stdout.");
  DEFINE_bool(hello, false,
              "Forces an hello and waits for it to complete. "
              "Implies --follow.");
  DEFINE_string(hello_over_cellular, "",
                "Enables (\"yes\") or disables (\"no\") the hellos over "
                "cellular networks.");
  DEFINE_bool(watch_for_hellos, false,
              "Listen for status hellos and print them to the screen.");
  DEFINE_bool(prev_version, false,
              "Show the previous OS version used before the hello reboot.");
  DEFINE_bool(last_attempt_error, false, "Show the last attempt error.");
  DEFINE_bool(eol_status, false, "Show the current end-of-life status.");
  DEFINE_bool(install, false, "Requests an install.");
  DEFINE_string(dlc_ids, "", "colon-separated list of DLC IDs.");

  // Boilerplate init commands.
  base::CommandLine::Init(argc_, argv_);
  brillo::FlagHelper::Init(argc_, argv_, "A/B Hello Engine Client");

  // Ensure there are no positional arguments.
  const vector<string> positional_args =
      base::CommandLine::ForCurrentProcess()->GetArgs();
  if (!positional_args.empty()) {
    LOG(ERROR) << "Found a positional argument '" << positional_args.front()
               << "'. If you want to pass a value to a flag, pass it as "
                  "--flag=value.";
    return 1;
  }

  // Hello the status if requested.
  if (FLAGS_reset_status) {
    LOG(INFO) << "Setting Hello Engine status to idle ...";

    if (client_->ResetStatus()) {
      LOG(INFO) << "ResetStatus succeeded; to undo partition table changes "
                   "run:\n"
                   "(D=$(rootdev -d) P=$(rootdev -s); cgpt p -i$(($(echo "
                   "${P#$D} | sed 's/^[^0-9]*//')-1)) $D;)";
    } else {
      LOG(ERROR) << "ResetStatus failed";
      return 1;
    }
  }

  // Changes the current hello over cellular network setting.
  if (!FLAGS_hello_over_cellular.empty()) {
    bool allowed = FLAGS_hello_over_cellular == "yes";
    if (!allowed && FLAGS_hello_over_cellular != "no") {
      LOG(ERROR) << "Unknown option: \"" << FLAGS_hello_over_cellular
                 << "\". Please specify \"yes\" or \"no\".";
    } else {
      if (!client_->SetHelloOverCellularPermission(allowed)) {
        LOG(ERROR) << "Error setting the hello over cellular setting.";
        return 1;
      }
    }
  }

  // Show the current hello over cellular network setting.
  if (FLAGS_show_hello_over_cellular) {
    bool allowed;

    if (!client_->GetHelloOverCellularPermission(&allowed)) {
      LOG(ERROR) << "Error getting the hello over cellular setting.";
      return 1;
    }

    LOG(INFO) << "Current hello over cellular network setting: "
              << (allowed ? "ENABLED" : "DISABLED");
  }

  // Change/show the cohort hint.
  bool set_cohort_hint =
      base::CommandLine::ForCurrentProcess()->HasSwitch("cohort_hint");
  if (set_cohort_hint) {
    LOG(INFO) << "Setting cohort hint to: \"" << FLAGS_cohort_hint << "\"";
    if (!client_->SetCohortHint(FLAGS_cohort_hint)) {
      LOG(ERROR) << "Error setting the cohort hint.";
      return 1;
    }
  }

  if (FLAGS_show_cohort_hint || set_cohort_hint) {
    string cohort_hint;
    if (!client_->GetCohortHint(&cohort_hint)) {
      LOG(ERROR) << "Error getting the cohort hint.";
      return 1;
    }

    LOG(INFO) << "Current cohort hint: \"" << cohort_hint << "\"";
  }

  if (!FLAGS_powerwash && !FLAGS_rollback && FLAGS_channel.empty()) {
    LOG(ERROR) << "powerwash flag only makes sense rollback or channel change";
    return 1;
  }

  // Change the P2P enabled setting.
  if (!FLAGS_p2p_hello.empty()) {
    bool enabled = FLAGS_p2p_hello == "yes";
    if (!enabled && FLAGS_p2p_hello != "no") {
      LOG(ERROR) << "Unknown option: \"" << FLAGS_p2p_hello
                 << "\". Please specify \"yes\" or \"no\".";
    } else {
      if (!client_->SetP2PHelloPermission(enabled)) {
        LOG(ERROR) << "Error setting the peer-to-peer hello setting.";
        return 1;
      }
    }
  }

  // Show the rollback availability.
  if (FLAGS_can_rollback) {
    string rollback_partition;

    if (!client_->GetRollbackPartition(&rollback_partition)) {
      LOG(ERROR) << "Error while querying rollback partition availability.";
      return 1;
    }

    bool can_rollback = true;
    if (rollback_partition.empty()) {
      rollback_partition = "UNAVAILABLE";
      can_rollback = false;
    } else {
      rollback_partition = "AVAILABLE: " + rollback_partition;
    }

    LOG(INFO) << "Rollback partition: " << rollback_partition;
    if (!can_rollback) {
      return 1;
    }
  }

  // Show the current P2P enabled setting.
  if (FLAGS_show_p2p_hello) {
    bool enabled;

    if (!client_->GetP2PHelloPermission(&enabled)) {
      LOG(ERROR) << "Error getting the peer-to-peer hello setting.";
      return 1;
    }

    LOG(INFO) << "Current hello using P2P setting: "
              << (enabled ? "ENABLED" : "DISABLED");
  }

  // First, hello the target channel if requested.
  if (!FLAGS_channel.empty()) {
    if (!client_->SetTargetChannel(FLAGS_channel, FLAGS_powerwash)) {
      LOG(ERROR) << "Error setting the channel.";
      return 1;
    }

    LOG(INFO) << "Channel permanently set to: " << FLAGS_channel;
  }

  // Show the current and target channels if requested.
  if (FLAGS_show_channel) {
    string current_channel;
    string target_channel;

    if (!client_->GetChannel(&current_channel)) {
      LOG(ERROR) << "Error getting the current channel.";
      return 1;
    }

    if (!client_->GetTargetChannel(&target_channel)) {
      LOG(ERROR) << "Error getting the target channel.";
      return 1;
    }

    LOG(INFO) << "Current Channel: " << current_channel;

    if (!target_channel.empty())
      LOG(INFO) << "Target Channel (pending hello): " << target_channel;
  }

  bool do_hello_request = FLAGS_check_for_hello || FLAGS_hello ||
                           !FLAGS_app_version.empty() ||
                           !FLAGS_omaha_url.empty();
  if (FLAGS_hello) FLAGS_follow = true;

  if (do_hello_request && FLAGS_rollback) {
    LOG(ERROR) << "Incompatible flags specified with rollback."
               << "Rollback should not include hello-related flags.";
    return 1;
  }

  if (FLAGS_rollback) {
    LOG(INFO) << "Requesting rollback.";
    if (!client_->Rollback(FLAGS_powerwash)) {
      LOG(ERROR) << "Rollback request failed.";
      return 1;
    }
  }

  if (FLAGS_install) {
    // Parse DLC IDs.
    vector<string> dlc_ids;
    if (!FLAGS_dlc_ids.empty()) {
      dlc_ids = base::SplitString(
          FLAGS_dlc_ids, ":", base::TRIM_WHITESPACE, base::SPLIT_WANT_ALL);
    }
    if (dlc_ids.empty()) {
      LOG(ERROR) << "dlc_ids is empty:" << FLAGS_dlc_ids;
      return 1;
    }
    if (!client_->AttemptInstall(FLAGS_omaha_url, dlc_ids)) {
      LOG(ERROR) << "AttemptInstall failed.";
      return 1;
    }
    return 0;
  } else if (!FLAGS_dlc_ids.empty()) {
    LOG(ERROR) << "dlc_ids is not empty while install is not set:"
               << FLAGS_dlc_ids;
    return 1;
  }

  // Initiate an hello check, if necessary.
  if (do_hello_request) {
    LOG_IF(WARNING, FLAGS_reboot) << "-reboot flag ignored.";
    string app_version = FLAGS_app_version;
    if (FLAGS_hello && app_version.empty()) {
      app_version = "ForcedHello";
      LOG(INFO) << "Forcing an hello by setting app_version to ForcedHello.";
    }
    LOG(INFO) << "Initiating hello check and install.";
    if (!client_->AttemptHello(app_version, FLAGS_omaha_url,
                                FLAGS_interactive)) {
      LOG(ERROR) << "Error checking for hello.";
      return 1;
    }
  }

  // These final options are all mutually exclusive with one another.
  if (FLAGS_follow + FLAGS_watch_for_hellos + FLAGS_reboot + FLAGS_status +
          FLAGS_is_reboot_needed + FLAGS_block_until_reboot_is_needed >
      1) {
    LOG(ERROR) << "Multiple exclusive options selected. "
               << "Select only one of --follow, --watch_for_hellos, --reboot, "
               << "--is_reboot_needed, --block_until_reboot_is_needed, "
               << "or --status.";
    return 1;
  }

  if (FLAGS_status) {
    LOG(INFO) << "Querying Hello Engine status...";
    if (!ShowStatus()) {
      LOG(ERROR) << "Failed to query status";
      return 1;
    }
    return 0;
  }

  if (FLAGS_follow) {
    LOG(INFO) << "Waiting for hello to complete.";
    auto handler = new HelloWaitHandler(true, client_.get());
    handlers_.emplace_back(handler);
    client_->RegisterStatusHelloHandler(handler);
    return kContinueRunning;
  }

  if (FLAGS_watch_for_hellos) {
    LOG(INFO) << "Watching for status hellos.";
    auto handler = new WatchingStatusHelloHandler();
    handlers_.emplace_back(handler);
    client_->RegisterStatusHelloHandler(handler);
    return kContinueRunning;
  }

  if (FLAGS_reboot) {
    LOG(INFO) << "Requesting a reboot...";
    client_->RebootIfNeeded();
    return 0;
  }

  if (FLAGS_prev_version) {
    string prev_version;

    if (!client_->GetPrevVersion(&prev_version)) {
      LOG(ERROR) << "Error getting previous version.";
    } else {
      LOG(INFO) << "Previous version = " << prev_version;
    }
  }

  if (FLAGS_is_reboot_needed) {
    int ret = GetNeedReboot();

    if (ret == 1) {
      LOG(ERROR) << "Could not query the current operation.";
    }

    return ret;
  }

  if (FLAGS_block_until_reboot_is_needed) {
    auto handler = new HelloWaitHandler(false, nullptr);
    handlers_.emplace_back(handler);
    client_->RegisterStatusHelloHandler(handler);
    return kContinueRunning;
  }

  if (FLAGS_last_attempt_error) {
    int last_attempt_error;
    if (!client_->GetLastAttemptError(&last_attempt_error)) {
      LOG(ERROR) << "Error getting last attempt error.";
    } else {
      LOG(ERROR) << "ERROR_CODE=" << last_attempt_error;
    }
  }

  if (FLAGS_eol_status) {
    int eol_status;
    if (!client_->GetEolStatus(&eol_status)) {
      LOG(ERROR) << "Error getting the end-of-life status.";
    } else {
      hello_world::EolStatus eol_status_code = static_cast<hello_world::EolStatus>(eol_status);
      LOG(ERROR) << "EOL_STATUS=" << eol_status_code;
    }
  }

  return 0;
}

void mHelloWorldClient::ProcessFlagsAndExit() {
  int ret = ProcessFlags();
  if (ret != kContinueRunning)
    QuitWithExitCode(ret);
}

}  // namespace

int main(int argc, char** argv) {
  mHelloWorldClient client(argc, argv);
  return client.Run();
}
