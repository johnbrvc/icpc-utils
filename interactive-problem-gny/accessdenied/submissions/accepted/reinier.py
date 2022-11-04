#!/usr/bin/env python3

def get_input(s):
	print(s, flush=True)
	a = input().split()
	if a[1][0] == "G":
		return -1
	else:
		return int(a[2][1:])

chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"
def to_string(a):
	return "".join(chars[c] for c in a)

done = False
for s in range(1, 21):
	r = get_input("A"*s)
	if r < 0:
		done = True
		break
	elif r > 5:
		break

while(not done):
	ans = [0]*s
	last_res = get_input(to_string(ans))
	for i in range(s):
		if (last_res < 0 or done):
			done = True
			break
		while last_res <= 9*i+14:
			ans[i] += 1
			last_res = get_input(to_string(ans))
			if (last_res < 0):
				done = True
				break

	
