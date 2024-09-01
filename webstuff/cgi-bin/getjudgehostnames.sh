#!/bin/bash
HOSTS_FILE=/etc/hosts
#HOSTS_FILE=hosts.test
JUDGE_PREFIX=pc2-aj

#
# Extracts hostnames matching "$JUDGE_PREFIX" followed by numbers
JUDGE_LIST=`sed -nE -e "s/^[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}[[:space:]]+(${JUDGE_PREFIX}[0-9][0-9]*)/\1/p" ${HOSTS_FILE}`

echo "Content-type: application/json"
echo "Access-Control-Allow-Origin: *"
echo ""
echo "["
cnt=1
if test -n "$JUDGE_LIST"
then
	set $JUDGE_LIST
	numjudge=$#
	eol=","
	for judge in $*
	do
		if test $cnt -eq $numjudge
		then
			eol=""
		fi
		echo '  "'$judge'"'$eol
		cnt=$((cnt+1))
	done
fi
echo "]"
exit 0
