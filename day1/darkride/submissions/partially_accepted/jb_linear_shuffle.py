#!/usr/bin/env python3

import random
random.seed(40)

n = int(input())
perm = list(range(n))
random.shuffle(perm)

ans = []
for i in perm:
  print("?", "0"*i + "1" + "0"*(n-i-1))
  q = int(input())
  if q == 1:
    ans.append(i)
  if len(ans) == 2:
    break

print("!", ans[0], ans[1])
