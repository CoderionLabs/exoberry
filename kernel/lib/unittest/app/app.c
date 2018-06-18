/*
 * Copyright (c) 2013, Google, Inc. All rights reserved
 * Copyright 2018 The DEOS Authors
 */
#include <app.h>
#include <unittest.h>
#include <platform.h>

void unittest_entry(const struct app_descriptor *app, void *args)
{
    bool success = run_all_tests();
}

APP_START(unittest)
.entry = unittest_entry,
 APP_END
