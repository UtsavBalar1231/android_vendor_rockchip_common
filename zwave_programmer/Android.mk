#
# Copyright (C) 2014 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

LOCAL_PATH := $(call my-dir)

CONTIKI_DIR := contiki

COMMON_INCLUDES := \
	$(LOCAL_PATH)/systools/zw_programmer \
	$(LOCAL_PATH)/Z-Wave/include \
	$(LOCAL_PATH)/src \
	$(LOCAL_PATH)/src/utls/ \
	$(LOCAL_PATH)/src/zwpgrmr/ \
	$(LOCAL_PATH)/src/serialapi \
	$(LOCAL_PATH)/contiki \
	$(LOCAL_PATH)/contiki/platform/linux \
	$(LOCAL_PATH)/contiki/platform/linux/dev \
	$(LOCAL_PATH)/contiki/cpu/native/. \
	$(LOCAL_PATH)/contiki/cpu/native/net \
	$(LOCAL_PATH)/contiki/core/dev \
	$(LOCAL_PATH)/contiki/core/lib \
	$(LOCAL_PATH)/contiki/core/net \
	$(LOCAL_PATH)/contiki/core/sys \
	$(LOCAL_PATH)/contiki/core \
	$(LOCAL_PATH)/../../../../external/libusb/include/libusb \

COMMON_SRC_FILES := \
	systools/zw_programmer/zw_programmer.c \
	src/txmodem.c \
	src/serialapi/port-timer-linux.c \
	contiki/cpu/native/linux-serial.c \
	contiki/core/lib/assert.c \
	src/serialapi/Serialapi.c \
	src/serialapi/conhandle.c \
	src/serialapi/nvm_tools.c \
	src/serialapi/sdk_versioning.c \
	src/zwpgrmr/zpg.c \
	src/zwpgrmr/zpgp.c \
	src/zwpgrmr/linux_usb_interface.c \
	src/zwpgrmr/linux_serial_interface.c \
	src/zwpgrmr/crc32.c \
	src/utls/zgw_crc.c \
	src/utls/zgw_nodemask.c \
	src/utls/hex_to_bin.c \

COMMON_CFLAGS := \
	-std=gnu11 \
	-Os \
	-Wall -Werror \
	-Wvisibility \
	-Wno-unused-function \
	-Wno-unused-variable \
	-Wimplicit-function-declaration \
	-Wno-char-subscripts \
	-Wno-gnu-variable-sized-type-not-at-end \
	-Wno-missing-field-initializers \
	-Wno-sign-compare \
	-Wno-string-plus-int \
	-Wno-uninitialized \
	-Wno-unused-parameter \
	-funsigned-char \
	-ffunction-sections -fdata-sections \
	-fno-asynchronous-unwind-tables \
	-DSERIAL_LOG \


COMMON_LIBS := libc liblog libusb

############################################
## build zwave_programmer
############################################

include $(CLEAR_VARS)

LOCAL_MODULE := zw_programmer
LOCAL_PROPRIETARY_MODULE := true
LOCAL_CFLAGS := $(COMMON_CFLAGS)
LOCAL_C_INCLUDES := $(COMMON_INCLUDES)
LOCAL_SRC_FILES := $(COMMON_SRC_FILES)
LOCAL_SHARED_LIBRARIES := $(COMMON_LIBS)

include $(BUILD_EXECUTABLE)
