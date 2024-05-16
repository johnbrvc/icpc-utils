#!/bin/bash
PATH=/usr/pc2/bin:$PATH
NOGUI=--nogui
if test $# -eq 1
then
	if test "$1" = "gui"
	then
		NOGUI=""
	fi
fi
cd $HOME
pids=`pgrep -u $USER java`
if test -n "$pids"
then
	echo $0: It looks like $USER is already running.
else
	rm -f logs/*
	j=`echo $USER | sed -e 's/judge//'`
#	nohup pc2judge --login j$j --password GNY2023Columbia $NOGUI >jlog_$j".log" 2>&1 &
       nohup pc2judge --login j$j --password $USER $NOGUI >jlog_$j".log" 2>&1 &
fi
exit 0


#!/bin/bash
# Script to start a judge instance from a remote system.  This is typically
# called by something like: ssh ubuntu@pc2judge2.icpc-vcss.org StartJudgeFromRemote 2
# That would start autojudge "judge2" in pc2.
DEBUG=

cd $HOME
PATH=/usr/pc2/bin:$PATH
NOGUI=--nogui
JUDGEPASSFILE=/home/ubuntu/pc2/judgepass.txt
if test $# -eq 1
then
	if test "$1" = "gui"
	then
		NOGUI=""
	fi
fi

pids=`pgrep -u $USER java`
if test -n "$pids"
then
	echo $0: It looks like $USER is already running.
else
	# Judge number is all non-digit chars
	j=`echo $USER | sed -e 's/^[^0-9][^0-9]*//'`
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
