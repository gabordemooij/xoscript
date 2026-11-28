#!/bin/ksh
ulimit -c 0 # avoid core dumps bc pledge/unveil

FFITESTLIB=$(ldconfig -r | awk '$3 ~ /libc\.so/ {print $3}')
export FFITESTLIB 

. misc/xotest/setup1.inc
. misc/xotest/setup2.inc
. misc/xotest/setup3.inc
. misc/xotest/setup_mapping.inc

# set malloc in security audit mode
MALLOC_OPTIONS=SCFGJ
export MALLOC_OPTIONS

CITRINE_MEMORY_LIMIT_MB=10
export CITRINE_MEMORY_LIMIT_MB

PLATFORMCODE="obsd"
export PLATFORMCODE

BUILD="${1:-build}"
MULTILANG="${2:-single}"

if [[ $MULTILANG == "multi" ]]; then
set -A LANGS es nl en
else
set -A LANGS en
fi

if [[ $BUILD == "build" ]]; then
LDFLAGS='-shared'
for ISO in ${LANGS[@]}; 
do
export ISO

SERVER="server"
if [[ $ISO == "es" ]]; then
	SERVER="servidor"
fi

make clean
EXTRACFLAGS="-D TEST -D EXPERIMENTS"
export EXTRACFLAGS
make -f makefile.obsd clean
PACKAGE="server" NAME=${SERVER} make -f makefile.obsd plugin-clean
make -f makefile.obsd
PACKAGE="server" NAME=${SERVER} make -f makefile.obsd plugin
cp build/OpenBSD/bin/xo build/OpenBSD/bin/xo$ISO #copy lang edition
done
fi

printf '%s' 'c=3&e[]=1&e[]=2&xx=1' > /tmp/xotest.txt


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
	if [[ "$skipcode" == "#Linux" ]]; then
		print "SKIP Linux-only test"
		return
	fi
	code="$(< ../../../tests/t-$i.ctr)"
	observed="$(< /tmp/out)"
	expected="$(< ../../../tests/exp/en/test${i}en.exp)"
	sed '$ { /^$/d; }' ../../../tests/exp/en/test${i}en.exp > /tmp/out2
	sed '$ { /^$/d; }' /tmp/out > /tmp/out3
	
	diff="$(diff -bw /tmp/out3 /tmp/out2)"
	if [[  $diff != "" ]]; then
		print "[fail] test $i"
		print $skipcode
		print "expected:"
		print "|$expected|"
		print "observed:"
		print "|$observed|"
		print "diff:"
		diff -bw ../../../tests/exp/en/test${i}en.exp /tmp/out
		print "code:"
		print $code
		printf "save new test result? (y/n)"
		read answer
		if [[ $answer == "y" ]]; then
			cat /tmp/out > ../../../tests/exp/en/test${i}en.exp
			print "recorded."
		else
			exit 1
		fi
	else
		print "[pass] test $i | $mmode"
	fi
}

# select range
FROM=1
TIL=822

cd build/OpenBSD/bin
for i in $(seq -f "%04g" $FROM $TIL);
do
	unittest $i 1
	unittest $i 4
	unittest $i 0
done
cd ../../..


