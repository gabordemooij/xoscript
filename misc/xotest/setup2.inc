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
