#!/bin/bash
if test $# -ne 1
then
	echo Usage: $0 git-diff-teams2.tsv
	exit 1
fi
f=$1
echo -e "site\taccount\texternalid\tgroup\tdisplayname\tlongschoolname\tshortschoolname\tcountrycode\tinstitution\tpermdisplay\tpermlogin\tperpassword"
fromdos < $f > .teamtmp
cut -f1,2,3,5 < .teamtmp >.teamtmp1
cut -f5,6,7,8 < .teamtmp >.teamtmp2
paste .teamtmp1 .teamtmp2 | \
	sed -e 1d -e 's/^< /1\tteam/' -e 's/$/\tTRUE\tTRUE\tFALSE/'
rm .teamtmp .teamtmp1 .teamtmp2
