#!/bin/bash
cd $HOME
pids=`pgrep -u $USER java`
if test -n "$pids"
then
        echo $0: killing $pids for judges 
        kill $pids
else
        echo $0: No judge running.
fi
exit 0
