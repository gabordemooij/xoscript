CC ?= gcc
PLUGIN_DIR ?= .
WARNINGS ?= -Wall 
CFLAGS ?= ${EXTRACFLAGS} -shared -O3 -g0 -I ./ -I ../../i18n/${ISO}/ $(WARNINGS) -fPIC
CFLAGS += `pkg-config --cflags libsecret-1`
LDFLAGS =  -lm -shared
LDFLAGS += `pkg-config --libs libsecret-1`
BIN = libctr$(NAME).so
BUILD_DIR = ../../../build/Linux
BUILD_OBJ_DIR = $(BUILD_DIR)/obj/mods/$(NAME)
BUILD_BIN_DIR = $(BUILD_DIR)/bin/mods/$(NAME)
prefix ?= /usr
bindir ?= $(prefix)/bin
CSRCS += example.c
OBJEXT ?= .o
COBJS = $(CSRCS:.c=$(OBJEXT))
MAINOBJ = $(MAINSRC:.c=$(OBJEXT))
SRCS = $(CSRCS) $(MAINSRC)
OBJS = $(COBJS) $(MAINOBJ)
TARGET = $(addprefix $(BUILD_OBJ_DIR)/, $(patsubst ./%, %, $(OBJS)))

all: default

$(BUILD_OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC)  $(CFLAGS) -c $< -o $@
	@echo "CC $<"

default: $(TARGET)
	@mkdir -p $(dir $(BUILD_BIN_DIR)/)
	$(CXX) -o $(BUILD_BIN_DIR)/$(BIN) $(TARGET) $(LDFLAGS)

clean: 
	rm -rf $(BUILD_OBJ_DIR)/*
	rm -rf $(BUILD_BIN_DIR)/*
