/*
 * Copyright 2018 The DEOS Authors
 */

#pragma once

#include <kernel/mutex>

class AutoLock{
public:
    AutoLock(mutex_t* mutex) : mutex_(mutex){
        mutex_acquire(mutex_);
    }

    AutoLock(mutex_t* mutex) : AutoLock(&mutex){}

    ~AutoLock(){
        release();
    }

    void release(){
        if(mutex_){
            mutex_release(mutex_);
            mutex_ = nullptr;
        }
    }


    // Don't allow these
    AutoLock(const AutoLock& am) = delete;
    AutoLock& operator=(const AutoLock& am) = delete;
    AutoLock(AutoLock&& c) = delete;
    AutoLock& operator=(AutoLock&& c) = delete;
private:
    mutex_t* mutex_;
}