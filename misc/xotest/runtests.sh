#!/bin/bash
ulimit -S -c unlimited # allow core dumps (unlike on obsd!)

FFITESTLIB=$(ldconfig -p | awk '$NF ~ /.*x86.*libc\.so/ {print $NF}') 
export FFITESTLIB

. misc/xotest/setup1.inc
. misc/xotest/setup2.inc
. misc/xotest/setup3.inc
. misc/xotest/setup_mapping.inc

CITRINE_MEMORY_LIMIT_MB=10
export CITRINE_MEMORY_LIMIT_MB

PLATFORMCODE="lin64"
export PLATFORMCODE

BUILD="${1:-build}"

if [[ $BUILD == "build" ]]; then

LDFLAGS='-shared'
ISO="en" 
export ISO

EXTRACFLAGS="-D TEST -D EXPERIMENTS"
export EXTRACFLAGS
make clean ; make
PACKAGE="server"
export PACKAGE
make plugin-clean
NAME="server" make plugin

fi

unittest() {
	i=$1
	mmode=$2
	CITRINE_MEMORY_MODE=$mmode
	export CITRINE_MEMORY_MODE
	setup_mapping $i
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
		echo "[fail] test $i"
		echo $skipcode
		echo "expected:"
		echo "|$expected|"
		echo "observed:"
		echo "|$observed|"
		echo "diff:"
		diff -bBZ ../../../tests/exp/en/test${i}en.exp /tmp/out
		echo "code:"
		echo $code
		read -p "save new test result? (y/n)" answer </dev/tty
		if [[ $answer == "y" ]]; then
			cat /tmp/out > ../../../tests/exp/en/test${i}en.exp
			echo "recorded."
		else
			exit 1
		fi
	else
		echo "[pass] test $i | $mmode"
	fi
}

# select range
FROM=1
TIL=822

# run tests for linux
pushd build/Linux/bin
for i in $(seq -f "%04g" $FROM $TIL);
do
	unittest $i 1
	unittest $i 4
	unittest $i 0
done
popd


