LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

MODULE_DEPS := \
    lib/unittest

MODULE_SRCS := \
	$(LOCAL_DIR)/app.c \

include make/module.mk
