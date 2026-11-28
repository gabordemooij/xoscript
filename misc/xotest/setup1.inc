
setup1() {
	printf '%s' 'c=3&e[]=1&e[]=2&xx=1' > /tmp/xotest.txt
	i=$1
	REQUEST_METHOD="POST" \
	CONTENT_TYPE="application/x-www-form-urlencoded" \
	CONTENT_LENGTH=20 \
	QUERY_STRING="a=2&b=4&d[]=a&d[]=b&f[]=1&f[]=2" \
	HTTP_COOKIE="xsid=abc123" \
	FFITESTLIB=$(ldconfig -r | awk '$3 ~ /libc\.so/ {print $3}') \
	./xo ../../../tests/t-$i.ctr 1>/tmp/rs 2>/tmp/err < /tmp/xotest.txt
}
