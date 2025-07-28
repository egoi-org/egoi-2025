#!/usr/bin/env python3

import random
n = int(input())

random.seed(43)
perm = list(range(0,n,+2))
random.shuffle(perm)

# assumes they are adjacent and only uses n/2 queries if this is the case
for i in perm:
  print("?", "0"*i + "1" + "0"*(n-i-1))
  q = int(input())
  if q == 1:
    j = (i+1)%n
    print("?", "0"*j + "1" + "0"*(n-j-1))
    q = int(input())
    if q == 1:
      print("!", i, (i+1)%n)
    else:
      print("!", i, (i-1+n)%n)
    exit()
