#!/bin/bash
echo "****************** PC2 AUTOJUDGES ***********************"
#for j in 1 2 3 4 5 6 7 8 11 12 13 14 15 16 17 18
for j in 1 2 3
do
	echo pc2-aj$j:"------------------"
	ssh root@pc2-aj$j "dmidecode -t memory | sed -e 's/^[ \t][ \t]*//' | egrep '^(Size:|Configured Memory Speed:)'" | egrep -v "No Module|Unknown"
done

#echo "****************** PC2 CCS ADMIN ***********************"
#for j in 1 2 3 4 5 6 
#do
#	echo ccsadmin$j:"------------------" 
#	ssh root@ccsadmin$j "dmidecode -t memory | sed -e 's/^[ \t][ \t]*//' | egrep '^(Size:|Configured Memory Speed:)'" | egrep -v "No Module|Unknown"
#done
#
#echo "****************** PC2 SERVERS ***********************"
#for j in 46 47
#do
#	echo pc2-wf$j:"------------------"
#	ssh root@pc2-wf$j "dmidecode -t memory | sed -e 's/^[ \t][ \t]*//' | egrep '^(Size:|Configured Memory Speed:)'" | egrep -v "No Module|Unknown"
#done
#
#
