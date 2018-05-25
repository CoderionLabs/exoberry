/*
 * Copyright (c) 2015, Google Inc. All rights reserved
 * Copyright 2018 The DEOS Authors
 */
#pragma once

/* Set fault handler for next instruction */
.macro set_fault_handler, handler
.Lfault_location\@:
.pushsection .rodata.fault_handler_table
.long    .Lfault_location\@
.long    \handler
.popsection
.endm
