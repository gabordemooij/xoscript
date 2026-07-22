#!/bin/ksh
#set -x
#set -v
ulimit -c 0 # avoid core dumps bc pledge/unveil

# set malloc in security audit mode
MALLOC_OPTIONS=S
export MALLOC_OPTIONS

CITRINE_MEMORY_LIMIT_MB=10
export CITRINE_MEMORY_LIMIT_MB

PLATFORMCODE="obsd"
export PLATFORMCODE

BUILD="${1:-build}"


declare -A server_plugin_name
server_plugin_name[es]="servidor"
server_plugin_name[en]="server"
server_plugin_name[nl]="server"

if [[ $BUILD == "build" ]]; then
LDFLAGS='-shared'
for ISO in "nl" "es" "en"; #en last (=base)
do
export ISO
make clean
EXTRACFLAGS="-D TEST -D EXPERIMENTS"
export EXTRACFLAGS
make -f makefile.obsd clean
PACKAGE="server" NAME=${server_plugin_name[$ISO]} make -f makefile.obsd plugin-clean
make -f makefile.obsd
PACKAGE="server" NAME=${server_plugin_name[$ISO]} make -f makefile.obsd plugin
cp build/OpenBSD/bin/xo build/OpenBSD/bin/xo$ISO #copy lang edition
done
fi

printf '%s' 'c=3&e[]=1&e[]=2&xx=1' > /tmp/xotest.txt

setup1() {
	i=$1
	REQUEST_METHOD="POST" \
	CONTENT_TYPE="application/x-www-form-urlencoded" \
	CONTENT_LENGTH=20 \
	QUERY_STRING="a=2&b=4&d[]=a&d[]=b&f[]=1&f[]=2" \
	HTTP_COOKIE="xsid=abc123" \
	FFITESTLIB=$(ldconfig -r | awk '$3 ~ /libc\.so/ {print $3}') \
	./xo ../../../tests/t-$i.ctr 1>/tmp/rs 2>/tmp/err < /tmp/xotest.txt
}

setup2() {
	i=$1
	BOUNDARY='------------------------abcdef1234567890'
	BODY=$(printf -- '--%s\r\nContent-Disposition: form-data; name="c"\r\n\r\n2\r\n--%s\r\nContent-Disposition: form-data; name="file"; filename="hello.txt"\r\nContent-Type: text/plain\r\n\r\nhello file\r\n--%s--\r\n' "$BOUNDARY" "$BOUNDARY" "$BOUNDARY")
	printf '%s' "$BODY" | \
	CONTENT_TYPE="multipart/form-data; boundary=$BOUNDARY" \
	CONTENT_LENGTH=${#BODY} \
	REQUEST_METHOD=POST \
	./xo ../../../tests/t-$i.ctr 1>/tmp/rs 2>/tmp/err
}

setup3() {
	i=$1
	CITRINE_MEMORY_PROFILE=1 \
	./xo ../../../tests/t-$i.ctr 1>/tmp/rs 2>/tmp/err
}

unittest() {
	i=$1
	mmode=$2
	CITRINE_MEMORY_MODE=$mmode
	export CITRINE_MEMORY_MODE
	if ((
	( 10#$i >= 132 && 10#$i <= 218 ) ||
	( 10#$i >= 310 && 10#$i <= 311 ) ||
	( 10#$i >= 351 && 10#$i <= 351 )
	)); then
		setup3 $i
	elif [[ $i == "0635" ]]; then
		setup2 $i
	else
		setup1 $i
	fi
	cat /tmp/rs /tmp/err > /tmp/out

	if ! test -f ../../../tests/exp/en/test${i}en.exp; then
		if ! touch ../../../tests/exp/en/test${i}en.exp; then
			exit 1
		fi
	fi

	skipcode=$(head -n1 ../../../tests/t-$1.ctr)
	if [[ "$skipcode" == "#Linux" ]]; then
		echo "SKIP Linux-only test"
		return
	fi
	code="$(< ../../../tests/t-$i.ctr)"
	observed="$(< /tmp/out)"
	expected="$(< ../../../tests/exp/en/test${i}en.exp)"
	sed '$ { /^$/d; }' ../../../tests/exp/en/test${i}en.exp > /tmp/out2
	sed '$ { /^$/d; }' /tmp/out > /tmp/out3
	
	diff="$(diff -bw /tmp/out3 /tmp/out2)"
	if [[  $diff != "" ]]; then
		echo "𐄂 test $i"
		echo $skipcode
		echo "expected:"
		echo "|$expected|"
		echo "observed:"
		echo "|$observed|"
		echo "diff:"
		diff -bw ../../../tests/exp/en/test${i}en.exp /tmp/out
		echo "code:"
		echo $code
		printf "save new test result? (y/n)"
		read answer
		if [[ $answer == "y" ]]; then
			cat /tmp/out > ../../../tests/exp/en/test${i}en.exp
			echo "recorded."
		else
			exit 1
		fi
	else
		echo "✓ test $i | $mmode"
	fi

}

# select range
FROM=1
TIL=736

cd build/OpenBSD/bin
for i in $(seq -f "%04g" $FROM $TIL);
do
	unittest $i 1
	unittest $i 4
	unittest $i 0
done
cd ../../..


