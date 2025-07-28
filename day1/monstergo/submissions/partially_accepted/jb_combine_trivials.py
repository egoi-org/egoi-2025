#!/usr/bin/env python3
import math, itertools

sol = {}
for i in range(5):
  for j in range(5):
    s = []
    k = 0
    for t in range(i):
      s.append(list(range(k,k+12)))
      k += 12
    for t in range(j):
      for a in range(13):
        s.append([x+k for x in range(13) if x != a])
      k += 13
    sol[len(s)] = s

for s in sol[int(input())]:
  print(*s)
