/*
 * Copyright 2018 The DEOS Authors
 */


// Scoped spinlock

#pragma once

#include <kernel/spinlock.h>

template <unsigned int flags = ARCH_DEFAULT_SPIN_LOCK_FLAG_INTERRUPTS>
class AutoSpinLock {
public:
    inline explicit AutoSpinLock(spin_lock_t* lock) : lock_(lock){
        arch_interrupt_save(&state_, flags);
        spin_lock(lock_);
    }

    inline ~AutoSpinLock(){
        spin_unlock(lock_);
        arch_interrupt_save(state_, flags);
    }

        
    // Don't allow these
    AutoSpinLock(const AutoSpinLock&) = delete;
    AutoSpinLock(AutoSpinLock&&) = delete;

    // No copying
    AutoSpinLock& operator = (const AutoSpinLock&) = delete;

private:
    spin_lock_t* lock_;
    spin_lock_saved_state_t state_;
};