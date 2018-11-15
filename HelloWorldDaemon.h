#ifndef HELLOWORLD_DAEMON_H_
#define HELLOWORLD_DAEMON_H_
#include <memory>
#include <string>

#include <brillo/daemons/daemon.h>
#include "dbus_service.h"
namespace chromeos_hello_world{
class HelloWorldDaemon: public brillo::Daemon {
 public:
  HelloWorldDaemon() = default;

 protected:
  int OnInit() override;
 private:
   // Run from the main loop when the |dbus_adaptor_| object is registered. At
  // this point we can request ownership of the DBus service name and continue
  // initialization.
  void OnDBusRegistered(bool succeeded);

  // Main D-Bus service adaptor.
  std::unique_ptr<HelloWorldAdaptor> dbus_adaptor_;
 // The daemon state with all the required daemon classes for the configured
  // platform.
  //std::unique_ptr<DaemonStateInterface> daemon_state_;

  DISALLOW_COPY_AND_ASSIGN(HelloWorldDaemon);
};
};
#endif //HELLOWORLD_DAEMON_H_