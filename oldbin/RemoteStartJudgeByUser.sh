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

