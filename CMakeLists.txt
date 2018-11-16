cmake_minimum_required(VERSION 3.7.2)
project (HelloWorld)
set (CMAKE_C_COMPILER "clang ")
set (CMAKE_CXX_COMPILER "clang++")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fno-strict-aliasing -Woverloaded-virtual -DNDEBUG -g")
#add_compile_options( "-Wl,--gc-sections ")

find_package(PkgConfig REQUIRED) 
pkg_search_module(CHROME  libbrillo-395517 libbrillo-glib-395517 libbrillo-test-395517 libchrome-395517 protobuf-lite protobuf)


add_executable(HelloWorld 
                main.cc
                HelloWorldDaemon.cc
                dbus_service.cc
                dbus_bindings/dbus_connection.cc
                proto_bindings/hello_world.pb.cc
                )
#message(${CHROME_INCLUDE_DIRS})
target_include_directories(HelloWorld PUBLIC ${CHROME_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../)

target_link_libraries(HelloWorld  PUBLIC
                        brillo-core-395517
                        base-core-395517
                        base-dbus-395517 
                        atomic 
                        pthread 
                        protobuf-lite
                        protobuf
                        rt 
                        modp_b64 
                        dbus-1
                        dbus-glib-1
                        expat
                        )                 

add_executable(HelloWorldClient 
                    HelloWorldClient_impl.cc
                    HelloWorldClient.cc
                    proto_bindings/hello_world.pb.cc
                    )

target_include_directories(HelloWorldClient PUBLIC ${CHROME_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../)
        
target_link_libraries(HelloWorldClient  PUBLIC
                        brillo-core-395517
                        base-core-395517
                        base-dbus-395517 
                        atomic 
                        pthread 
                        protobuf-lite
                        protobuf
                        rt 
                        modp_b64 
                        dbus-1
                        dbus-glib-1
                        expat
                        )                                         