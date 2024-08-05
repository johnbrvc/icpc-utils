#!/bin/bash
cd $HOME
pids=`pgrep -U $USER -f "Starter --login j"`
if test -n "$pids"
then
	echo $0: killing $pids for $USER
	kill $pids
else
	echo $0: No $USER running.
fi
exit 0
