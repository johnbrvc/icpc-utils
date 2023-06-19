#!/bin/bash
prog=$0

INFIFO=fin
OUTFIFO=fout
FIFOMODE=600

EXITCODE_AC=42
EXITCODE_WA=43

if test $# -lt 6
then
	echo $prog: Usage: $prog interactive-validator judgein judgeans feedbackdir result.xml command ...
	exit 1
fi

iv="$1"
judgein="$2"
judgeout="$3"
feedbackdir="$4"
resultxml="$5"
command="$6"
shift 6

sent_xml=0

GenXML()
{
	msg1="$1"
	msg2="$2"
	cat << EOF > $resultxml
<?xml version="1.0"?>
<result outcome="$msg1" security="$resultxml">$msg2</result>
EOF
	sent_xml=1
}

Cleanup()
{	
	if test -n "$intv_pid"
	then
		kill -15 $intv_pid
	fi
	if test -n "$contestant_pid"
	then
		kill -15 $contestant_pid
	fi
	rm -f $INFIFO $OUTFIFO
	exit 15
}

trap Cleanup 15

feedbackfile=$feedbackdir/judgemessage.txt

rm -f $INFIFO $OUTFIFO

if ! mkfifo --mode=$FIFOMODE $INFIFO
then
	echo $prog: Can not create $INFIFO 1>&2
	exit 2
fi
if ! mkfifo --mode=$FIFOMODE $OUTFIFO
then
	echo $prog: Can not create $INFIFO 1>&2
	exit 2
fi

echo Running: "$iv $judgein $judgeout $feedbackdir >$INFIFO < $OUTFIFO &" 1>&2
# Note: order of the redirection is important.  We want to do the output to $INFIFO first here
# since the contestant pid does the input from $INFIFO first.  This will allow that connection
# to complete, at which point it will attempt to open $OUTFIFO as input, but that will block
# until contestant pid opens that for input, which it will do right after the first is done
$iv $judgein $judgeout $feedbackdir >$INFIFO < $OUTFIFO &
intv_pid=$!
echo Validator pid $intv_pid 1>&2

# The following contestant process will be put into a sandbox governing memory and time, etc.
echo Running: "$command $* <$INFIFO >$OUTFIFO &" 1>&2
$command $* < $INFIFO >$OUTFIFO &
contestant_pid=$!
echo Contestant pid $contestant_pid 1>&2

contestant_done=0

while true
do
	wait -n -p child_pid
	wstat=$?
	if test $wstat -eq 127
	then
		echo No more children found 1>&2
		break
	fi
	if test "$child_pid" -eq "$intv_pid"
	then
		echo Validator finishes status $wstat 1>&2
		if test "$contestant_done" -eq 0
		then
			echo Contestant has not finished - killing it
			kill -9 "$contestant_pid"
		fi
		if test "$wstat" -eq $EXITCODE_AC
		then
			GenXML Accepted ""
		elif test "$wstat" -eq $EXITCODE_WA
		then
			if test -s "$feedbackfile"
			then
				GenXML "No - Wrong answer" `tail -1 $feedbackfile`
			else
				GenXML "No - Wrong answer" "No feedback file"
			fi
		else
			GenXML "Other - contact staff" "bad return code $wstat"
		fi
		break;
	fi
	if test "$child_pid" -eq "$contestant_pid"
	then
		echo Contestant finished status $wstat 1>&2
		wsubstat=$wstat
		contestant_done=1
		if test "$wstat" -ne 0
		then
			echo Contestant finished abnormally - killing validator 1>&2
			kill -9 "$intv_pid"
			GenXML "No - Run-time Error" "Exit status $wstat"
			break
		fi
	fi
done
echo All done 1>&2
rm -f $INFIFO $OUTFIFO
if test "$sent_xml" -eq 0
then
	GenXML "Other - contact staff" "unexpected runner exit"
fi

exit 0
