#!/usr/bin/env python3
# @EXPECTED_GRADES@ WA AC WA

phase, n = [int(x) for x in input().split()]

#################### ALICE ####################
if phase == 1:
  deg, xors = [0]*n, [0]*n
  for i in range(n-1):
    a, b = [int(x) for x in input().split()]
    xors[a] ^= b
    xors[b] ^= a
    deg[a] += 1
    deg[b] += 1
  x = deg.index(1)
  print(1 if x > xors[x] else 0)
  for i in range(n-1):
    print(x)
    xors[xors[x]] ^= x
    x = xors[x]

####################  BOB  ####################
if phase == 2:
  typ = int(input())
  x, y = [int(a) for a in input().split()]
  p = (min if typ else max)(x,y)
  print(p ^ x ^ y)
  for i in range(n-2):
    x, y = [int(a) for a in input().split()]
    p ^= x^y
    print(p ^ x ^ y)
