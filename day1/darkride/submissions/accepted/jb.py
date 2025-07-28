#!/usr/bin/env python3

n = int(input())

def query(r):
  r = set(r)
  print("?", *["01"[i in r] for i in range(n)])
  return int(input()) % 2

xor = 0
for bit in range(100):
  q = [i for i in range(n) if i >> bit & 1]
  if q and query(q):
    xor |= 1 << bit

q = [i for i in range(n) if i < (i ^ xor)]
while len(q) > 1:
    mid = len(q) // 2
    q = q[:mid] if query(q[:mid]) else q[mid:]

print('!', q[0], q[0]^xor)
