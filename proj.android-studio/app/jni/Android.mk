LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)
$(call import-add-path,$(LOCAL_PATH)/../../../Libraries)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../../Classes/AppDelegate.cpp

# LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

CPP_FILES := $(shell find $(LOCAL_PATH)/../../../Classes -name "*.cpp")
LOCAL_SRC_FILES := hellocpp/main.cpp \
					jp_co_rightcode_rakuran_AppActivity.cpp

LOCAL_SRC_FILES += $(CPP_FILES:$(LOCAL_PATH)/%=%)
LOCAL_C_INCLUDES := $(shell find $(LOCAL_PATH)/../../../Classes -type d)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Libraries/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Libraries/boost/include

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END

LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
