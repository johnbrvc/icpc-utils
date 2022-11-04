#!/bin/bash
#
# Purpose: Start a pc2 server into background capture any console log to a log file
# laned@ecs.csus.edu
# Tue 16 Feb 2021 12:14:25 AM UTC
#

LOGFILE=pc2v9.console.$$.log

#
# CDP is the CDP location/directory config info to load into pc2 server
#
# CDP=sumitMTC
#
# feb 13 contest
# CDP=conn6testFeb13
#
# Pac NW Contest practice
CDP=PacificNWReal2020

# /home/ubuntu/repos/ccsconfig-bapc2022/bapc2022/contest.yaml
CDP=/home/ubuntu/repos/ccsconfig-bapc2022/bapc2022

#nohup pc2server --nogui --login s --load $CDP --contestpassword contest > $LOGFILE &
nohup pc2server --login s --load $CDP --contestpassword contest > $LOGFILE &

# eof start.server.sh

