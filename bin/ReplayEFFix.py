#!/bin/env python3
#coding: utf8

import sys
import os
import json
import operator
import datetime
import random
EVENT_FEED = "event-feed.json"

def extract_time(json):
    if "contest_time" in json :
        t = json["contest_time"]
    else :
        t = json["start_contest_time"]
    return t

def convert_millis(ms) :
    sec, msec = divmod(ms, 1000)
    mins, sec = divmod(sec, 60)
    hrs, mins = divmod(mins, 60)
    return f"{hrs:02d}:{mins:02d}:{sec:02d}.{msec:03d}"

#load json from file
lines = []
with open(EVENT_FEED, 'r') as ef :
    while True :
        line = ef.readline()
        if not line: break
        line = line.strip()
        json_obj = json.loads(line)
        if "type" in json_obj :
            t = json_obj["type"]
            if t == "submissions" :
                data_obj = json_obj["data"]
                lines.append(data_obj)
            elif t == "judgements" :
                data_obj = json_obj["data"]
                st = data_obj["start_time"] + ":00"
                tdel = datetime.timedelta(milliseconds=random.randint(20,1500))
                stiso = datetime.datetime.fromisoformat(st) + tdel
                data_obj["end_time"] = stiso.isoformat(timespec="milliseconds")
                st = data_obj["start_contest_time"]
                ms = sum(float(x) * 60 ** i for i, x in enumerate(reversed(st.split(':'))))
                ms = ms*1000 + tdel.microseconds/1000
                data_obj["end_contest_time"] = convert_millis(int(ms))
                lines.append(data_obj)

#sort json
lines.sort(key=extract_time)

#output result
print("[", end="")
sep=None
for line in lines:
    if sep != None :
        print(f"{sep}")
    print(f"{json.dumps(line)}", end="")
    sep = ","
print("]")

