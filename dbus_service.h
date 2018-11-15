//
// Copyright (C) 2010 The Android Open Source Project
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

#ifndef HELLO_WORLD_DBUS_SERVICE_H_
#define HELLO_WORLD_DBUS_SERVICE_H_

#include <inttypes.h>

#include <memory>
#include <string>

#include <base/memory/ref_counted.h>
#include <brillo/errors/error.h>


#include "dbus_bindings/org.chromium.HelloWorldInterface.h"

namespace chromeos_hello_world {

class DBusHelloWorldService
    : public org::chromium::HelloWorldInterfaceInterface {
 public:
  explicit DBusHelloWorldService();
  virtual ~DBusHelloWorldService() = default;

  // Implementation of org::chromium::HelloWorldInterfaceInterface.
  bool AttemptHello(brillo::ErrorPtr* error,
                     const std::string& in_app_version,
                     const std::string& in_omaha_url) override;

  bool AttemptHelloWithFlags(brillo::ErrorPtr* error,
                              const std::string& in_app_version,
                              const std::string& in_omaha_url,
                              int32_t in_flags_as_int) override;

  bool AttemptInstall(brillo::ErrorPtr* error,
                      const std::string& dlc_request) override;

  bool AttemptRollback(brillo::ErrorPtr* error, bool in_powerwash) override;

  // Checks if the system rollback is available by verifying if the secondary
  // system partition is valid and bootable.
  bool CanRollback(brillo::ErrorPtr* error, bool* out_can_rollback) override;

  // Resets the status of the hello_world to idle, ignoring any applied
  // Hello. This is used for development only.
  bool ResetStatus(brillo::ErrorPtr* error) override;

  // Returns the current status of the Hello Engine. If an Hello is in
  // progress, the number of operations, size to download and overall progress
  // is reported.
  bool GetStatus(brillo::ErrorPtr* error,
                 int64_t* out_last_checked_time,
                 double* out_progress,
                 std::string* out_current_operation,
                 std::string* out_new_version,
                 int64_t* out_new_size) override;

  // Reboots the device if an Hello is applied and a reboot is required.
  bool RebootIfNeeded(brillo::ErrorPtr* error) override;

  // Changes the current channel of the device to the target channel. If the
  // target channel is a less stable channel than the current channel, then the
  // channel change happens immediately (at the next Hello check).  If the
  // target channel is a more stable channel, then if is_powerwash_allowed is
  // set to true, then also the change happens immediately but with a powerwash
  // if required. Otherwise, the change takes effect eventually (when the
  // version on the target channel goes above the version number of what the
  // device currently has).
  bool SetChannel(brillo::ErrorPtr* error,
                  const std::string& in_target_channel,
                  bool in_is_powerwash_allowed) override;

  // If get_current_channel is set to true, populates |channel| with the name of
  // the channel that the device is currently on. Otherwise, it populates it
  // with the name of the channel the device is supposed to be (in case of a
  // pending channel change).
  bool GetChannel(brillo::ErrorPtr* error,
                  bool in_get_current_channel,
                  std::string* out_channel) override;

  bool SetCohortHint(brillo::ErrorPtr* error,
                     const std::string& in_cohort_hint) override;

  bool GetCohortHint(brillo::ErrorPtr* error,
                     std::string* out_cohort_hint) override;

  // Enables or disables the sharing and consuming Hellos over P2P feature
  // according to the |enabled| argument passed.
  bool SetP2PHelloPermission(brillo::ErrorPtr* error,
                              bool in_enabled) override;

  // Returns the current value for the P2P enabled setting. This involves both
  // sharing and consuming Hellos over P2P.
  bool GetP2PHelloPermission(brillo::ErrorPtr* error,
                              bool* out_enabled) override;

  // If there's no device policy installed, sets the Hello over cellular
  // networks permission to the |allowed| value. Otherwise, this method returns
  // with an error since this setting is overridden by the applied policy.
  bool SetHelloOverCellularPermission(brillo::ErrorPtr* error,
                                       bool in_allowed) override;

  // If there's no device policy installed, sets the Hello over cellular
  // target. Otherwise, this method returns with an error.
  bool SetHelloOverCellularTarget(brillo::ErrorPtr* error,
                                   const std::string& target_version,
                                   int64_t target_size) override;

  // Returns the current value of the Hello over cellular network setting,
  // either forced by the device policy if the device is enrolled or the current
  // user preference otherwise.
  bool GetHelloOverCellularPermission(brillo::ErrorPtr* error,
                                       bool* out_allowed) override;

  // Returns the duration since the last successful Hello, as the
  // duration on the wallclock. Returns an error if the device has not
  // Hellod.
  bool GetDurationSinceHello(brillo::ErrorPtr* error,
                              int64_t* out_usec_wallclock) override;

  // Returns the version string of OS that was used before the last reboot
  // into an Hellod version. This is available only when rebooting into an
  // Hello from previous version, otherwise an empty string is returned.
  bool GetPrevVersion(brillo::ErrorPtr* error,
                      std::string* out_prev_version) override;

  // Returns the name of kernel partition that can be rolled back into.
  bool GetRollbackPartition(brillo::ErrorPtr* error,
                            std::string* out_rollback_partition_name) override;

  // Returns the last HelloAttempt error. If not Hellod yet, default success
  // ErrorCode will be returned.
  bool GetLastAttemptError(brillo::ErrorPtr* error,
                           int32_t* out_last_attempt_error) override;

  // Returns the current end-of-life status of the device in |out_eol_status|.
  bool GetEolStatus(brillo::ErrorPtr* error, int32_t* out_eol_status) override;

};

// The HelloWorldAdaptor class runs the HelloWorldInterface in the fixed
// object path, without an ObjectManager notifying the interfaces, since it is
// all static and clients don't expect it to be implemented.
class HelloWorldAdaptor : public org::chromium::HelloWorldInterfaceAdaptor {
 public:
  explicit HelloWorldAdaptor();
  ~HelloWorldAdaptor() = default;

  // Register the DBus object with the Hello engine service asynchronously.
  // Calls |copmletion_callback| when done passing a boolean indicating if the
  // registration succeeded.
  void RegisterAsync(const base::Callback<void(bool)>& completion_callback);

  // Takes ownership of the well-known DBus name and returns whether it
  // succeeded.
  bool RequestOwnership();

  // ServiceObserverInterface overrides.
  void SendStatusHello(
      const std::string &status) ;

  void SendPayloadApplicationComplete(int error_code)  {}

 private:
  scoped_refptr<dbus::Bus> bus_;
  DBusHelloWorldService dbus_service_;
  brillo::dbus_utils::DBusObject dbus_object_;
};

}  // namespace chromeos_hello_world

#endif  // HELLO_WORLD_DBUS_SERVICE_H_
