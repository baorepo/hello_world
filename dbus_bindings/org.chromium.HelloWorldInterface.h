// Automatic generation of D-Bus interfaces:
//  - org.chromium.HelloWorldInterface
#ifndef ____CHROMEOS_DBUS_BINDING__ORG_CHROMIUM_HELLOWORLDINTERFACE_H
#define ____CHROMEOS_DBUS_BINDING__ORG_CHROMIUM_HELLOWORLDINTERFACE_H
#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include <base/files/scoped_file.h>
#include <base/macros.h>
#include <dbus/object_path.h>
#include <brillo/any.h>
#include <brillo/dbus/dbus_object.h>
#include <brillo/dbus/exported_object_manager.h>
#include <brillo/dbus/file_descriptor.h>
#include <brillo/variant_dictionary.h>

namespace org {
namespace chromium {

// Interface definition for org::chromium::HelloWorldInterface.
class HelloWorldInterfaceInterface {
 public:
  virtual ~HelloWorldInterfaceInterface() = default;

  virtual bool AttemptHello(
      brillo::ErrorPtr* error,
      const std::string& in_app_version,
      const std::string& in_omaha_url) = 0;
  virtual bool AttemptHelloWithFlags(
      brillo::ErrorPtr* error,
      const std::string& in_app_version,
      const std::string& in_omaha_url,
      int32_t in_flags) = 0;
  virtual bool AttemptInstall(
      brillo::ErrorPtr* error,
      const std::string& in_dlc_request) = 0;
  virtual bool AttemptRollback(
      brillo::ErrorPtr* error,
      bool in_powerwash) = 0;
  virtual bool CanRollback(
      brillo::ErrorPtr* error,
      bool* out_can_rollback) = 0;
  virtual bool ResetStatus(
      brillo::ErrorPtr* error) = 0;
  virtual bool GetStatus(
      brillo::ErrorPtr* error,
      int64_t* out_last_checked_time,
      double* out_progress,
      std::string* out_current_operation,
      std::string* out_new_version,
      int64_t* out_new_size) = 0;
  virtual bool RebootIfNeeded(
      brillo::ErrorPtr* error) = 0;
  virtual bool SetChannel(
      brillo::ErrorPtr* error,
      const std::string& in_target_channel,
      bool in_is_powerwash_allowed) = 0;
  virtual bool GetChannel(
      brillo::ErrorPtr* error,
      bool in_get_current_channel,
      std::string* out_channel) = 0;
  virtual bool SetCohortHint(
      brillo::ErrorPtr* error,
      const std::string& in_cohort_hint) = 0;
  virtual bool GetCohortHint(
      brillo::ErrorPtr* error,
      std::string* out_cohort_hint) = 0;
  virtual bool SetP2PHelloPermission(
      brillo::ErrorPtr* error,
      bool in_enabled) = 0;
  virtual bool GetP2PHelloPermission(
      brillo::ErrorPtr* error,
      bool* out_enabled) = 0;
  virtual bool SetHelloOverCellularPermission(
      brillo::ErrorPtr* error,
      bool in_allowed) = 0;
  virtual bool SetHelloOverCellularTarget(
      brillo::ErrorPtr* error,
      const std::string& in_target_version,
      int64_t in_target_size) = 0;
  virtual bool GetHelloOverCellularPermission(
      brillo::ErrorPtr* error,
      bool* out_allowed) = 0;
  virtual bool GetDurationSinceHello(
      brillo::ErrorPtr* error,
      int64_t* out_usec_wallclock) = 0;
  virtual bool GetPrevVersion(
      brillo::ErrorPtr* error,
      std::string* out_prev_version) = 0;
  virtual bool GetRollbackPartition(
      brillo::ErrorPtr* error,
      std::string* out_rollback_partition_name) = 0;
  virtual bool GetLastAttemptError(
      brillo::ErrorPtr* error,
      int32_t* out_last_attempt_error) = 0;
  virtual bool GetEolStatus(
      brillo::ErrorPtr* error,
      int32_t* out_eol_status) = 0;
};

// Interface adaptor for org::chromium::HelloWorldInterface.
class HelloWorldInterfaceAdaptor {
 public:
  HelloWorldInterfaceAdaptor(HelloWorldInterfaceInterface* interface) : interface_(interface) {}

  void RegisterWithDBusObject(brillo::dbus_utils::DBusObject* object) {
    brillo::dbus_utils::DBusInterface* itf =
        object->AddOrGetInterface("org.chromium.HelloWorldInterface");

    itf->AddSimpleMethodHandlerWithError(
        "AttemptHello",
        base::Unretained(interface_),
        &HelloWorldInterfaceInterface::AttemptHello);
    itf->AddSimpleMethodHandlerWithError(
        "AttemptHelloWithFlags",
        base::Unretained(interface_),
        &HelloWorldInterfaceInterface::AttemptHelloWithFlags);
    itf->AddSimpleMethodHandlerWithError(
        "AttemptInstall",
        base::Unretained(interface_),
        &HelloWorldInterfaceInterface::AttemptInstall);
    itf->AddSimpleMethodHandlerWithError(
        "AttemptRollback",
        base::Unretained(interface_),
        &HelloWorldInterfaceInterface::AttemptRollback);
    itf->AddSimpleMethodHandlerWithError(
        "CanRollback",
        base::Unretained(interface_),
        &HelloWorldInterfaceInterface::CanRollback);
    itf->AddSimpleMethodHandlerWithError(
        "ResetStatus",
        base::Unretained(interface_),
        &HelloWorldInterfaceInterface::ResetStatus);
    itf->AddSimpleMethodHandlerWithError(
        "GetStatus",
        base::Unretained(interface_),
        &HelloWorldInterfaceInterface::GetStatus);
    itf->AddSimpleMethodHandlerWithError(
        "RebootIfNeeded",
        base::Unretained(interface_),
        &HelloWorldInterfaceInterface::RebootIfNeeded);
    itf->AddSimpleMethodHandlerWithError(
        "SetChannel",
        base::Unretained(interface_),
        &HelloWorldInterfaceInterface::SetChannel);
    itf->AddSimpleMethodHandlerWithError(
        "GetChannel",
        base::Unretained(interface_),
        &HelloWorldInterfaceInterface::GetChannel);
    itf->AddSimpleMethodHandlerWithError(
        "SetCohortHint",
        base::Unretained(interface_),
        &HelloWorldInterfaceInterface::SetCohortHint);
    itf->AddSimpleMethodHandlerWithError(
        "GetCohortHint",
        base::Unretained(interface_),
        &HelloWorldInterfaceInterface::GetCohortHint);
    itf->AddSimpleMethodHandlerWithError(
        "SetP2PHelloPermission",
        base::Unretained(interface_),
        &HelloWorldInterfaceInterface::SetP2PHelloPermission);
    itf->AddSimpleMethodHandlerWithError(
        "GetP2PHelloPermission",
        base::Unretained(interface_),
        &HelloWorldInterfaceInterface::GetP2PHelloPermission);
    itf->AddSimpleMethodHandlerWithError(
        "SetHelloOverCellularPermission",
        base::Unretained(interface_),
        &HelloWorldInterfaceInterface::SetHelloOverCellularPermission);
    itf->AddSimpleMethodHandlerWithError(
        "SetHelloOverCellularTarget",
        base::Unretained(interface_),
        &HelloWorldInterfaceInterface::SetHelloOverCellularTarget);
    itf->AddSimpleMethodHandlerWithError(
        "GetHelloOverCellularPermission",
        base::Unretained(interface_),
        &HelloWorldInterfaceInterface::GetHelloOverCellularPermission);
    itf->AddSimpleMethodHandlerWithError(
        "GetDurationSinceHello",
        base::Unretained(interface_),
        &HelloWorldInterfaceInterface::GetDurationSinceHello);
    itf->AddSimpleMethodHandlerWithError(
        "GetPrevVersion",
        base::Unretained(interface_),
        &HelloWorldInterfaceInterface::GetPrevVersion);
    itf->AddSimpleMethodHandlerWithError(
        "GetRollbackPartition",
        base::Unretained(interface_),
        &HelloWorldInterfaceInterface::GetRollbackPartition);
    itf->AddSimpleMethodHandlerWithError(
        "GetLastAttemptError",
        base::Unretained(interface_),
        &HelloWorldInterfaceInterface::GetLastAttemptError);
    itf->AddSimpleMethodHandlerWithError(
        "GetEolStatus",
        base::Unretained(interface_),
        &HelloWorldInterfaceInterface::GetEolStatus);

    signal_StatusHello_ = itf->RegisterSignalOfType<SignalStatusHelloType>("StatusHello");
  }

  void SendStatusHelloSignal(
      int64_t in_last_checked_time,
      double in_progress,
      const std::string& in_current_operation,
      const std::string& in_new_version,
      int64_t in_new_size) {
    auto signal = signal_StatusHello_.lock();
    if (signal)
      signal->Send(in_last_checked_time, in_progress, in_current_operation, in_new_version, in_new_size);
  }

  static dbus::ObjectPath GetObjectPath() {
    return dbus::ObjectPath{"/org/chromium/HelloWorld"};
  }

 private:
  using SignalStatusHelloType = brillo::dbus_utils::DBusSignal<
      int64_t /*last_checked_time*/,
      double /*progress*/,
      std::string /*current_operation*/,
      std::string /*new_version*/,
      int64_t /*new_size*/>;
  std::weak_ptr<SignalStatusHelloType> signal_StatusHello_;

  HelloWorldInterfaceInterface* interface_;  // Owned by container of this adapter.

  DISALLOW_COPY_AND_ASSIGN(HelloWorldInterfaceAdaptor);
};

}  // namespace chromium
}  // namespace org
#endif  // ____CHROMEOS_DBUS_BINDING__ORG_CHROMIUM_HELLOWORLDINTERFACE_H
