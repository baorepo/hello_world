// Copyright 2015 The Chromium OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYSTEM_API_DBUS_HELLOWORLD_DBUS_CONSTANTS_H_
#define SYSTEM_API_DBUS_HELLOWORLD_DBUS_CONSTANTS_H_

namespace hello_world {
const char kHelloWorldInterface[] = "org.chromium.HelloWorldInterface";
const char kHelloWorldServicePath[] = "/org/chromium/HelloWorld";
const char kHelloWorldServiceName[] = "org.chromium.HelloWorld";

// Generic HelloWorld D-Bus error.
const char kHelloWorldServiceErrorFailed[] =
    "org.chromium.HelloWorld.Error.Failed";

// Methods.
const char kAttemptHello[] = "AttemptHello";
const char kGetLastAttemptError[] = "GetLastAttemptError";
const char kGetStatus[] = "GetStatus";
const char kRebootIfNeeded[] = "RebootIfNeeded";
const char kSetChannel[] = "SetChannel";
const char kGetChannel[] = "GetChannel";
const char kAttemptRollback[] = "AttemptRollback";
const char kCanRollback[] = "CanRollback";
const char kGetEolStatus[] = "GetEolStatus";
const char kSetHelloOverCellularPermission[] =
    "SetHelloOverCellularPermission";
const char kSetHelloOverCellularTarget[] =
    "SetHelloOverCellularTarget";

// Signals.
const char kStatusHello[] = "StatusHello";

// Flags used in the AttemptHelloWithFlags() D-Bus method.
typedef enum {
  kAttemptHelloFlagNonInteractive = (1 << 0)
} AttemptHelloFlags;

// End of Life status used in the GetEolStatus() D-Bus method.
typedef enum {
  kSupported = 0,
  kSecurityOnly = 1,
  kEol = 2,
} EndOfLifeStatus;

// Operations contained in StatusHello signals.
const char kHelloStatusIdle[] = "HELLO_STATUS_IDLE";
const char kHelloStatusCheckingForHello[] =
    "HELLO_STATUS_CHECKING_FOR_Hello";
const char kHelloStatusHelloAvailable[] = "HELLO_STATUS_Hello_AVAILABLE";
const char kHelloStatusDownloading[] = "HELLO_STATUS_DOWNLOADING";
const char kHelloStatusVerifying[] = "HELLO_STATUS_VERIFYING";
const char kHelloStatusFinalizing[] = "HELLO_STATUS_FINALIZING";
const char kHelloStatusHellodNeedReboot[] =
    "HELLO_STATUS_HELLO_NEED_REBOOT";
const char kHelloStatusReportingErrorEvent[] =
    "HELLO_STATUS_REPORTING_ERROR_EVENT";
const char kHelloStatusAttemptingRollback[] =
    "HELLO_STATUS_ATTEMPTING_ROLLBACK";
const char kHelloStatusDisabled[] = "HELLO_STATUS_DISABLED";
const char kHelloStatusNeedPermissionToHello[] =
    "HELLO_STATUS_NEED_PERMISSION_TO_HELLO";
}  // namespace hello_world

#endif  // SYSTEM_API_DBUS_HELLOWORLD_DBUS_CONSTANTS_H_
