/*
 * Copyright (c) 2008 Travis Geiselbrecht
 * * Copyright 2018 The DEOS Authors
 */
#include <app.h>
#include <debug.h>
#include <stdio.h>
#include <dev/accelerometer.h>
#include <compiler.h>


#if defined(WITH_LIB_CONSOLE)
#include <lib/console.h>

void read_xyz(void);

STATIC_COMMAND_START
STATIC_COMMAND("read_xyz", "read xyz vectors", (console_cmd)&read_xyz)
STATIC_COMMAND_END(accelerometer);

#endif

void read_xyz(void)
{
    position_vector_t pos_vector;
    acc_read_xyz(&pos_vector);
    printf("X value = %f\n",pos_vector.x);
    printf("Y value = %f\n",pos_vector.y);
    printf("Z value = %f\n",pos_vector.z);

}

APP_START(accelerometer)
.flags = 0,
 APP_END

