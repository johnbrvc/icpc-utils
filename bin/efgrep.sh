#!/bin/bash
if test $# -lt 1
then
	echo Usage: $0 type ...
	exit 1
fi
estr="("
for type in $*
do
	estr="$estr|$type"
done
estr="$estr)"
echo "["
egrep '"type":"'$estr'"' | sed -e 's/^.*"data"://' -e 's/},"time"[^}][^}]*}/}/' -e '$ ! s/$/,/'
echo "]"

### {"token":"337","id":"10","type":"submissions","data":{"language_id":"java","time":"2024-04-17T22:36:06.086+02:00","contest_time":"-13:23:53.914","team_id":"tobi
### ","problem_id":"turningred","files":[{"href":"contests/wf46_finals/submissions/10/files","mime":"application/zip","filename":"submission.zip"}],"id":"10","exter
### nal_id":null,"entry_point":null,"import_error":null},"time":"2024-04-17T22:36:06.099+02:00"}
### {"token":"345","id":"1","type":"judgements","data":{"max_run_time":null,"start_time":"2024-04-17T22:36:07.804+02:00","start_contest_time":"-13:23:52.195","end_t
### ime":null,"end_contest_time":null,"submission_id":"1","id":"1","valid":true,"judgement_type_id":null},"time":"2024-04-17T22:36:08.770+02:00"}
### 
