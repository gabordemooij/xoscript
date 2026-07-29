#gmake
USE_GTK ?= 0
CFLAGS = -I.
LDFLAGS = -lm 
CSRCS = xocl.c

ifeq ($(USE_GTK),1)
	CSRCS += gui/gtk/gtk.c
	CFLAGS += -DGUI_GTK $(shell pkg-config --cflags gtk4)
	LDFLAGS += $(shell pkg-config --libs gtk4)
endif

all: default

default: xocl.c
	$(CC) $(CFLAGS) $(CSRCS) $(LDFLAGS) -o xocl

clean: 
	rm xocl.o
	rm xocl
