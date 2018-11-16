//
// Copyright (C) 2015 The Android Open Source Project
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

#include "HelloWorldClient_impl.h"

#include <base/message_loop/message_loop.h>

#include <dbus/bus.h>
#include <dbus_bindings/dbus-constants.h>
#include <proto_bindings/hello_world.pb.h>


using dbus::Bus;
using org::chromium::HelloWorldInterfaceProxy;
using std::string;
using std::vector;

namespace hello_world {
namespace internal {

const char* HelloStatusToString(const HelloStatus& status) {
  switch (status) {
    case HelloStatus::IDLE:
      return hello_world::kHelloStatusIdle;
    case HelloStatus::CHECKING_FOR_UPDATE:
      return hello_world::kHelloStatusCheckingForHello;
    case HelloStatus::UPDATE_AVAILABLE:
      return hello_world::kHelloStatusHelloAvailable;
    case HelloStatus::NEED_PERMISSION_TO_UPDATE:
      return hello_world::kHelloStatusNeedPermissionToHello;
    case HelloStatus::DOWNLOADING:
      return hello_world::kHelloStatusDownloading;
    case HelloStatus::VERIFYING:
      return hello_world::kHelloStatusVerifying;
    case HelloStatus::FINALIZING:
      return hello_world::kHelloStatusFinalizing;
    case HelloStatus::UPDATED_NEED_REBOOT:
      return hello_world::kHelloStatusHellodNeedReboot;
    case HelloStatus::REPORTING_ERROR_EVENT:
      return hello_world::kHelloStatusReportingErrorEvent;
    case HelloStatus::ATTEMPTING_ROLLBACK:
      return hello_world::kHelloStatusAttemptingRollback;
    case HelloStatus::DISABLED:
      return hello_world::kHelloStatusDisabled;
  }

  NOTREACHED();
  return nullptr;
}

bool StringToHelloStatus(const std::string& s,
                          HelloStatus* status) {
  if (s == hello_world::kHelloStatusIdle) {
    *status = HelloStatus::IDLE;
    return true;
  } else if (s == hello_world::kHelloStatusCheckingForHello) {
    *status = HelloStatus::CHECKING_FOR_UPDATE;
    return true;
  } else if (s == hello_world::kHelloStatusHelloAvailable) {
    *status = HelloStatus::UPDATE_AVAILABLE;
    return true;
  } else if (s == hello_world::kHelloStatusNeedPermissionToHello) {
    *status = HelloStatus::NEED_PERMISSION_TO_UPDATE;
    return true;
  } else if (s == hello_world::kHelloStatusDownloading) {
    *status = HelloStatus::DOWNLOADING;
    return true;
  } else if (s == hello_world::kHelloStatusVerifying) {
    *status = HelloStatus::VERIFYING;
    return true;
  } else if (s == hello_world::kHelloStatusFinalizing) {
    *status = HelloStatus::FINALIZING;
    return true;
  } else if (s == hello_world::kHelloStatusHellodNeedReboot) {
    *status = HelloStatus::UPDATED_NEED_REBOOT;
    return true;
  } else if (s == hello_world::kHelloStatusReportingErrorEvent) {
    *status = HelloStatus::REPORTING_ERROR_EVENT;
    return true;
  } else if (s == hello_world::kHelloStatusAttemptingRollback) {
    *status = HelloStatus::ATTEMPTING_ROLLBACK;
    return true;
  } else if (s == hello_world::kHelloStatusDisabled) {
    *status = HelloStatus::DISABLED;
    return true;
  }
  return false;
}
bool DBusHelloWorldClient::Init() {
  Bus::Options options;
  options.bus_type = Bus::SYSTEM;
  scoped_refptr<Bus> bus{new Bus{options}};

  if (!bus->Connect())
    return false;

  proxy_.reset(new HelloWorldInterfaceProxy({bus},hello_world::kHelloWorldServiceName));
  return true;
}

bool DBusHelloWorldClient::AttemptHello(const string& in_app_version,
                                           const string& in_omaha_url,
                                           bool at_user_request) {
  return proxy_->AttemptHelloWithFlags(
      in_app_version,
      in_omaha_url,
      (at_user_request)
          ? 0
          : HelloAttemptFlags::kFlagNonInteractive,
      nullptr);
}

bool DBusHelloWorldClient::AttemptInstall(const string& omaha_url,
                                            const vector<string>& dlc_ids) {
  // Convert parameters into protobuf.
  chromeos_hello_world::DlcParameters dlc_parameters;
  dlc_parameters.set_omaha_url(omaha_url);
  for (const auto& dlc_id : dlc_ids) {
    chromeos_hello_world::DlcInfo* dlc_info = dlc_parameters.add_dlc_infos();
    dlc_info->set_dlc_id(dlc_id);
  }
  string dlc_request;
  if (dlc_parameters.SerializeToString(&dlc_request)) {
    return proxy_->AttemptInstall(dlc_request, nullptr /* brillo::ErrorPtr* */);
  } else {
    LOG(ERROR) << "Fail to serialize a protobuf to a string.";
    return false;
  }
}

bool DBusHelloWorldClient::GetStatus(int64_t* out_last_checked_time,
                                       double* out_progress,
                                       HelloStatus* out_update_status,
                                       string* out_new_version,
                                       int64_t* out_new_size) const {
  string status_as_string;
  const bool success = proxy_->GetStatus(out_last_checked_time,
                                         out_progress,
                                         &status_as_string,
                                         out_new_version,
                                         out_new_size,
                                         nullptr);
  if (!success) {
    return false;
  }

  return StringToHelloStatus(status_as_string, out_update_status);
}

bool DBusHelloWorldClient::SetCohortHint(const string& cohort_hint) {
  return proxy_->SetCohortHint(cohort_hint, nullptr);
}

bool DBusHelloWorldClient::GetCohortHint(string* cohort_hint) const {
  return proxy_->GetCohortHint(cohort_hint, nullptr);
}

bool DBusHelloWorldClient::SetHelloOverCellularPermission(bool allowed) {
  return proxy_->SetHelloOverCellularPermission(allowed, nullptr);
}

bool DBusHelloWorldClient::GetHelloOverCellularPermission(
    bool* allowed) const {
  return proxy_->GetHelloOverCellularPermission(allowed, nullptr);
}

bool DBusHelloWorldClient::SetP2PHelloPermission(bool enabled) {
  return proxy_->SetP2PHelloPermission(enabled, nullptr);
}

bool DBusHelloWorldClient::GetP2PHelloPermission(bool* enabled) const {
  return proxy_->GetP2PHelloPermission(enabled, nullptr);
}

bool DBusHelloWorldClient::Rollback(bool powerwash) {
  return proxy_->AttemptRollback(powerwash, nullptr);
}

bool DBusHelloWorldClient::GetRollbackPartition(
    string* rollback_partition) const {
  return proxy_->GetRollbackPartition(rollback_partition, nullptr);
}

bool DBusHelloWorldClient::GetPrevVersion(string* prev_version) const {
  return proxy_->GetPrevVersion(prev_version, nullptr);
}

void DBusHelloWorldClient::RebootIfNeeded() {
  bool ret = proxy_->RebootIfNeeded(nullptr);
  if (!ret) {
    // Reboot error code doesn't necessarily mean that a reboot
    // failed. For example, D-Bus may be shutdown before we receive the
    // result.
    LOG(INFO) << "RebootIfNeeded() failure ignored.";
  }
}

bool DBusHelloWorldClient::ResetStatus() {
  return proxy_->ResetStatus(nullptr);
}

void DBusHelloWorldClient::DBusStatusHandlersRegistered(
    const string& interface,
    const string& signal_name,
    bool success) const {
  if (!success) {
    for (auto handler : handlers_) {
      handler->IPCError("Could not connect to" + signal_name +
                        " on " + interface);
    }
  } else {
    StatusHelloHandlersRegistered(nullptr);
  }
}

void DBusHelloWorldClient::StatusHelloHandlersRegistered(
    StatusHelloHandler* handler) const {
  int64_t last_checked_time;
  double progress;
  HelloStatus update_status;
  string new_version;
  int64_t new_size;

  if (!GetStatus(&last_checked_time,
                 &progress,
                 &update_status,
                 &new_version,
                 &new_size)) {
    handler->IPCError("Could not query current status");
    return;
  }

  std::vector<hello_world::StatusHelloHandler*> just_handler = {handler};
  for (auto h : handler ? just_handler : handlers_) {
    h->HandleStatusHello(
        last_checked_time, progress, update_status, new_version, new_size);
  }
}

void DBusHelloWorldClient::RunStatusHelloHandlers(
    int64_t last_checked_time,
    double progress,
    const string& current_operation,
    const string& new_version,
    int64_t new_size) {
  HelloStatus status;
  StringToHelloStatus(current_operation, &status);

  for (auto handler : handlers_) {
    handler->HandleStatusHello(
        last_checked_time, progress, status, new_version, new_size);
  }
}

bool DBusHelloWorldClient::UnregisterStatusHelloHandler(
    StatusHelloHandler* handler) {
  auto it = std::find(handlers_.begin(), handlers_.end(), handler);
  if (it != handlers_.end()) {
    handlers_.erase(it);
    return true;
  }

  return false;
}

bool DBusHelloWorldClient::RegisterStatusHelloHandler(
    StatusHelloHandler* handler) {
  if (!base::MessageLoopForIO::current()) {
    LOG(FATAL) << "Cannot get HelloWorldClient outside of message loop.";
    return false;
  }

  handlers_.push_back(handler);

  if (dbus_handler_registered_) {
    StatusHelloHandlersRegistered(handler);
    return true;
  }

  proxy_->RegisterStatusHelloSignalHandler(
      base::Bind(&DBusHelloWorldClient::RunStatusHelloHandlers,
                 base::Unretained(this)),
      base::Bind(&DBusHelloWorldClient::DBusStatusHandlersRegistered,
                 base::Unretained(this)));

  dbus_handler_registered_ = true;

  return true;
}

bool DBusHelloWorldClient::SetTargetChannel(const string& in_target_channel,
                                              bool allow_powerwash) {
  return proxy_->SetChannel(in_target_channel, allow_powerwash, nullptr);
}

bool DBusHelloWorldClient::GetTargetChannel(string* out_channel) const {
  return proxy_->GetChannel(false,  // Get the target channel.
                            out_channel,
                            nullptr);
}

bool DBusHelloWorldClient::GetChannel(string* out_channel) const {
  return proxy_->GetChannel(true,  // Get the current channel.
                            out_channel,
                            nullptr);
}

bool DBusHelloWorldClient::GetLastAttemptError(
    int32_t* last_attempt_error) const {
  return proxy_->GetLastAttemptError(last_attempt_error, nullptr);
}

bool DBusHelloWorldClient::GetEolStatus(int32_t* eol_status) const {
  return proxy_->GetEolStatus(eol_status, nullptr);
}

}  // namespace internal
}  // namespace hello_world