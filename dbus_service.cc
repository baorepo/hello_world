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

#include "hello_world/dbus_service.h"

#include <string>
#include <vector>

#include <dbus_bindings/dbus-constants.h>
#include <hello_world/proto_bindings/hello_world.pb.h>

#include "dbus_bindings/dbus_connection.h"

namespace chromeos_hello_world {

using brillo::ErrorPtr;
using chromeos_hello_world::DBusHelloWorldService;
using std::string;
using std::vector;

DBusHelloWorldService::DBusHelloWorldService(){
}

// org::chromium::HelloWorldInterfaceInterface methods implementation.

bool DBusHelloWorldService::AttemptHello(ErrorPtr* error,
                                            const string& in_app_version,
                                            const string& in_omaha_url) {
    return EX_OK;
}

bool DBusHelloWorldService::AttemptHelloWithFlags(
        ErrorPtr* error,
        const string& in_app_version,
        const string& in_omaha_url,
        int32_t in_flags_as_int) {
    return EX_OK;
}

bool DBusHelloWorldService::AttemptInstall(ErrorPtr* error,
                                             const string& dlc_request) {
    return EX_OK;
}

bool DBusHelloWorldService::AttemptRollback(ErrorPtr* error,
                                              bool in_powerwash) {
  return EX_OK;
}

bool DBusHelloWorldService::CanRollback(ErrorPtr* error,
                                          bool* out_can_rollback) {
  return EX_OK;
}

bool DBusHelloWorldService::ResetStatus(ErrorPtr* error) {
  return EX_OK;
}

bool DBusHelloWorldService::GetStatus(ErrorPtr* error,
                                        int64_t* out_last_checked_time,
                                        double* out_progress,
                                        string* out_current_operation,
                                        string* out_new_version,
                                        int64_t* out_new_size) {
    return EX_OK;
}

bool DBusHelloWorldService::RebootIfNeeded(ErrorPtr* error) {
  return EX_OK;
}

bool DBusHelloWorldService::SetChannel(ErrorPtr* error,
                                         const string& in_target_channel,
                                         bool in_is_powerwash_allowed) {
  return EX_OK;
}

bool DBusHelloWorldService::GetChannel(ErrorPtr* error,
                                         bool in_get_current_channel,
                                         string* out_channel) {
  return EX_OK;
}

bool DBusHelloWorldService::GetCohortHint(ErrorPtr* error,
                                            string* out_cohort_hint) {
  return EX_OK;
}

bool DBusHelloWorldService::SetCohortHint(ErrorPtr* error,
                                            const string& in_cohort_hint) {
  return EX_OK;
}

bool DBusHelloWorldService::SetP2PHelloPermission(ErrorPtr* error,
                                                     bool in_enabled) {
  return EX_OK;
}

bool DBusHelloWorldService::GetP2PHelloPermission(ErrorPtr* error,
                                                     bool* out_enabled) {
  return EX_OK;
}

bool DBusHelloWorldService::SetHelloOverCellularPermission(ErrorPtr* error,
                                                              bool in_allowed) {
  return EX_OK;
}

bool DBusHelloWorldService::SetHelloOverCellularTarget(
    brillo::ErrorPtr* error,
    const std::string& target_version,
    int64_t target_size) {
    return EX_OK;
}

bool DBusHelloWorldService::GetHelloOverCellularPermission(
    ErrorPtr* error, bool* out_allowed) {
    return EX_OK;
}

bool DBusHelloWorldService::GetDurationSinceHello(
    ErrorPtr* error, int64_t* out_usec_wallclock) {
  return EX_OK;
}

bool DBusHelloWorldService::GetPrevVersion(ErrorPtr* error,
                                             string* out_prev_version) {
  return EX_OK;
}

bool DBusHelloWorldService::GetRollbackPartition(
    ErrorPtr* error, string* out_rollback_partition_name) {
  return EX_OK;
}

bool DBusHelloWorldService::GetLastAttemptError(
    ErrorPtr* error, int32_t* out_last_attempt_error) {
  return EX_OK;
}

bool DBusHelloWorldService::GetEolStatus(ErrorPtr* error,
                                           int32_t* out_eol_status) {
  return EX_OK;
}

HelloWorldAdaptor::HelloWorldAdaptor()
    : org::chromium::HelloWorldInterfaceAdaptor(&dbus_service_),
      bus_(DBusConnection::Get()->GetDBus()),
      dbus_object_(nullptr,
                   bus_,
                   dbus::ObjectPath(hello_world::kHelloWorldServicePath)) {}

void HelloWorldAdaptor::RegisterAsync(
    const base::Callback<void(bool)>& completion_callback) {
  RegisterWithDBusObject(&dbus_object_);
  dbus_object_.RegisterAsync(completion_callback);
}

bool HelloWorldAdaptor::RequestOwnership() {
  return bus_->RequestOwnershipAndBlock(hello_world::kHelloWorldServiceName,
                                        dbus::Bus::REQUIRE_PRIMARY);
}

void HelloWorldAdaptor::SendStatusHello(
    const std::string &status) {

}

}  // namespace chromeos_hello_world
