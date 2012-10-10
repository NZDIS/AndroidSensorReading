LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := Controller
LOCAL_SRC_FILES := Controller.cpp Accelerometer.cpp 

LOCAL_LDLIBS := -lm -lGLESv2 -ldl -llog -landroid

include $(BUILD_SHARED_LIBRARY)


