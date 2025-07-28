#!/usr/bin/env python3
# should solve subtask "N, M, Q ≤ 2 000 and (ri − ℓi + 1) ≤ 2 000" subtask

n, m, q = [int(x) for x in input().split()]
edges = [[int(x) for x in input().split()] for i in range(m)]
edges.sort(key=lambda x: x[2])

for i in range(q):
  l, r = [int(x) for x in input().split()]
  uf = list(range(n))
  for x in range(l,r):
    uf[x] = r
  cost = 0
  for x, y, c in edges:
    while uf[x] != x:
      uf[x] = uf[uf[x]]
      x = uf[x]
    while uf[y] != y:
      uf[y] = uf[uf[y]]
      y = uf[y]
    if x != y:
      uf[x] = y
      cost += c
  print(cost)
