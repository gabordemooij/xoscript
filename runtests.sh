#!/bin/sh

# Runs tests
# This script branches to either OBSD/Linux based on uname

OS=$(uname)
if [ "$OS" = "OpenBSD" ]; then
	# Run tests on OpenBSD
	./misc/xotest/runtests_obsd.sh
else
	# Run tests on Linux
	./misc/xotest/runtests.sh
fi
