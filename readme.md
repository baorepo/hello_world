# Hello World

## test

One terminal:
```
debian@beaglebone:~/hello_world/build$ sudo ./HelloWorld --logtostderr
[sudo] password for debian: 
[1116/032311:INFO:main.cc(88)] Hello World Daemon starting
[1116/032311:INFO:HelloWorldDaemon.cc(10)] Waiting for DBus object to be registered.
[1116/032314:INFO:dbus_service.cc(83)] 1231231231231,12312321312,1312312123123

[1116/032423:INFO:dbus_service.cc(83)] 1231231231231,12312321312,1312312123123,fsadfsdfsaf

[1116/032436:INFO:dbus_service.cc(57)] Attempt update: app_version="" omaha_url="http://192.168.4.48/respeaker/develop" flags=0x0 interactive=yes RestrictDownload=no 

```
The other terminal:
```
debian@beaglebone:~/hello_world/build$ sudo ./HelloWorldClient --install --dlc_ids="1231231231231,12312321312,1312312123123" 
debian@beaglebone:~/hello_world/build$ sudo ./HelloWorldClient --install --dlc_ids="1231231231231,12312321312,1312312123123,fsadfsdfsaf" 
debian@beaglebone:~/hello_world/build$ sudo ./HelloWorldClient --omaha_url=http://192.168.4.48/respeaker/develop
[1116/032436:INFO:HelloWorldClient.cc(524)] Initiating hello check and install.
```