#!/bin/bash
# Script to start a judge instance from a remote system.  This is typically
# called by something like: ssh ubuntu@pc2judge2.icpc-vcss.org StartJudgeFromRemote 2
# That would start autojudge "judge2" in pc2.
DEBUG=

cd $HOME/pc2
PATH=/usr/pc2/bin:$PATH
NOGUI=--nogui
JUDGEPASSFILE=/home/ubuntu/pc2/judgepass.txt
if test $# -eq 0
then
	echo $0: Usage: $0 judgenumber "[gui]"
	exit 1
fi
j=$1
if test $# -ge 2
then
        if test "$2" = "gui"
        then
                NOGUI=""
        fi
fi
if test "$j" -lt 1 -o "$j" -gt 20
then
	echo $0: Invalid autojudge number $j
	exit 2
fi

pids=`pgrep -U $USER -f "Starter --login j"`
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
