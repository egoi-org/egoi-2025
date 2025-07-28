#!/usr/bin/env python3

n = int(input())

ans = []
for i in range(n):
  print("?", "0"*i + "1" + "0"*(n-i-1))
  q = int(input())
  if q == 1:
    ans.append(i)
  if len(ans) == 2:
    break

print("!", ans[0], ans[1])
