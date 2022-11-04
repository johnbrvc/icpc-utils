#!/usr/bin/env python3
import string
c,r,v = string.ascii_letters+string.digits,[],5
def read(s): return int('0'+input(''.join([c[i] for i in s]+['\n']))[15:-4])
while v==5:
    r.append(0)
    v = read(r)
while v:
    r[(v-14)//9] += 1
    v = read(r)
