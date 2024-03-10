#!/bin/bash
# Script to start a judge instance from a remote system.  This is typically
# called by something like: ssh ubuntu@pc2judge2.icpc-vcss.org StartJudgeFromRemote 2
# That would start autojudge "judge2" in pc2.
DEBUG=

cd $HOME/pc2
PATH=/usr/pc2/bin:$PATH
NOGUI=--nogui
JUDGEPASSFILE=/home/ubuntu/pc2/judgepass.txt
if test $# -ne 1
then
	echo $0: Must supply the autojudge number to start
	exit 1
fi
j=$1
if test "$j" -lt 1 -o "$j" -gt 5
then
	echo $0: Invalid autojudge number $j
	exit 2
fi

pids=`pgrep -u $USER java`
if test -n "$pids"
then
	echo $0: It looks like $USER is already running.
else
	if test -s "$JUDGEPASSFILE"
	then
		PASS="--password "`cat $JUDGEPASSFILE`
	else
		PASS=""
	fi
	rm -f logs/* 
	rm -rf executesite*
	$DEBUG nohup pc2judge --login j$j $PASS $NOGUI >jlog_$j".log" 2>&1 &
fi
exit 0
