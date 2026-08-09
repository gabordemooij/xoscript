XOScript
========

XOScript is a simple server-side scripting language
focusing on security through simplicity and auditability.

- Simple grammar, just 5 rules
- Sane security defaults
- Backward compatible, always
- No packages needed, fully featured
- Simple deployment, just drop an .xo file and run it
- Minimal machinery, no large, opaque runtime stack

Security is difficult when the behavior of a system is difficult to understand.
XOScript therefore focuses on reducing the number of things developers
need to reason about: fewer language rules, fewer dependencies, fewer moving parts,
and a runtime designed to remain understandable. With XOScript,
you, the developer, take back control.

## Example

```xo
# Add a simple XOScript example here
```

## In short

**XOScript is a simple, server-side scripting language built around one idea:**

> **Software that is easier to understand is easier to maintain and audit.**


xoscript
========

Welcome to XOScript.

Security is becoming a bigger issue every day.
To keep your code secure you have to be able to maintain it
properly and understand it. This is harder than you think.

Many of todays programming languages have evolved to have
a highly complex syntax, need lots of dependencies and packages to run,
have lots of historical quirks, have a lot complex machinery under the
hood and constantly break with every update.

The purpose of XOScript is to offer a scripting language that
is really simple to understand on every layer, from script file to
engine, making your code easier to maintain. This is how we do it:

- Simple grammar, just 5 rules of writing
- Secure by default
- Backward compatible, always
- No packages needed, fully featured base
- Page-based, just upload .xo file and done
- No complex machinery under the hood

With XOScript you are in control. You can understand every
layer of the system without being a rocket scientist.
And, that means that you can, at least be little more confident
about the security of your systems.

XOScript is server-side scripting language, focused on
security through simplicity and auditability.






Here is how to say 'Hello World' in XO:

Example:

```
Out write: ['Hello world'], stop.
```

To run this program:

```
xo hello.xo
```

To run it on the server, just install the XOScript interpreter
on your server and the Server plugin in the /mods folder next to it.
Then, with a CGI webserver, point your script file to
XOScript with something like:

```
#!/bin/xo
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

To run the example with a clean build in English:

```
./example.sh fizzbuzz OBSD clean en
```

To run the unit tests:

```
./runtests.sh
```

To run the unit test without building (just testing):

```
./runtests.sh nobuild
```

On OpenBSD:

```
./runtests_obsd.sh nobuild
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
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

To build the server plugin on Linux:

```
PACKAGE="server" NAME="server" make plugin-clean
ISO="en" PACKAGE="server" NAME="server" make plugin
```

For Spanish:

```
PACKAGE="server" NAME="servidor" make plugin-clean
ISO="en" PACKAGE="server" NAME="servidor" make plugin
```

To build the server plugin on OpenBSD:

```
PACKAGE="server" NAME="server" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server" make -f makefile.obsd plugin
```

