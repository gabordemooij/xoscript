
setup_mapping() {
	i=$1
	if ((
	( 10#$i >= 132 && 10#$i <= 218 ) ||
	( 10#$i >= 310 && 10#$i <= 311 ) ||
	( 10#$i >= 351 && 10#$i <= 351 )
	)); then
		setup3 $i
	elif [[ $i == "0635" ]]; then
		setup2 $i
	else
		setup1 $i
	fi
}
