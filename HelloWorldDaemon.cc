#include "HelloWorldDaemon.h"

namespace chromeos_hello_world {
int HelloWorldDaemon::OnInit(){
    // Create the DBus service.
  dbus_adaptor_.reset(new HelloWorldAdaptor());

  dbus_adaptor_->RegisterAsync(base::Bind(&HelloWorldDaemon::OnDBusRegistered,
                                          base::Unretained(this)));
  LOG(INFO) << "Waiting for DBus object to be registered.";
  return EX_OK;
}

void HelloWorldDaemon::OnDBusRegistered(bool succeeded){
  if (!succeeded) {
    LOG(ERROR) << "Registering the HelloWorldAdaptor";
    QuitWithExitCode(1);
    return ;
  }

  // Take ownership of the service now that everything is initialized. We need
  // to this now and not before to avoid exposing a well known DBus service
  // path that doesn't have the service it is supposed to implement.
  if (!dbus_adaptor_->RequestOwnership()) {
    LOG(ERROR) << "Unable to take ownership of the DBus service, is there "
               << "other hello_world daemon running?";
    QuitWithExitCode(1);
    return ;
  }
}
};