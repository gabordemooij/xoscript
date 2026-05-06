BUILD_DIR         = .
BUILD_OBJ_DIR     = $(BUILD_DIR)/Linux/obj
BUILD_BIN_DIR     = $(BUILD_DIR)/Linux/bin
BIN               = xo
CFLAGS            = -O2 -g -mtune=native -Wpedantic -Wall -Wno-unknown-pragmas -I src/i18n/en -D Linux -D ALLOCALIGN=16 -D LIBBSD -D CTRLANG=en -D INCLUDETESTS
LDFLAGS           = -g -rdynamic -lm -ldl -lbsd
CSRCS             = $(shell find ./src -maxdepth 1 -type f -name '*.c')
COBJS             = $(patsubst ./src/%.c, $(BUILD_OBJ_DIR)/%.o, $(CSRCS))
TARGET            = $(COBJS)

all: xotr

xotr:
	cc  ../../src/lexer.c xotr.c -I ../../src/i18n/en -I ../../src -o xotr
	

clean:
	rm  xotr


