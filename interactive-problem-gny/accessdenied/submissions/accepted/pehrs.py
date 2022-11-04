#!/usr/bin/env python3
import string
import re
import sys

characters = string.ascii_uppercase + string.ascii_lowercase + string.digits

def debug(string):
    with open("/tmp/debug.txt", 'a') as f:
        f.write(string + "\n")

def write(string: str) -> int:
    assert string != "", "Attempted to send empty string"
    debug(string)
    print(string, flush=True)
    read = input()
    debug(read)
    if read == 'ACCESS GRANTED':
        sys.exit(0)
    return int(re.findall(r'\d+', read)[0])

#detect length
def get_length()->int:
    for i in range(1, 21):
        for j in characters:
            time = write(j*i)
            if time > 6:
                return i

def guess(start, length, time) -> string:
    for i in characters:
        new_time = write(start+i*(length-len(start)))
        if new_time > time:
            return start+i

length = get_length()
password = ""
time = 14

for i in range(0, length):
    password = guess(password, length, time)
    time +=9
