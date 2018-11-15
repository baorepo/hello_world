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

#ifndef HELLO_WORLD_CLIENT_LIBRARY_CLIENT_DBUS_H_
#define HELLO_WORLD_CLIENT_LIBRARY_CLIENT_DBUS_H_

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <base/macros.h>

#include "HelloWorldClient.h"
#include "dbus_bindings/dbus-proxies.h"
#include "HelloWorldClient.h"
namespace hello_world {
namespace internal {

const char* HelloStatusToString(const HelloStatus& status);

bool StringToHelloStatus(const std::string& hello_status_as_string,
                          HelloStatus* status);

class DBusHelloWorldClient : public HelloWorldClient {
 public:
  DBusHelloWorldClient() = default;
  bool Init();

  virtual ~DBusHelloWorldClient() = default;

  bool AttemptHello(const std::string& app_version,
                     const std::string& omaha_url,
                     bool at_user_request) override;

  bool AttemptInstall(const std::string& omaha_url,
                      const std::vector<std::string>& dlc_ids) override;

  bool GetStatus(int64_t* out_last_checked_time,
                 double* out_progress,
                 HelloStatus* out_update_status,
                 std::string* out_new_version,
                 int64_t* out_new_size) const override;

  bool SetCohortHint(const std::string& cohort_hint) override;
  bool GetCohortHint(std::string* cohort_hint) const override;

  bool SetHelloOverCellularPermission(bool allowed) override;
  bool GetHelloOverCellularPermission(bool* allowed) const override;

  bool SetP2PHelloPermission(bool enabled) override;
  bool GetP2PHelloPermission(bool* enabled) const override;

  bool Rollback(bool powerwash) override;

  bool GetRollbackPartition(std::string* rollback_partition) const override;

  void RebootIfNeeded() override;

  bool GetPrevVersion(std::string* prev_version) const override;

  bool ResetStatus() override;

  bool SetTargetChannel(const std::string& target_channel,
                        bool allow_powerwash) override;

  bool GetTargetChannel(std::string* out_channel) const override;

  bool GetChannel(std::string* out_channel) const override;

  bool RegisterStatusHelloHandler(StatusHelloHandler* handler) override;
  bool UnregisterStatusHelloHandler(StatusHelloHandler* handler) override;

  bool GetLastAttemptError(int32_t* last_attempt_error) const override;

  bool GetEolStatus(int32_t* eol_status) const override;

 private:
  void DBusStatusHandlersRegistered(const std::string& interface,
                                    const std::string& signal_name,
                                    bool success) const;

  // Send an initial event to new StatusHelloHandlers. If the handler argument
  // is not nullptr, only that handler receives the event. Otherwise all
  // registered handlers receive the event.
  void StatusHelloHandlersRegistered(StatusHelloHandler* handler) const;

  void RunStatusHelloHandlers(int64_t last_checked_time,
                               double progress,
                               const std::string& current_operation,
                               const std::string& new_version,
                               int64_t new_size);

  std::unique_ptr<org::chromium::HelloWorldInterfaceProxy> proxy_;
  std::vector<StatusHelloHandler*> handlers_;
  bool dbus_handler_registered_{false};

  DISALLOW_COPY_AND_ASSIGN(DBusHelloWorldClient);
};  // class DBusHelloWorldClient

}  // namespace internal
}  // namespace hello_world

#endif  // HELLO_WORLD_CLIENT_LIBRARY_CLIENT_DBUS_H_