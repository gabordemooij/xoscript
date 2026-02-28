#!/bin/bash
#set -x
#set -v
ulimit -S -c unlimited

CITRINE_MEMORY_LIMIT_MB=10
export CITRINE_MEMORY_LIMIT_MB

PLATFORMCODE="lin64"
export PLATFORMCODE

BUILD="${1:-build}"

if [[ $BUILD == "build" ]]; then

LDFLAGS='-shared'
ISO="en" 
export ISO

make clean ; make
EXTRACFLAGS="-D TEST"
PACKAGE="server"
export EXTRACFLAGS
export PACKAGE
make plugin-clean
NAME="libctrserver.so" make plugin

fi

setup1() {
	i=$1
	REQUEST_METHOD="POST" \
	CONTENT_TYPE="application/x-www-form-urlencoded" \
	CONTENT_LENGTH=20 \
	QUERY_STRING="a=2&b=4&d[]=a&d[]=b&f[]=1&f[]=2" \
	HTTP_COOKIE="xsid=abc123" \
	FFITESTLIB="/usr/lib/x86_64-linux-gnu/libc.so.6" \
	./xo ../../../tests/t-$i.ctr 1>/tmp/rs 2>/tmp/err < <(echo -n 'c=3&e[]=1&e[]=2&xx=1')
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

unittest() {
	i=$1
	mmode=$2
	os=$3
	CITRINE_MEMORY_MODE=$mmode
	export CITRINE_MEMORY_MODE
	if [[ $i == "0635" ]]; then
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

	if [[ "$skipcode" == "#OBSD" ]]; then
		echo "SKIP OBSD-only test"
		return
	fi

	code="$(< ../../../tests/t-$i.ctr)"
	observed="$(< /tmp/out)"
	expected="$(< ../../../tests/exp/en/test${i}en.exp)"
	diff="$(diff -bBZ /tmp/out ../../../tests/exp/en/test${i}en.exp)"
    if [[  $diff != "" ]]; then
		echo "𐄂 test $i"
		echo $skipcode
		echo "expected:"
		echo "|$expected|"
		echo "observed:"
		echo "|$observed|"
		echo "diff:"
		diff -bBZ ../../../tests/exp/en/test${i}en.exp /tmp/out
		echo "code:"
		echo $code
		read -p "save new test result? (y/n)" answer
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
TIL=675

# run tests for linux
pushd build/Linux/bin
for i in $(seq -f "%04g" $FROM $TIL);
do
    unittest $i 1
    unittest $i 4
    unittest $i 0
done
popd


