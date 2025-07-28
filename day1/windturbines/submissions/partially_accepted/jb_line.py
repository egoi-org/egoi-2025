#!/usr/bin/env python3
# should solve subtask "M = N − 1 and vi = ui + 1 for all i."

n, m, q = [int(x) for x in input().split()]
prefix = [0]*n
for i in range(m):
  x, y, c = [int(x) for x in input().split()]
  prefix[x+1] = c
for i in range(n-1):
  prefix[i+1] += prefix[i]
for i in range(q):
  l, r = [int(x) for x in input().split()]
  print(prefix[l] + prefix[-1] - prefix[r])
