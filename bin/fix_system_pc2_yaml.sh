#!/bin/bash
for file in *
do
	cfg=$file/config
	if test -d $cfg
	then
		id=`sed -nE -e 's/^id:[[:space:]]+//p' $cfg/contest.yaml`
		syspc2yaml=$cfg/system.pc2.yaml
		sed -e "s/^ccs-password.*/ccs-password: pusher-upper-crier-purple/" \
		    -e "s;^ccs-url.*;ccs-url: https://domjudge.nac.icpc.global/api/contests/$id;" \
		    -e "s/^max-output-size-K.*/max-output-size-K: 8192/" \
			-e "s/number: 2,3$/number: 2,3,4,5,6,7,8/" \
		    -e "s/1,2,3,4,5,6,7,8/&,9,10/" \
			-e "s/count: 6$/count: 10/" \
		    -e "/^max-output-size-K:/a\
memory-limit-in-Meg: 2048\
" \
            -e "/^permissions:/a\
# domjudge admins\n\
  - account: ADMINISTRATOR\n\
    number: 9,10\n\
    disable: EDIT_RUN,ADD_ACCOUNT,EDIT_ACCOUNT,JUDGE_RUN,REJUDGE_RUN,EDIT_LANGUAGE,EDIT_PERMISSIONS,EDIT_PROBLEM,ALLOWED_TO_AUTO_JUDGE,RESET_CONTEST,SWITCH_PROFILE,EDIT_JUDGEMENTS,SHUTDOWN_SERVER\
"  < $syspc2yaml >$syspc2yaml.new
	cat $syspc2yaml.new > $syspc2yaml
	rm $syspc2yaml.new
	fi
done
