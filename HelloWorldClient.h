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

#ifndef HELLO_WORLD_CLIENT_LIBRARY_INCLUDE_HELLO_WORLD_CLIENT_H_
#define HELLO_WORLD_CLIENT_LIBRARY_INCLUDE_HELLO_WORLD_CLIENT_H_

#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include <brillo/enum_flags.h>
#include "HelloWorld_Status.h"

namespace hello_world {

class HelloWorldClient {
 public:
  static std::unique_ptr<HelloWorldClient> CreateInstance();

  virtual ~HelloWorldClient() = default;

  // Force the hello_world to attempt an update.
  // |app_version|
  //     Attempt to update to this version.  An empty string indicates that
  //     update engine should pick the most recent image on the current channel.
  // |omaha_url|
  //     Force hello_world to look for updates from the given server.  Passing
  //     empty indicates hello_world should get this parameter from its
  //     config.  Note that hello_world will ignore this parameter in
  //     production mode to avoid pulling untrusted updates.
  // |at_user_request|
  //     This update was directly requested by the user.
  virtual bool AttemptHello(const std::string& app_version,
                             const std::string& omaha_url,
                             bool at_user_request) = 0;

  // Request the hello_world to install a list of DLC.
  // |omaha_url|
  //     Force hello_world to look for updates from the given server. Passing
  //     empty indicates hello_world should use its default value. Note that
  //     hello_world will ignore this parameter in production mode to avoid
  //     pulling untrusted updates.
  // |dlc_ids|
  //     A vector of DLC IDs.
  virtual bool AttemptInstall(const std::string& omaha_url,
                              const std::vector<std::string>& dlc_ids) = 0;

  // Returns the current status of the Hello Engine.
  //
  // |out_last_checked_time|
  //     the last time the update engine checked for an update in seconds since
  //     the epoc.
  // |out_progress|
  //     when downloading an update, this is calculated as
  //     (number of bytes received) / (total bytes).
  // |out_update_status|
  //     See update_status.h.
  // |out_new_version|
  //     string version of the new system image.
  // |out_new_size|
  //     number of bytes in the new system image.
  virtual bool GetStatus(int64_t* out_last_checked_time,
                         double* out_progress,
                         HelloStatus* out_update_status,
                         std::string* out_new_version,
                         int64_t* out_new_size) const = 0;

  // Getter and setter for the cohort hint.
  virtual bool SetCohortHint(const std::string& cohort_hint) = 0;
  virtual bool GetCohortHint(std::string* cohort_hint) const = 0;

  // Getter and setter for the updates over cellular connections.
  virtual bool SetHelloOverCellularPermission(bool allowed) = 0;
  virtual bool GetHelloOverCellularPermission(bool* allowed) const = 0;

  // Getter and setter for the updates from P2P permission.
  virtual bool SetP2PHelloPermission(bool enabled) = 0;
  virtual bool GetP2PHelloPermission(bool* enabled) const = 0;

  // Attempt a rollback. Set 'powerwash' to reset the device while rolling
  // back.
  virtual bool Rollback(bool powerwash) = 0;

  // Get the rollback partition if available. Gives empty string if not.
  virtual bool GetRollbackPartition(std::string* rollback_partition) const = 0;

  // Reboot the system if needed.
  virtual void RebootIfNeeded() = 0;

  // Get the previous version
  virtual bool GetPrevVersion(std::string* prev_version) const = 0;

  // Resets the status of the Hello Engine
  virtual bool ResetStatus() = 0;

  // Changes the current channel of the device to the target channel.
  virtual bool SetTargetChannel(const std::string& target_channel,
                                bool allow_powerwash) = 0;

  // Get the channel the device will switch to on reboot.
  virtual bool GetTargetChannel(std::string* out_channel) const = 0;

  // Get the channel the device is currently on.
  virtual bool GetChannel(std::string* out_channel) const = 0;

  // Handle status updates. The handler must exist until the client is
  // destroyed or UnregisterStatusHelloHandler is called for it. Its IPCError
  // method will be called if the handler could not be registered. Otherwise
  // its HandleStatusHello method will be called every time hello_world's
  // status changes. Will always report the status on registration to prevent
  // race conditions.
  virtual bool RegisterStatusHelloHandler(StatusHelloHandler* handler) = 0;

  // Unregister a status update handler
  virtual bool UnregisterStatusHelloHandler(StatusHelloHandler* handler) = 0;

  // Get the last HelloAttempt error code.
  virtual bool GetLastAttemptError(int32_t* last_attempt_error) const = 0;

  // Get the current end-of-life status code. See EolStatus enum for details.
  virtual bool GetEolStatus(int32_t* eol_status) const = 0;

 protected:
  // Use CreateInstance().
  HelloWorldClient() = default;

 private:
  HelloWorldClient(const HelloWorldClient&) = delete;
  void operator=(const HelloWorldClient&) = delete;
};  // class HelloWorldClient


}  // namespace hello_world

#endif  // HELLO_WORLD_CLIENT_LIBRARY_INCLUDE_HELLO_WORLD_CLIENT_H_
