/*
 * Copyright 2016 Google Inc. All Rights Reserved.
 * Author: gkalsi@google.com (Gurjant Kalsi)
 * Copyright 2018 The DEOS Authors
 */

#pragma once

// The platform/target should implement this routine by mouting the default
// filesystem and returning a string that points to the mount point. If NULL is
// returned it is assumed that either (1) the platform does not implement FS
// boot or that (2) mounting the default filesystem failed in which case the
// system proceeds to boot without FSBoot.
void attempt_fs_boot(void);
