#!/usr/bin/env python3
import math, itertools

m, k = 46, 12
n = int(input())

blocks = []
for s in range(1,k+1):
  if k%s == 0:
    for c in range(100):
      blocks.append((math.comb(c,k//s),c,s))

par = [()]*(n+1)
dp = [0] + [1e9]*n
for i in range(n+1):
  for b,c,s in blocks:
    if i+b <= n and dp[i+b] > dp[i] + c*s:
      dp[i+b] = dp[i] + c*s
      par[i+b] = (b,c,s)

while n != 0:
  b,c,s = par[n]
  n -= b
  for t in itertools.combinations(range(c), k//s):
    print(*[x for i in t for x in range(dp[n] + s*i, dp[n] + s*(i+1))])
