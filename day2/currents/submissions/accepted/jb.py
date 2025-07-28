#!/usr/bin/env python3

n, m = [int(x) for x in input().split()]
g  = [[] for i in range(n)]
gr = [[] for i in range(n)]
for i in range(m):
  a, b = [int(x) for x in input().split()]
  g[a].append(b)
  gr[b].append(a)

def bfs(s, g, low):
  d, atdist = [-1]*n, [[] for i in range(2*n)]
  d[s] = 0
  atdist[0].append(s)
  for layer in atdist:
    for x in layer:
      for y in g[x]:
        if d[y] == -1:
          d[y] = max(low[y], d[x]+1)
          atdist[d[y]].append(y)
  return d

d0 = bfs(0,g,[0]*n)
d1 = bfs(n-1,gr,d0)
print(*d1[:-1])
