ulimit -S -c unlimited

EXAMPLE="${1:-passwordapp}"
OS="${2:-Linux}"
CLEAN="${3:-no}"

echo $EXAMPLE
echo $OS

ISO="en"
export ISO

if [[ $OS = "Linux" ]]; then
	if [[ $CLEAN = "clean" ]]; then
		make clean
		PACKAGE="gui" NAME="libctrgui.so" make plugin-clean
	fi
	make
	PACKAGE="gui" NAME="libctrgui.so" make plugin
	cd examples/${EXAMPLE}
	rm mods
	ln -s ../../build/Linux/bin/mods mods
	../../build/Linux/bin/xo ${EXAMPLE}.xo 
fi

if [[ $OS = "Win64" ]]; then
	if [[ $CLEAN = "clean" ]]; then
		make -f makefile.win64 clean
		PACKAGE="gui" NAME="libctrgui.dll" make -f makefile.win64 plugin-clean
	fi
	make -f makefile.win64
	PACKAGE="gui" NAME="libctrgui.dll" make -f makefile.win64 plugin
	cd examples/${EXAMPLE}
	rm mods
	ln -s ../../build/Win64/bin/mods mods
	wine ../../build/Win64/bin/xo.exe ${EXAMPLE}.xo 
fi

if [[ $OS = "Mac" ]]; then
	if [[ $CLEAN = "clean" ]]; then
		make -f makefile.mac clean
		PACKAGE="gui" NAME="libctrgui.dylib" make -f makefile.mac plugin-clean
	fi
	make -f makefile.mac
	PACKAGE="gui" NAME="libctrgui.dylib" make -f makefile.mac plugin
	cd examples/${EXAMPLE}
	rm mods
	ln -s ../../build/Mac/bin/mods mods
	../../build/Mac/bin/xo ${EXAMPLE}.xo
fi
