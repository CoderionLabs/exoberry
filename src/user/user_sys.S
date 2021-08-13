.section ".text.user"

.globl user_delay
user_delay:
	subs x0, x0, #1
	bne user_delay
	ret
