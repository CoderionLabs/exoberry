/*
 * Copyright (c) 2008-2015 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */

/* nulled out atexit. static object constructors call this */
int atexit(void (*func)(void))
{
    return 0;
}

