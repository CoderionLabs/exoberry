LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

MODULE_SRCS += \
	$(LOCAL_DIR)/protocol.c
	$(LOCAL_DIR)/message.c

include make/module.mk
