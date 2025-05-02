xoscript
========

Welcome to xoscript.

xoscript is a __generic client-side scripting language__ to quickly
develop connected, cross-platform apps.

Example:

```
# Hello world in dialog
Gui show: ['Hello world'].
```

To run an example program:

```
./example.sh <name> <Linux/Win64> [clean]
```

For example, to run the counter example on Linux:

```
./example.sh counter Linux
```

Another example: run the helloworld example on Win64 with a clean build:

```
./example.sh helloworld Win64 clean
```

To run the unit tests (Mingw-win/Lin):

```
./runtests.sh
```

To run the unit test without building (just testing):

```
./runtests.sh nobuild
```

The tests are designed to run on Linux and test Win64 through mingw/wine.

If you use the binary distribution, you don't have to use the example.sh script,
simply do:

```
xo counter_example.xo
```

To build from source on Linux:

```
ISO="en" make clean
ISO="en" make
ISO="en" PACKAGE="gui" NAME="libctrgui.so" make plugin-clean
ISO="en" PACKAGE="gui" NAME="libctrgui.so" make plugin
```

for Win64/mingw32:

```
ISO="en" make -f makefile.win64 clean
ISO="en" make -f makefile.win64
ISO="en" PACKAGE="gui" NAME="libctrgui.so" make -f makefile.win64 plugin-clean
ISO="en" PACKAGE="gui" NAME="libctrgui.so" make -f makefile.win64 plugin
```

on macos:

```
ISO="en" make -f makefile.mac clean
ISO="en" make -f makefile.mac
ISO="en" PACKAGE="gui" NAME="libctrgui.so" make -f makefile.mac plugin-clean
ISO="en" PACKAGE="gui" NAME="libctrgui.so" make -f makefile.mac plugin
```

Of course you may also just export the vars (ISO etc..).
Just a matter of style.

