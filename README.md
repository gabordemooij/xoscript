xoscript
========

Welcome to xoscript.

xoscript is a __simple scripting language__ to quickly
develop (server-side) applications.

Example:

```
Out write: ['Hello world'], stop.
```

To run this program:

```
xo hello.xo
```

To run one of the example programs in the package:

```
./example.sh <name> <Linux/Win64> [clean]
```

For example, to run the FizzBuzz example on Linux:

```
./example.sh fizzbuzz Linux
```

To run the same example on OpenBSD:

```
./example.sh fizzbuzz OBSD
```

To run the example with a clean build:

```
./example.sh fizzbuzz OBSD clean
```

To run the unit tests:

```
./runtests.sh
```

To run the unit test without building (just testing):

```
./runtests.sh nobuild
```

Binary distributions are available from the website:
https://xoscript.com

To build from source on Linux:

```
make clean
ISO="en" make
```

On OpenBSD:

```
gmake -f makefile.obsd clean
ISO="en" gmake -f makefile.obsd
```

To build the server plugin on Linux:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

To build the server plugin on OpenBSD:

```
PACKAGE="server" NAME="server.so" gmake -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" gmake -f makefile.obsd plugin
```

