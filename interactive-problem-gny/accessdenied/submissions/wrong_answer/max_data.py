#!/usr/bin/env python3
import sys
import string
import random

alpha = string.ascii_lowercase + string.ascii_uppercase + string.digits
for i in range(2501):
    print(''.join( random.choice(alpha) for _ in range(20) ))

