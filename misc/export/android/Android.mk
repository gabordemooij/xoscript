LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL2
ISO := en

# Create a symlink called orig that points to the Citrine source directory
LOCAL_C_INCLUDES := $(LOCAL_PATH)/.. $(LOCAL_PATH)/../Citrine/orig/src \
$(LOCAL_PATH)/../Citrine/orig/src/i18n/$(ISO) \
$(LOCAL_PATH)/../Citrine/orig/src/plugins/gui \
$(LOCAL_PATH)/../Citrine/orig/src/plugins/gui/i18n/$(ISO) \


# Add your application source files here...
LOCAL_SRC_FILES :=  citrine_gui.c orig/src/base.c orig/src/file.c \
orig/src/memory.c orig/src/siphash.c orig/src/util.c \
orig/src/citrine.c orig/src/lexer.c orig/src/parser.c \
orig/src/system.c orig/src/walker.c \
orig/src/collections.c  orig/src/portability.c orig/src/test.c \
orig/src/utf8.c orig/src/world.c \
orig/src/plugins/gui/jsmn/jsmn.c orig/src/plugins/gui/json.c \
orig/src/plugins/gui/vault.c orig/src/plugins/gui/gui.c\


GUI_PATH = $(LOCAL_PATH)/orig/src/plugins/gui
LOCAL_CFLAGS += -I$(GUI_PATH)
LOCAL_CFLAGS += -D ANDROID_EXPORT -D FULLSCREEN


LOCAL_SHARED_LIBRARIES := SDL2 SDL2_ttf SDL2_image lvgl
LOCAL_LDLIBS := -lOpenSLES -llog -landroid 

include $(BUILD_SHARED_LIBRARY)
