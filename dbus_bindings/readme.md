
### Note

```
generate-chromeos-dbus-bindings org.chromium.HelloWorldInterface.dbus-xml --adaptor=org.chromium.HelloWorldInterface.h
generate-chromeos-dbus-bindings org.chromium.HelloWorldInterface.dbus-xml --proxy=dbus-proxies.h
sudo cp HelloWorld.conf /etc/dbus-1/system.d/
```