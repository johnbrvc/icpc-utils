#!/bin/bash
if test $# -ne 2
then
	echo Usage: $0 problemid testcase'#'
	exit 1
fi
if test ! -s sandbox.log
then
	echo There is no sandbox.log file.  This the file produced by judging.
	exit 6
fi
cmd=`egrep -m 1 "^Executing setsid taskset" < sandbox.log | sed -n -e 's/^Executing setsid taskset 0x[0-9a-fA-F][0-9a-fA-F]* \(.*\)/\1/p'`
if test -z "$cmd"
then
	echo Could not find the submission to execute command in sandbox.log
	exit 7
fi

prob=$1
testcase=$2
probdir=$HOME/pc2/current/config/$prob
probfile=$probdir/problem.yaml
if test ! -d $probdir
then
	echo $prob is not a valid problem id
	exit 2
fi
datadir=$HOME/pc2/current/config/$prob/data
sampdir=$datadir/sample
secretdir=$datadir/secret
if test ! -d $sampdir
then
	echo $sampdir does not exist.
	exit 3
fi
if test ! -d $secretdir
then
	echo $secretdir does not exist.
	exit 4
fi
custom=`egrep "^validation:.*custom" $probfile`
find $sampdir -name '*.in' | sort > /tmp/.samps
find $secretdir -name '*.in' | sort > /tmp/.secrets
cat /tmp/.samps /tmp/.secrets > /tmp/.alldata
nsamp=`wc -l </tmp/.samps`
nsecret=`wc -l </tmp/.secrets`
#license: permission
#
#sandbox-type: PC2_INTERNAL_SANDBOX
#
#limits:
#   timeout: 7
#   memory: 2048
#   time_multiplier: 1.55
#   safety_margin: 1.8

timelim=`sed -n -e 's/^  *timeout: *\([0-9][0-9]*\)/\1/p' < $probfile`
if test -z "$timelim"
then
	timelim=`cat $probdir/.timelimit`
	if test -z "$timelim"
	then
		echo Can not find timelimit for problem $prob
		exit 5
	fi
fi
memlim=`sed -n -e 's/^  *memory: *\([0-9][0-9]*\)/\1/p' < $probfile`
if test -z "$memlim"
then
	echo Using default memory limit of 2048 since I can not find it in the $probfile
	memlim=2048
fi

#echo $nsamp samples and $nsecret secret timelim=$timelim memlim=$memlim cmd=$cmd
# Handle non-interactive
if test -z "$custom"
then
	infile=`sed -n "$testcase"p < /tmp/.alldata`
	databasename=`basename $infile`
	ansfile=${infile/.in/.ans}
	locinfile=${databasename}
	locansfile=${databasename/.in/.ans}
	tryfile=${databasename/.in/.try}
	echo For testcase $testcase:
	echo "    " Copying the following Input file: $infile to current folder $locinfile
	cp $infile .
	echo "    " The "judge's" answer file: $ansfile to current folder $locansfile
	cp $ansfile .
	echo "    " Using the following output/answer file: $tryfile
	echo "    " Executing: "./pc2sandbox.sh $memlim $timelim $cmd < $locinfile >$tryfile"
	echo "_____________________________________"
	./pc2sandbox.sh $memlim $timelim $cmd < $locinfile >$tryfile
	if ! diff -w $tryfile $locansfile
	then
		echo '***** OUTPUT DIFFERS FROM JUDGES *****'
	fi
	tail -7 sandbox.log
else
	echo "This is an interactive problem."
fi
	

