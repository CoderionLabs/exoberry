/*
 * Copyright 2016 Google Inc. All Rights Reserved.
 * Author: gkalsi@google.com (Gurjant Kalsi)
 * Copyright 2018 The DEOS Authors
 */

#include <app/moot/stubs.h>
#include <compiler.h>
#include <err.h>

// Fail by default. System must override this.
__WEAK status_t moot_mount_default_fs(char **mount_path, char **device_name)
{
    *device_name = NULL;
    *mount_path = NULL;
    return ERR_NOT_IMPLEMENTED;
}
