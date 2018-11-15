// Automatic generation of D-Bus interfaces:
//  - org.chromium.HelloWorldInterface
#ifndef ____CHROMEOS_DBUS_BINDING__DBUS_PROXIES_H
#define ____CHROMEOS_DBUS_BINDING__DBUS_PROXIES_H
#include <memory>
#include <string>
#include <vector>

#include <base/bind.h>
#include <base/callback.h>
#include <base/files/scoped_file.h>
#include <base/logging.h>
#include <base/macros.h>
#include <base/memory/ref_counted.h>
#include <brillo/any.h>
#include <brillo/dbus/dbus_method_invoker.h>
#include <brillo/dbus/dbus_property.h>
#include <brillo/dbus/dbus_signal_handler.h>
#include <brillo/dbus/file_descriptor.h>
#include <brillo/errors/error.h>
#include <brillo/variant_dictionary.h>
#include <dbus/bus.h>
#include <dbus/message.h>
#include <dbus/object_manager.h>
#include <dbus/object_path.h>
#include <dbus/object_proxy.h>

namespace org {
namespace chromium {

// Abstract interface proxy for org::chromium::HelloWorldInterface.
class HelloWorldInterfaceProxyInterface {
 public:
  virtual ~HelloWorldInterfaceProxyInterface() = default;

  virtual bool AttemptHello(
      const std::string& in_app_version,
      const std::string& in_omaha_url,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual void AttemptHelloAsync(
      const std::string& in_app_version,
      const std::string& in_omaha_url,
      const base::Callback<void()>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual bool AttemptHelloWithFlags(
      const std::string& in_app_version,
      const std::string& in_omaha_url,
      int32_t in_flags,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual void AttemptHelloWithFlagsAsync(
      const std::string& in_app_version,
      const std::string& in_omaha_url,
      int32_t in_flags,
      const base::Callback<void()>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual bool AttemptInstall(
      const std::string& in_dlc_request,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual void AttemptInstallAsync(
      const std::string& in_dlc_request,
      const base::Callback<void()>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual bool AttemptRollback(
      bool in_powerwash,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual void AttemptRollbackAsync(
      bool in_powerwash,
      const base::Callback<void()>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual bool CanRollback(
      bool* out_can_rollback,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual void CanRollbackAsync(
      const base::Callback<void(bool /*can_rollback*/)>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual bool ResetStatus(
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual void ResetStatusAsync(
      const base::Callback<void()>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual bool GetStatus(
      int64_t* out_last_checked_time,
      double* out_progress,
      std::string* out_current_operation,
      std::string* out_new_version,
      int64_t* out_new_size,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual void GetStatusAsync(
      const base::Callback<void(int64_t /*last_checked_time*/, double /*progress*/, const std::string& /*current_operation*/, const std::string& /*new_version*/, int64_t /*new_size*/)>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual bool RebootIfNeeded(
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual void RebootIfNeededAsync(
      const base::Callback<void()>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual bool SetChannel(
      const std::string& in_target_channel,
      bool in_is_powerwash_allowed,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual void SetChannelAsync(
      const std::string& in_target_channel,
      bool in_is_powerwash_allowed,
      const base::Callback<void()>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual bool GetChannel(
      bool in_get_current_channel,
      std::string* out_channel,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual void GetChannelAsync(
      bool in_get_current_channel,
      const base::Callback<void(const std::string& /*channel*/)>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual bool SetCohortHint(
      const std::string& in_cohort_hint,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual void SetCohortHintAsync(
      const std::string& in_cohort_hint,
      const base::Callback<void()>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual bool GetCohortHint(
      std::string* out_cohort_hint,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual void GetCohortHintAsync(
      const base::Callback<void(const std::string& /*cohort_hint*/)>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual bool SetP2PHelloPermission(
      bool in_enabled,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual void SetP2PHelloPermissionAsync(
      bool in_enabled,
      const base::Callback<void()>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual bool GetP2PHelloPermission(
      bool* out_enabled,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual void GetP2PHelloPermissionAsync(
      const base::Callback<void(bool /*enabled*/)>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual bool SetHelloOverCellularPermission(
      bool in_allowed,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual void SetHelloOverCellularPermissionAsync(
      bool in_allowed,
      const base::Callback<void()>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual bool SetHelloOverCellularTarget(
      const std::string& in_target_version,
      int64_t in_target_size,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual void SetHelloOverCellularTargetAsync(
      const std::string& in_target_version,
      int64_t in_target_size,
      const base::Callback<void()>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual bool GetHelloOverCellularPermission(
      bool* out_allowed,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual void GetHelloOverCellularPermissionAsync(
      const base::Callback<void(bool /*allowed*/)>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual bool GetDurationSinceHello(
      int64_t* out_usec_wallclock,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual void GetDurationSinceHelloAsync(
      const base::Callback<void(int64_t /*usec_wallclock*/)>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual bool GetPrevVersion(
      std::string* out_prev_version,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual void GetPrevVersionAsync(
      const base::Callback<void(const std::string& /*prev_version*/)>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual bool GetRollbackPartition(
      std::string* out_rollback_partition_name,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual void GetRollbackPartitionAsync(
      const base::Callback<void(const std::string& /*rollback_partition_name*/)>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual bool GetLastAttemptError(
      int32_t* out_last_attempt_error,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual void GetLastAttemptErrorAsync(
      const base::Callback<void(int32_t /*last_attempt_error*/)>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual bool GetEolStatus(
      int32_t* out_eol_status,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual void GetEolStatusAsync(
      const base::Callback<void(int32_t /*eol_status*/)>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) = 0;

  virtual void RegisterStatusHelloSignalHandler(
      const base::Callback<void(int64_t,
                                double,
                                const std::string&,
                                const std::string&,
                                int64_t)>& signal_callback,
      dbus::ObjectProxy::OnConnectedCallback on_connected_callback) = 0;

  virtual const dbus::ObjectPath& GetObjectPath() const = 0;
  virtual dbus::ObjectProxy* GetObjectProxy() const = 0;
};

}  // namespace chromium
}  // namespace org

namespace org {
namespace chromium {

// Interface proxy for org::chromium::HelloWorldInterface.
class HelloWorldInterfaceProxy final : public HelloWorldInterfaceProxyInterface {
 public:
  HelloWorldInterfaceProxy(
      const scoped_refptr<dbus::Bus>& bus,
      const std::string& service_name) :
          bus_{bus},
          service_name_{service_name},
          dbus_object_proxy_{
              bus_->GetObjectProxy(service_name_, object_path_)} {
  }

  ~HelloWorldInterfaceProxy() override {
  }

  void RegisterStatusHelloSignalHandler(
      const base::Callback<void(int64_t,
                                double,
                                const std::string&,
                                const std::string&,
                                int64_t)>& signal_callback,
      dbus::ObjectProxy::OnConnectedCallback on_connected_callback) override {
    brillo::dbus_utils::ConnectToSignal(
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "StatusHello",
        signal_callback,
        on_connected_callback);
  }

  void ReleaseObjectProxy(const base::Closure& callback) {
    bus_->RemoveObjectProxy(service_name_, object_path_, callback);
  }

  const dbus::ObjectPath& GetObjectPath() const override {
    return object_path_;
  }

  dbus::ObjectProxy* GetObjectProxy() const override {
    return dbus_object_proxy_;
  }

  bool AttemptHello(
      const std::string& in_app_version,
      const std::string& in_omaha_url,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    auto response = brillo::dbus_utils::CallMethodAndBlockWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "AttemptHello",
        error,
        in_app_version,
        in_omaha_url);
    return response && brillo::dbus_utils::ExtractMethodCallResults(
        response.get(), error);
  }

  void AttemptHelloAsync(
      const std::string& in_app_version,
      const std::string& in_omaha_url,
      const base::Callback<void()>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    brillo::dbus_utils::CallMethodWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "AttemptHello",
        success_callback,
        error_callback,
        in_app_version,
        in_omaha_url);
  }

  bool AttemptHelloWithFlags(
      const std::string& in_app_version,
      const std::string& in_omaha_url,
      int32_t in_flags,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    auto response = brillo::dbus_utils::CallMethodAndBlockWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "AttemptHelloWithFlags",
        error,
        in_app_version,
        in_omaha_url,
        in_flags);
    return response && brillo::dbus_utils::ExtractMethodCallResults(
        response.get(), error);
  }

  void AttemptHelloWithFlagsAsync(
      const std::string& in_app_version,
      const std::string& in_omaha_url,
      int32_t in_flags,
      const base::Callback<void()>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    brillo::dbus_utils::CallMethodWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "AttemptHelloWithFlags",
        success_callback,
        error_callback,
        in_app_version,
        in_omaha_url,
        in_flags);
  }

  bool AttemptInstall(
      const std::string& in_dlc_request,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    auto response = brillo::dbus_utils::CallMethodAndBlockWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "AttemptInstall",
        error,
        in_dlc_request);
    return response && brillo::dbus_utils::ExtractMethodCallResults(
        response.get(), error);
  }

  void AttemptInstallAsync(
      const std::string& in_dlc_request,
      const base::Callback<void()>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    brillo::dbus_utils::CallMethodWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "AttemptInstall",
        success_callback,
        error_callback,
        in_dlc_request);
  }

  bool AttemptRollback(
      bool in_powerwash,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    auto response = brillo::dbus_utils::CallMethodAndBlockWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "AttemptRollback",
        error,
        in_powerwash);
    return response && brillo::dbus_utils::ExtractMethodCallResults(
        response.get(), error);
  }

  void AttemptRollbackAsync(
      bool in_powerwash,
      const base::Callback<void()>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    brillo::dbus_utils::CallMethodWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "AttemptRollback",
        success_callback,
        error_callback,
        in_powerwash);
  }

  bool CanRollback(
      bool* out_can_rollback,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    auto response = brillo::dbus_utils::CallMethodAndBlockWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "CanRollback",
        error);
    return response && brillo::dbus_utils::ExtractMethodCallResults(
        response.get(), error, out_can_rollback);
  }

  void CanRollbackAsync(
      const base::Callback<void(bool /*can_rollback*/)>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    brillo::dbus_utils::CallMethodWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "CanRollback",
        success_callback,
        error_callback);
  }

  bool ResetStatus(
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    auto response = brillo::dbus_utils::CallMethodAndBlockWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "ResetStatus",
        error);
    return response && brillo::dbus_utils::ExtractMethodCallResults(
        response.get(), error);
  }

  void ResetStatusAsync(
      const base::Callback<void()>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    brillo::dbus_utils::CallMethodWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "ResetStatus",
        success_callback,
        error_callback);
  }

  bool GetStatus(
      int64_t* out_last_checked_time,
      double* out_progress,
      std::string* out_current_operation,
      std::string* out_new_version,
      int64_t* out_new_size,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    auto response = brillo::dbus_utils::CallMethodAndBlockWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "GetStatus",
        error);
    return response && brillo::dbus_utils::ExtractMethodCallResults(
        response.get(), error, out_last_checked_time, out_progress, out_current_operation, out_new_version, out_new_size);
  }

  void GetStatusAsync(
      const base::Callback<void(int64_t /*last_checked_time*/, double /*progress*/, const std::string& /*current_operation*/, const std::string& /*new_version*/, int64_t /*new_size*/)>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    brillo::dbus_utils::CallMethodWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "GetStatus",
        success_callback,
        error_callback);
  }

  bool RebootIfNeeded(
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    auto response = brillo::dbus_utils::CallMethodAndBlockWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "RebootIfNeeded",
        error);
    return response && brillo::dbus_utils::ExtractMethodCallResults(
        response.get(), error);
  }

  void RebootIfNeededAsync(
      const base::Callback<void()>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    brillo::dbus_utils::CallMethodWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "RebootIfNeeded",
        success_callback,
        error_callback);
  }

  bool SetChannel(
      const std::string& in_target_channel,
      bool in_is_powerwash_allowed,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    auto response = brillo::dbus_utils::CallMethodAndBlockWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "SetChannel",
        error,
        in_target_channel,
        in_is_powerwash_allowed);
    return response && brillo::dbus_utils::ExtractMethodCallResults(
        response.get(), error);
  }

  void SetChannelAsync(
      const std::string& in_target_channel,
      bool in_is_powerwash_allowed,
      const base::Callback<void()>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    brillo::dbus_utils::CallMethodWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "SetChannel",
        success_callback,
        error_callback,
        in_target_channel,
        in_is_powerwash_allowed);
  }

  bool GetChannel(
      bool in_get_current_channel,
      std::string* out_channel,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    auto response = brillo::dbus_utils::CallMethodAndBlockWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "GetChannel",
        error,
        in_get_current_channel);
    return response && brillo::dbus_utils::ExtractMethodCallResults(
        response.get(), error, out_channel);
  }

  void GetChannelAsync(
      bool in_get_current_channel,
      const base::Callback<void(const std::string& /*channel*/)>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    brillo::dbus_utils::CallMethodWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "GetChannel",
        success_callback,
        error_callback,
        in_get_current_channel);
  }

  bool SetCohortHint(
      const std::string& in_cohort_hint,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    auto response = brillo::dbus_utils::CallMethodAndBlockWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "SetCohortHint",
        error,
        in_cohort_hint);
    return response && brillo::dbus_utils::ExtractMethodCallResults(
        response.get(), error);
  }

  void SetCohortHintAsync(
      const std::string& in_cohort_hint,
      const base::Callback<void()>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    brillo::dbus_utils::CallMethodWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "SetCohortHint",
        success_callback,
        error_callback,
        in_cohort_hint);
  }

  bool GetCohortHint(
      std::string* out_cohort_hint,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    auto response = brillo::dbus_utils::CallMethodAndBlockWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "GetCohortHint",
        error);
    return response && brillo::dbus_utils::ExtractMethodCallResults(
        response.get(), error, out_cohort_hint);
  }

  void GetCohortHintAsync(
      const base::Callback<void(const std::string& /*cohort_hint*/)>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    brillo::dbus_utils::CallMethodWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "GetCohortHint",
        success_callback,
        error_callback);
  }

  bool SetP2PHelloPermission(
      bool in_enabled,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    auto response = brillo::dbus_utils::CallMethodAndBlockWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "SetP2PHelloPermission",
        error,
        in_enabled);
    return response && brillo::dbus_utils::ExtractMethodCallResults(
        response.get(), error);
  }

  void SetP2PHelloPermissionAsync(
      bool in_enabled,
      const base::Callback<void()>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    brillo::dbus_utils::CallMethodWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "SetP2PHelloPermission",
        success_callback,
        error_callback,
        in_enabled);
  }

  bool GetP2PHelloPermission(
      bool* out_enabled,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    auto response = brillo::dbus_utils::CallMethodAndBlockWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "GetP2PHelloPermission",
        error);
    return response && brillo::dbus_utils::ExtractMethodCallResults(
        response.get(), error, out_enabled);
  }

  void GetP2PHelloPermissionAsync(
      const base::Callback<void(bool /*enabled*/)>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    brillo::dbus_utils::CallMethodWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "GetP2PHelloPermission",
        success_callback,
        error_callback);
  }

  bool SetHelloOverCellularPermission(
      bool in_allowed,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    auto response = brillo::dbus_utils::CallMethodAndBlockWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "SetHelloOverCellularPermission",
        error,
        in_allowed);
    return response && brillo::dbus_utils::ExtractMethodCallResults(
        response.get(), error);
  }

  void SetHelloOverCellularPermissionAsync(
      bool in_allowed,
      const base::Callback<void()>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    brillo::dbus_utils::CallMethodWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "SetHelloOverCellularPermission",
        success_callback,
        error_callback,
        in_allowed);
  }

  bool SetHelloOverCellularTarget(
      const std::string& in_target_version,
      int64_t in_target_size,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    auto response = brillo::dbus_utils::CallMethodAndBlockWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "SetHelloOverCellularTarget",
        error,
        in_target_version,
        in_target_size);
    return response && brillo::dbus_utils::ExtractMethodCallResults(
        response.get(), error);
  }

  void SetHelloOverCellularTargetAsync(
      const std::string& in_target_version,
      int64_t in_target_size,
      const base::Callback<void()>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    brillo::dbus_utils::CallMethodWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "SetHelloOverCellularTarget",
        success_callback,
        error_callback,
        in_target_version,
        in_target_size);
  }

  bool GetHelloOverCellularPermission(
      bool* out_allowed,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    auto response = brillo::dbus_utils::CallMethodAndBlockWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "GetHelloOverCellularPermission",
        error);
    return response && brillo::dbus_utils::ExtractMethodCallResults(
        response.get(), error, out_allowed);
  }

  void GetHelloOverCellularPermissionAsync(
      const base::Callback<void(bool /*allowed*/)>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    brillo::dbus_utils::CallMethodWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "GetHelloOverCellularPermission",
        success_callback,
        error_callback);
  }

  bool GetDurationSinceHello(
      int64_t* out_usec_wallclock,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    auto response = brillo::dbus_utils::CallMethodAndBlockWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "GetDurationSinceHello",
        error);
    return response && brillo::dbus_utils::ExtractMethodCallResults(
        response.get(), error, out_usec_wallclock);
  }

  void GetDurationSinceHelloAsync(
      const base::Callback<void(int64_t /*usec_wallclock*/)>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    brillo::dbus_utils::CallMethodWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "GetDurationSinceHello",
        success_callback,
        error_callback);
  }

  bool GetPrevVersion(
      std::string* out_prev_version,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    auto response = brillo::dbus_utils::CallMethodAndBlockWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "GetPrevVersion",
        error);
    return response && brillo::dbus_utils::ExtractMethodCallResults(
        response.get(), error, out_prev_version);
  }

  void GetPrevVersionAsync(
      const base::Callback<void(const std::string& /*prev_version*/)>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    brillo::dbus_utils::CallMethodWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "GetPrevVersion",
        success_callback,
        error_callback);
  }

  bool GetRollbackPartition(
      std::string* out_rollback_partition_name,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    auto response = brillo::dbus_utils::CallMethodAndBlockWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "GetRollbackPartition",
        error);
    return response && brillo::dbus_utils::ExtractMethodCallResults(
        response.get(), error, out_rollback_partition_name);
  }

  void GetRollbackPartitionAsync(
      const base::Callback<void(const std::string& /*rollback_partition_name*/)>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    brillo::dbus_utils::CallMethodWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "GetRollbackPartition",
        success_callback,
        error_callback);
  }

  bool GetLastAttemptError(
      int32_t* out_last_attempt_error,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    auto response = brillo::dbus_utils::CallMethodAndBlockWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "GetLastAttemptError",
        error);
    return response && brillo::dbus_utils::ExtractMethodCallResults(
        response.get(), error, out_last_attempt_error);
  }

  void GetLastAttemptErrorAsync(
      const base::Callback<void(int32_t /*last_attempt_error*/)>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    brillo::dbus_utils::CallMethodWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "GetLastAttemptError",
        success_callback,
        error_callback);
  }

  bool GetEolStatus(
      int32_t* out_eol_status,
      brillo::ErrorPtr* error,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    auto response = brillo::dbus_utils::CallMethodAndBlockWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "GetEolStatus",
        error);
    return response && brillo::dbus_utils::ExtractMethodCallResults(
        response.get(), error, out_eol_status);
  }

  void GetEolStatusAsync(
      const base::Callback<void(int32_t /*eol_status*/)>& success_callback,
      const base::Callback<void(brillo::Error*)>& error_callback,
      int timeout_ms = dbus::ObjectProxy::TIMEOUT_USE_DEFAULT) override {
    brillo::dbus_utils::CallMethodWithTimeout(
        timeout_ms,
        dbus_object_proxy_,
        "org.chromium.HelloWorldInterface",
        "GetEolStatus",
        success_callback,
        error_callback);
  }

 private:
  scoped_refptr<dbus::Bus> bus_;
  std::string service_name_;
  const dbus::ObjectPath object_path_{"/org/chromium/HelloWorld"};
  dbus::ObjectProxy* dbus_object_proxy_;

  DISALLOW_COPY_AND_ASSIGN(HelloWorldInterfaceProxy);
};

}  // namespace chromium
}  // namespace org

#endif  // ____CHROMEOS_DBUS_BINDING__DBUS_PROXIES_H
