# works with GNU make and BSD make; no dependencies besides bearssl/
CC ?= cc
CFLAGS ?= -O2 -Wall

xocat: xocat.c
	$(CC) $(CFLAGS) -Ibearssl/inc -Ibearssl/src -o xocat xocat.c bearssl/src/*.c bearssl/src/*/*.c

clean:
	rm -f xocat
