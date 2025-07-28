#!/usr/bin/env python3
import math, itertools

m, k = 46, 12
n = int(input())

blocks = []
for s in range(1,k+1):
  if k%s == 0:
    for c in range(100):
      blocks.append((math.comb(c,k//s),c,s))

# also add the complement of the affine plane of order 3
affine = ['001111110', '010111101', '011001111', '011110011', '100110111', '101011011', '101101101', '110011110', '110101011', '111010101', '111100110', '111111000']
blocks.append((len(affine),-1,-9*k//6))

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
  if c > 0:
    for t in itertools.combinations(range(c), k//s):
      print(*[x for i in t for x in range(dp[n] + s*i, dp[n] + s*(i+1))])
  else:
    for a in affine:
      print(*[x for i in range(9) if a[i]=='1' for x in [dp[n]+2*i, dp[n]+2*i+1]])


