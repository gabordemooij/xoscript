#!/bin/ksh
ulimit -S -c unlimited # allow core dumps (unlike on obsd!)
gmake clean
gmake all
rm -rf /tmp/xo # remove workspace
mkdir -p /tmp/xo # create dirs
mkdir -p /tmp/xo/dicts # for dictionaries
mkdir -p /tmp/xo/mltests # for multilang tests
LANGS=$(ls ../../src/i18n)
# generate dicts
for LANG in ${LANGS};
do
	if [[ $LANG != "rules.txt" && $LANG != "en" ]]; then
		echo $LANG
		# generate core dict
		../../build/OpenBSD/bin/xo gendict.xo \
			../../src/i18n/en/dictionary.h \
			../../src/i18n/$LANG/dictionary.h \
			1>/tmp/xo/dicts/en${LANG}.dict 2>/dev/null
		# generate server dict
		../../build/OpenBSD/bin/xo gendict.xo \
			../../src/plugins/server/i18n/en/server.h \
			../../src/plugins/server/i18n/$LANG/server.h \
			1>>/tmp/xo/dicts/en${LANG}.dict 2>/dev/null
		# generate tests
		mkdir -p /tmp/xo/mltests/${LANG}
		./xotr /tmp/xo/dicts/en${LANG}.dict ../../tests/t-0001.ctr \
			1>/tmp/xo/mltests/${LANG}/t-0001.ctr 2>/dev/null
		if [ $? != 0 ]; then
			exit $?
		fi
		
		TESTS=$(ls ../../tests/t-*.ctr)
		for TEST in ${TESTS}
		do
			TFILE=${TEST##*/}
			print $TFILE
			
			
			skipcode=$(head -n1 ../../tests/${TFILE})
			if [[ "$skipcode" == *"!XOTR"* ]]; then
				print "SKIP !XOTR test"
				continue
			fi
			
			./xotr /tmp/xo/dicts/en${LANG}.dict ../../tests/${TFILE} \
			1>/tmp/xo/mltests/${LANG}/${TFILE} 2>/tmp/xo/errorlog.txt
			if [ $? != 0 ]; then
				print "Error:"
				tail /tmp/xo/errorlog.txt 
				print "Source:"
				cat ../../tests/${TFILE}
				print "Partial result:"
				cat /tmp/xo/mltests/${LANG}/${TFILE}
				exit $?
			fi
		done
		
	fi
done
