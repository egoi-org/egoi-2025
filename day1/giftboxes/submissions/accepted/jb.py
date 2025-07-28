#!/usr/bin/env python3

n, m = [int(x) for x in input().split()]
a = [int(x) for x in input().split()]

j, last = -1, [-1]*n
for i,x in enumerate(a):
  j = max(j, last[x])
  last[x] = i

ans = (-j,0,j)
for i,x in enumerate(a):
  if last[x] == -1:
    break
  j = max(i+1, j, last[x])
  ans = max(ans, (i-j,i+1,j))
  last[x] = -1
print(ans[1],ans[2]) if m > n else print(-1)
