#!/bin/bash

# CUSTOMIZE START
YEAR=2023
start_dir=~/pc2
html_dir=/home/ubuntu/pc2/wti/WebTeamInterface-1.1/WebContent/WTI-UI/scoreboard
# CUSTOMIZE DONE

stage_dir=$html_dir/staging

umask 022
while [ 1 ]; do
  echo -n `date` copying html from $html_dir
  rm $stage_dir/*.html
  cp $html_dir/*.html $stage_dir/
  cd $stage_dir
  for f in *.html ; do
    j=`echo $f | sed 's/ /_/g'`
    mv -n "$f" $j
    sed -i -e 's/ - /_-_/' -e 's/British Columbia/British_Columbia/' $j
  done
# prompt replaced with -i
  cat >/tmp/ftp.score <<EOM
open ftp.acmicpc-pacnw.org
binary
cd scoreboard
cd $YEAR
mput *.html
EOM
#  for f in *.html ; do echo put \"$f\" >> /tmp/ftp.score; done
  cat >>/tmp/ftp.score <<EOM
bye
EOM
  (cd $stage_dir; ftp -i |grep -v Interactive) < /tmp/ftp.score
  echo -n .
  cd $start_dir
  echo done at `date`.
  sleep 30
done
