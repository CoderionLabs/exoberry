/*
 * Copyright (c) 2013-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */



/*
 * Acquire lock using load-/store-exclusive instruction pair.
 *
 * void spin_lock(spinlock_t *lock);
 */

.globl spin_lock
spin_lock:
	mov	x1, #1
	sevl
1:
	wfe
	ldaxr	x2, [x0]
	cbnz	x2, 1b
	stxr	w2, x1, [x0]
	cbnz	w2, 1b
	ret

/*
 * Release lock previously acquired by spin_lock.
 *
 * Use store-release to unconditionally clear the spinlock variable.
 * Store operation generates an event to all cores waiting in WFE
 * when address is monitored by the global monitor.
 *
 * void spin_unlock(spinlock_t *lock);
 */

.globl	spin_unlock
spin_unlock:
	stlr	wzr, [x0]
	ret
