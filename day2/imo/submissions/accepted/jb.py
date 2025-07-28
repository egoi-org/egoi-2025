#!/usr/bin/env python3

# should run in O(n*m + k*m^3) time, with okay-ish constant
n, m, k = [int(x) for x in input().split()]
a = [[int(x) for x in input().split()] for i in range(n)]
score = [sum(ai) for ai in a]
order = sorted(list(range(n)), key = lambda x: (score[x],-x))

dp, low_dp, high_dp = [0], 0, 0

for i, x in enumerate(order):
  low = score[order[i-1]] + (x > order[i-1]) if i else 0
  high = score[order[i+1]] - (x < order[i+1]) if i+1 < n else m*k
  assert low <= score[x] <= high

  kk = min(m, (high-low+1)//k)
  if kk == 0: # slight speedup, skip handling too small intervals
    dp, low_dp, high_dp = [dp[-1]], score[x], score[x]
    continue

  knapsack = [[0]*(high-score[x]+1) for j in range(kk+1)]
  knapsack[0][0] = 1
  for j in range(m):
    for s in reversed(range(len(knapsack)-1)):
      for sc in range(len(knapsack[0])-k+a[x][j]):
        knapsack[s+1][sc+k-a[x][j]] |= knapsack[s][sc]

  need_extra = (i and x > order[i-1])

  ndp = [0]*(high-score[x]+1)
  for s in range(kk+1):
    for sc in range(len(knapsack[0])):
      if knapsack[s][sc]:
        end = score[x] + sc
        start = score[x] + sc - s*k
        if start < low or end > high:
          continue
        dp_idx = min(start-need_extra, high_dp) - low_dp
        assert 0 <= dp_idx < len(dp)
        ndp[sc] = max(ndp[sc], dp[dp_idx] + s)

  for t in range(len(ndp)-1):
    ndp[t+1] = max(ndp[t+1], ndp[t])
  dp, low_dp, high_dp = ndp, score[x], high

print(n*m-dp[-1])
