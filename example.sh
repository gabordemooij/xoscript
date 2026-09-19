ulimit -S -c unlimited

if [ "$#" -eq 0 ]; then
    echo "Usage: example.sh <example> [Linux|OBSD] [clean] [en]"
    exit 0
fi

EXAMPLE="${1:-none}"
OS="${2:-Linux}"
CLEAN="${3:-no}"
ISO="${4:-en}"

echo "Running example: "
echo $EXAMPLE

echo "On platform: "
echo $OS

echo "with language edition code: "
echo $ISO

echo "With build option: "
echo $CLEAN

if [[ $ISO = "nl" ]]; then
	ISOKEY=2
elif [[ $ISO = "en" ]]; then
	ISOKEY=1
elif [[ $ISO = "es" ]]; then
	ISOKEY=0
else
	echo "Example for this language not supported yet."
fi

server_plugin_name[0]="servidor"
server_plugin_name[1]="server"
server_plugin_name[2]="server"
echo ${server_plugin_name[$ISOKEY]}

export ISO

if [[ $OS = "Linux" ]]; then
	if [[ $CLEAN = "clean" ]]; then
		make clean
		PACKAGE="server" NAME="${server_plugin_name[$ISOKEY]}" make plugin-clean
	fi
	make
	PACKAGE="server" NAME="${server_plugin_name[$ISOKEY]}" make plugin
	cd examples/${EXAMPLE}
	rm mods
	ln -s ../../build/Linux/bin/mods mods
	ln -s ../../src/xo/* .
	echo 'c=3' > /tmp/xo_fxt_stdin
	CITRINE_MEMORY_MODE=4 \
	REQUEST_METHOD="POST" \
	CONTENT_TYPE="application/x-www-form-urlencoded" \
	CONTENT_LENGTH=3 \
	QUERY_STRING="a=2&b=4" \
	HTTP_COOKIE="xsid=abc123" \
	../../build/Linux/bin/xo ${EXAMPLE}.xo < /tmp/xo_fxt_stdin
fi

if [[ $OS = "OBSD" ]]; then
	if [[ $CLEAN = "clean" ]]; then
		make -f makefile.obsd clean
		PACKAGE="server" NAME="${server_plugin_name[$ISOKEY]}" make -f makefile.obsd plugin-clean
	fi
	make -f makefile.obsd
	PACKAGE="server" NAME="${server_plugin_name[$ISOKEY]}" make -f makefile.obsd plugin
	cd examples/${EXAMPLE}
	rm mods
	ln -s ../../build/OpenBSD/bin/mods mods
	ln -s ../../src/xo/* .
	printf 'c=3' > /tmp/xo_fxt_stdin
	CITRINE_MEMORY_MODE=4 \
	REQUEST_METHOD="POST" \
	CONTENT_TYPE="application/x-www-form-urlencoded" \
	CONTENT_LENGTH=3 \
	QUERY_STRING="a=2&b=4" \
	HTTP_COOKIE="xsid=abc123" \
	../../build/OpenBSD/bin/xo ${EXAMPLE}.xo < /tmp/xo_fxt_stdin
fi


