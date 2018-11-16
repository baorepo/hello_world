
#ifndef HELLO_WORLD_STATUS_DBUS_H_
#define HELLO_WORLD_STATUS_DBUS_H_
#include <brillo/enum_flags.h>

namespace hello_world {
// The end-of-life status of the device.
enum class EolStatus {
  kSupported = 0,
  kSecurityOnly,
  kEol,
};
// ATTENTION: When adding a new enum value here, always append at the end and
// make sure to make proper adjustments in HelloAttempter:ActionCompleted(). If
// any enum memeber is deprecated, the assigned value of other members should
// not change. See b/62842358.
enum class HelloStatus {
  IDLE = 0,
  CHECKING_FOR_UPDATE = 1,
  UPDATE_AVAILABLE = 2,
  DOWNLOADING = 3,
  VERIFYING = 4,
  FINALIZING = 5,
  UPDATED_NEED_REBOOT = 6,
  REPORTING_ERROR_EVENT = 7,
  ATTEMPTING_ROLLBACK = 8,
  DISABLED = 9,
  // Broadcast this state when an update aborts because user preferences do not
  // allow updates, e.g. over cellular network.
  NEED_PERMISSION_TO_UPDATE = 10,
};

// Enum of bit-wise flags for controlling how updates are attempted.
enum HelloAttemptFlags : int32_t {
  kNone = 0,
  // Treat the update like a non-interactive update, even when being triggered
  // by the interactive APIs.
  kFlagNonInteractive = (1 << 0),
  // Restrict (disallow) downloading of updates.
  kFlagRestrictDownload = (1 << 1),
};

// Enable bit-wise operators for the above enumeration of flag values.
DECLARE_FLAGS_ENUM(HelloAttemptFlags);

struct HelloWorldStatus {
  // When the hello_world last checked for updates (time_t: seconds from unix
  // epoch)
  int64_t last_checked_time;
  // the current status/operation of the hello_world
  HelloStatus status;
  // the current product version (oem bundle id)
  std::string current_version;
  // the current system version
  std::string current_system_version;
  // The current progress (0.0f-1.0f).
  double progress;
  // the size of the update (bytes)
  uint64_t new_size_bytes;
  // the new product version
  std::string new_version;
  // the new system version, if there is one (empty, otherwise)
  std::string new_system_version;
};


// Handles hello_world status changes. An instance of this class can be
// registered with HelloWorldClient and will respond to any hello_world
// status changes.
class StatusHelloHandler {
 public:
  virtual ~StatusHelloHandler() = default;

  // Runs when we fail to register the handler due to an IPC error.
  virtual void IPCError(const std::string& error) = 0;

  // Runs every time hello_world reports a status change.
  virtual void HandleStatusHello(int64_t last_checked_time,
                                  double progress,
                                  HelloStatus current_operation,
                                  const std::string& new_version,
                                  int64_t new_size) = 0;
};
}
#endif //HELLO_WORLD_STATUS_DBUS_H_