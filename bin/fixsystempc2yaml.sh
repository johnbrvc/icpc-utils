#!/bin/bash
for c in 46 47
do
	for file in wf$c/*/config/system.pc2.yaml
	do
		sed -i -e 's;/home/ubuntu/pc2/current/config;/home/icpc2023/pc2/current/config;' \
			-e "s;domserver$c;domserver-wf$c;" $file
	done
done
