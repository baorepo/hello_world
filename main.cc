#include <inttypes.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <algorithm>
#include <string>
#include <vector>

#include <base/at_exit.h>
#include <base/command_line.h>
#include <base/files/dir_reader_posix.h>
#include <base/files/file_util.h>
#include <base/logging.h>
#include <base/strings/string_util.h>
#include <base/strings/stringprintf.h>
#include <brillo/flag_helper.h>
#include "HelloWorldDaemon.h"

using std::string;

constexpr char kSystemLogsRoot[] = "/var/log";

string GetTimeAsString(time_t utime) {
  struct tm tm;
  CHECK_EQ(localtime_r(&utime, &tm), &tm);
  char str[16];
  CHECK_EQ(strftime(str, sizeof(str), "%Y%m%d-%H%M%S", &tm), 15u);
  return str;
}

void SetupLogSymlink(const string& symlink_path, const string& log_path) {

  base::DeleteFile(base::FilePath(symlink_path), true);
  if (symlink(log_path.c_str(), symlink_path.c_str()) == -1) {
    PLOG(ERROR) << "Unable to create symlink " << symlink_path
                << " pointing at " << log_path;
  }
}

string SetupLogFile(const string& kLogsRoot) {
  const string kLogSymlink = kLogsRoot + "/hello_world.log";
  const string kLogsDir = kLogsRoot + "/hello_world";
  const string kLogPath =
      base::StringPrintf("%s/hello_world.%s",
                         kLogsDir.c_str(),
                         GetTimeAsString(::time(nullptr)).c_str());
  mkdir(kLogsDir.c_str(), 0755);
  SetupLogSymlink(kLogSymlink, kLogPath);
  return kLogSymlink;
}

void SetupLogging(bool log_to_system, bool log_to_file) {
  logging::LoggingSettings log_settings;
  log_settings.lock_log = logging::DONT_LOCK_LOG_FILE;
  log_settings.logging_dest = static_cast<logging::LoggingDestination>(
      (log_to_system ? logging::LOG_TO_SYSTEM_DEBUG_LOG : 0) |
      (log_to_file ? logging::LOG_TO_FILE : 0));
  log_settings.log_file = nullptr;

  string log_file;
  if (log_to_file) {
    log_file = SetupLogFile(kSystemLogsRoot);
    log_settings.delete_old = logging::APPEND_TO_OLD_LOG_FILE;
    log_settings.log_file = log_file.c_str();
  }
  logging::InitLogging(log_settings);

}


int main(int argc, char** argv) {
  DEFINE_bool(logtofile, false, "Write logs to a file in log_dir.");
  DEFINE_bool(logtostderr, false,
              "Write logs to stderr instead of to a file in log_dir.");
  DEFINE_bool(foreground, false,
              "Don't daemon()ize; run in foreground.");
  brillo::FlagHelper::Init(argc, argv, "Hello World test");
  // We have two logging flags "--logtostderr" and "--logtofile"; and the logic
  // to choose the logging destination is:
  // 1. --logtostderr --logtofile -> logs to both
  // 2. --logtostderr             -> logs to system debug
  // 3. --logtofile or no flags   -> logs to file
  bool log_to_system = FLAGS_logtostderr;
  bool log_to_file = FLAGS_logtofile || !FLAGS_logtostderr;    
  SetupLogging(log_to_system, log_to_file);

  LOG(INFO) << "Hello World Daemon starting";
  chromeos_hello_world::HelloWorldDaemon hello_world_daemon;
  int exit_code = hello_world_daemon.Run();

  // chromeos_hello_world::Subprocess::Get().FlushBufferedLogsAtExit();

  LOG(INFO) << "Hello World Daemon with exit code " << exit_code;
  return exit_code;
}