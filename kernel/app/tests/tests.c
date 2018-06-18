/*
 * Copyright (c) 2008 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <app.h>
#include <debug.h>
#include <app/tests.h>
#include <compiler.h>

#if defined(WITH_LIB_CONSOLE)
#include <lib/console.h>

STATIC_COMMAND_START
STATIC_COMMAND("printf_tests", "test printf", (console_cmd)&printf_tests)
STATIC_COMMAND("printf_tests_float", "test printf with floating point", (console_cmd)&printf_tests_float)
STATIC_COMMAND("thread_tests", "test the scheduler", (console_cmd)&thread_tests)
STATIC_COMMAND("port_tests", "test the ports", (console_cmd)&port_tests)
STATIC_COMMAND("clock_tests", "test clocks", (console_cmd)&clock_tests)
STATIC_COMMAND("bench", "miscellaneous benchmarks", (console_cmd)&benchmarks)
STATIC_COMMAND("fibo", "threaded fibonacci", (console_cmd)&fibo)
STATIC_COMMAND("spinner", "create a spinning thread", (console_cmd)&spinner)
STATIC_COMMAND("cbuf_tests", "test lib/cbuf", &cbuf_tests)
STATIC_COMMAND_END(tests);

#endif

static void tests_init(const struct app_descriptor *app)
{
}

APP_START(tests)
.init = tests_init,
 .flags = 0,
  APP_END

