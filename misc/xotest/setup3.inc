setup3() {
	i=$1
	CITRINE_MEMORY_PROFILE=1 \
	./xo ../../../tests/t-$i.ctr 1>/tmp/rs 2>/tmp/err
}
