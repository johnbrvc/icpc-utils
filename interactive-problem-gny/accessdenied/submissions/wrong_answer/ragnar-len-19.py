#!/usr/bin/env python3


def query(x):
    print(x, flush=True)
    r = input()
    if r == "ACCESS GRANTED":
        exit(0)
    return int(r[15:-4])


for l in range(1, 20):
    if query("A" * l) > 5:
        break
chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

s = ["A"] * l
for i in range(l):
    times = [query("".join(s[:i] + [c] + s[i + 1 :])) for c in chars]
    j = times.index(max(times))
    s[i] = chars[j]
