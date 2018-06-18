/*
 * Copyright (c) 2015 Eric Holland
 * Copyright 2018 The DEOS Authors
 */
#ifndef __DEV_ACCELEROMETER_H
#define __DEV_ACCELEROMETER_H
typedef struct {
    double x;
    double y;
    double z;
} position_vector_t;

status_t acc_read_xyz(position_vector_t *pos_vector);

#endif
