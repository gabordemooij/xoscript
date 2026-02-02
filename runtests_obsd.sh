#!/bin/bash
#set -x
#set -v
ulimit -S -c unlimited

CITRINE_MEMORY_LIMIT_MB=10
export CITRINE_MEMORY_LIMIT_MB

BUILD="${1:-build}"

if [[ $BUILD == "build" ]]; then
LDFLAGS='-shared'
ISO="en" 
export ISO
gmake clean ; gmake
EXTRACFLAGS="-D TEST"
gmake -f makefile.obsd clean
PACKAGE="server" NAME="server.so" gmake -f makefile.obsd plugin-clean
gmake -f makefile.obsd
PACKAGE="server" NAME="server.so" gmake -f makefile.obsd plugin
fi


unittest() {
	i=$1
	mmode=$2
	CITRINE_MEMORY_MODE=$mmode
	export CITRINE_MEMORY_MODE
	
	
	if [[ $i == "0635" ]]; then
		BOUNDARY='------------------------abcdef1234567890'
		BODY=$(printf -- '--%s\r\nContent-Disposition: form-data; name="c"\r\n\r\n2\r\n--%s\r\nContent-Disposition: form-data; name="file"; filename="hello.txt"\r\nContent-Type: text/plain\r\n\r\nhello file\r\n--%s--\r\n' "$BOUNDARY" "$BOUNDARY" "$BOUNDARY")
		printf '%s' "$BODY" | \
		CONTENT_TYPE="multipart/form-data; boundary=$BOUNDARY" \
		CONTENT_LENGTH=${#BODY} \
		REQUEST_METHOD=POST \
		./xo ../../../tests/t-$i.ctr 1>/tmp/rs 2>/tmp/err
	else
		REQUEST_METHOD="POST" \
		CONTENT_TYPE="application/x-www-form-urlencoded" \
		CONTENT_LENGTH=20 \
		QUERY_STRING="a=2&b=4&d[]=a&d[]=b&f[]=1&f[]=2" \
		HTTP_COOKIE="xsid=abc123" \
		FFITESTLIB="/usr/lib/libc.so.102.0" \
		./xo ../../../tests/t-$i.ctr 1>/tmp/rs 2>/tmp/err < <(echo -n 'c=3&e[]=1&e[]=2&xx=1')
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
TIL=653

# run tests for linux
pushd build/OpenBSD/bin
for i in $(seq -f "%04g" $FROM $TIL);
do
    unittest $i 1
    unittest $i 4
    unittest $i 0
done
popd


