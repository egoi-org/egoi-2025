#!/usr/bin/env python3
import random

n = int(input())
pins = []
ma = 0

for _ in range(n):
    a,b = map(int,input().split())
    pins.append((a,b))

candidates = set()
for i in range(min(n,3000)):
    candidates.add(i)
    candidates.add(random.randrange(0,n))
candidates = list(candidates)

for i in candidates:
    hej = 0
    if (pins[i][0] + pins[i][1])%2 == 0:
        continue
    for j in range(n):
        if (pins[j][0]+pins[j][1]-pins[i][0]-pins[i][1])%(2*n) == 0:
            hej += 1
    ma = max(ma, hej)

print(n-ma)