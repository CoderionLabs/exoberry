/*
 * Copyright (c) 2009 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <app.h>
#include <debug.h>
#include <lib/console.h>

static void shell_init(const struct app_descriptor *app)
{
    console_init();
}

static void shell_entry(const struct app_descriptor *app, void *args)
{
    console_start();
}

APP_START(shell)
.init = shell_init,
 .entry = shell_entry,
  APP_END

