#!/bin/sh
rm /tmp/xin
rm /tmp/xout
mkfifo /tmp/xin
mkfifo /tmp/xout
./xocl </tmp/xin 1>/tmp/xout &
exec 3>/tmp/xin
curl $YOUR_URL > /tmp/html
cat /tmp/html
xsltproc $XSL_PATH /tmp/html 1>&3
while IFS= read -r JSON_LINE
do
	if printf '%s' "$JSON_LINE" | jq -e '.submit == "exit"' >/dev/null; then
		echo "exit"
		exit
	fi
	POSTDATA=$(
		printf '%s' "$JSON_LINE" |
		jq -r '
			to_entries
			| map(
				(.key | @uri) + "=" +
				(.value | tostring | @uri)
			  )
			| join("&")
		'
	)
	curl -v \
	-fsS \
	-X POST \
	-H 'Content-Type: application/x-www-form-urlencoded' \
	--data "$POSTDATA" \
	$YOUR_URL > /tmp/html
	xsltproc $XSL_PATH /tmp/html > /tmp/xin
done < /tmp/xout
exec n<&-
