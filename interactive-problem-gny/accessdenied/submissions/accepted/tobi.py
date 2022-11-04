#!/usr/bin/env python3
import random
import sys

chars = [chr(i) for i in list(range(ord('A'),ord('Z')+1)) + list(range(ord('a'),ord('z')+1))] + [str(i) for i in range(0,10)]
random.shuffle(chars)

def interact():
    print(''.join(answer), flush=True)
    line = sys.stdin.readline().strip()
    if line == 'ACCESS GRANTED':
        sys.exit(0)
    return (int)(line[15:].split()[0])

for i in range(1,21):
    answer = ['a' for _ in range(0,i)]
    if interact() > 5:
        break

for i in range(0,len(answer)):
    best = -1, ' '
    for c in chars:
        answer[i] = c
        timing = interact()
        if timing > best[0]:
            best = timing, c
    answer[i] = best[1]
