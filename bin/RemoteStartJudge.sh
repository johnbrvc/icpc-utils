#!/bin/bash
PATH=/usr/pc2/bin:$PATH
NOGUI=--nogui
if test $# -eq 0
then
	echo $0: Usage is: $0 judge-num '[gui]'
	exit 1
fi
judge=$1
if test $# -eq 2
then
        if test "$2" = "gui"
        then
                NOGUI=""
        fi
fi
cd $HOME
pids=`pgrep -u $USER java`
if test -n "$pids"
then
        echo $0: It looks like judge $judge is already running.
else
        rm -f logs/*
        nohup pc2judge --login j$judge --password judge$judge $NOGUI >jlog_$judge".log" 2>&1 &
fi
exit 0

