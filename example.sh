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
		PACKAGE="server" NAME="server.so" make plugin-clean
	fi
	make
	PACKAGE="server" NAME="server.so" make plugin
	cd examples/${EXAMPLE}
	rm mods
	ln -s ../../build/Linux/bin/mods mods
	
	CITRINE_MEMORY_MODE=4 \
	REQUEST_METHOD="POST" \
	CONTENT_TYPE="application/x-www-form-urlencoded" \
	CONTENT_LENGTH=3 \
	QUERY_STRING="a=2&b=4" \
	HTTP_COOKIE="xsid=abc123" \
	../../build/Linux/bin/xo ${EXAMPLE}.xo < <(echo -n "c=3")
fi

# On OpenBSD you need gmake and bash
if [[ $OS = "OBSD" ]]; then
	if [[ $CLEAN = "clean" ]]; then
		gmake -f makefile.obsd clean
		PACKAGE="server" NAME="server.so" gmake -f makefile.obsd plugin-clean
	fi
	gmake -f makefile.obsd
	PACKAGE="server" NAME="server.so" gmake -f makefile.obsd plugin
	cd examples/${EXAMPLE}
	rm mods
	ln -s ../../build/OpenBSD/bin/mods mods
	
	CITRINE_MEMORY_MODE=4 \
	REQUEST_METHOD="POST" \
	CONTENT_TYPE="application/x-www-form-urlencoded" \
	CONTENT_LENGTH=3 \
	QUERY_STRING="a=2&b=4" \
	HTTP_COOKIE="xsid=abc123" \
	../../build/OpenBSD/bin/xo ${EXAMPLE}.xo < <(echo -n "c=3")
fi


