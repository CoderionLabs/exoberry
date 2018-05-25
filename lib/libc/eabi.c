/* Copyright (c) 2008 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */

/* some cruft we have to define when using the linux toolchain */
#include <unwind.h>

void *__dso_handle;

#if defined(__ARM_EABI_UNWINDER__) && __ARM_EABI_UNWINDER__

/* Our toolchain has eabi functionality built in, but they're not really used.
 * so we stub them out here. */
_Unwind_Reason_Code __aeabi_unwind_cpp_pr0(_Unwind_State state, _Unwind_Control_Block *ucbp, _Unwind_Context *context)
{
    return _URC_FAILURE;
}

_Unwind_Reason_Code __aeabi_unwind_cpp_pr1(_Unwind_State state, _Unwind_Control_Block *ucbp, _Unwind_Context *context)
{
    return _URC_FAILURE;
}

_Unwind_Reason_Code __aeabi_unwind_cpp_pr2(_Unwind_State state, _Unwind_Control_Block *ucbp, _Unwind_Context *context)
{
    return _URC_FAILURE;
}

#endif

/* needed by some piece of EABI */
void raise(void)
{
}

extern int __cxa_atexit(void (*func)(void *), void *arg, void *d);

int __aeabi_atexit(void *arg, void (*func)(void *), void *d)
{
    return __cxa_atexit(func, arg, d);
}



