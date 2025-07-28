#!/usr/bin/env python3

# UF, FenwickTree, RMQ, and LCA from https://github.com/cheran-senthil/PyRival
class UnionFind:
  def __init__(self, n):
    self.parent = list(range(n))

  def find(self, a):
    acopy = a
    while a != self.parent[a]:
      a = self.parent[a]
    while acopy != a:
      self.parent[acopy], acopy = a, self.parent[acopy]
    return a

  def union(self, a, b): # must have self.find(b) = b
    self.parent[b] = a

class FenwickTree:
  def __init__(self, n):
    self.bit = [0]*n
    self.n = n

  def update(self, idx, x):
    while idx < self.n:
      self.bit[idx] += x
      idx |= idx + 1

  def query(self, end):
    x = 0
    while end:
      x += self.bit[end - 1]
      end &= end - 1
    return x

class RangeQuery:
  def __init__(self, data):
    self._data = _data = [list(data)]
    i, n = 1, len(_data[0])
    while 2 * i <= n:
      prev = _data[-1]
      _data.append([min(prev[j], prev[j + i]) for j in range(n - 2 * i + 1)])
      i <<= 1

  def query(self, begin, end):
    depth = (end - begin).bit_length() - 1
    return min(self._data[depth][begin], self._data[depth][end - (1 << depth)])

class LCA:
  def __init__(self, root, graph):
    self.time = [-1] * len(graph)
    self.path = [-1] * len(graph)
    P = [-1] * len(graph)
    t = -1
    dfs = [root]
    while dfs:
      node = dfs.pop()
      self.path[t] = P[node]
      self.time[node] = t = t + 1
      for nei in graph[node]:
        P[nei] = node
        dfs.append(nei)
    self.rmq = RangeQuery(self.time[node] for node in self.path)

  def __call__(self, a, b):
    if a == b:
        return a
    a = self.time[a]
    b = self.time[b]
    if a > b:
        a, b = b, a
    return self.path[self.rmq.query(a, b)]

##### main solution begins here #####

n, m, q  = [int(x) for x in input().split()]
edges = [(i,i+1,int(1e12)) for i in range(n-1)]
for i in range(m):
  edges.append([int(x) for x in input().split()])
edges.sort(key=lambda x: x[2])

uf = UnionFind(n)
root = [i for i in range(n)]
weight = [0]*(2*n-1)
childs = [[] for i in range(2*n-1)]
rt = n-1

for x, y, w in edges:
  x = uf.find(x)
  y = uf.find(y)
  if x == y:
    continue
  uf.union(x,y)
  rt += 1
  childs[rt] = [root[x], root[y]]
  weight[rt] = w
  root[x] = root[y] = rt

cost = sum(weight)

leaf_chain = [n]*len(childs)
lca = LCA(rt, childs)
fw = FenwickTree(n)

def activate(x):
  r = rt
  while leaf_chain[r] != n:
    y = leaf_chain[r]
    z = lca(x,y)
    zy, zx = childs[z]
    if lca.time[x] >= lca.time[zy]:
      zx, zy = zy, zx
    fw.update(leaf_chain[zx],-weight[z])
    fw.update(y,weight[z])
    leaf_chain[zy] = y
    leaf_chain[r] = n
    r = zx
  leaf_chain[-1] = x

qr, ans = [0]*q, [0]*q
queries_at_l = [[] for i in range(n)]

for i in range(q):
  ql, qr[i] = [int(i) for i in input().split()]
  queries_at_l[ql].append(i)

for l in reversed(range(n)):
  activate(l)
  for i in queries_at_l[l]:
    ans[i] = cost - fw.query(qr[i]+1)

print(*[a for a in ans])

