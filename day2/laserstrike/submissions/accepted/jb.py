#!/usr/bin/env python3

phase, n = [int(x) for x in input().split()]

#################### ALICE ####################
if phase == 1:
  g = [[] for i in range(n)]
  for i in range(n-1):
    a, b = [int(x) for x in input().split()]
    g[a].append(b)
    g[b].append(a)

  leafs = []
  leafs_hanging = [[] for i in range(n)]

  def touch(x):
    if len(g[x]) == 1:
      leafs.append(x)
      leafs_hanging[g[x][0]].append(x)

  for x in range(n):
    touch(x)

  def cut(par, leaf):
    print(leaf)
    g[par].remove(leaf)
    leafs.remove(leaf);
    touch(par)
    if len(g[par]) == 0:
      exit()

  def trim(x):
    for y in leafs_hanging[x]:
      cut(x, y)
    leafs_hanging[x].clear()

  xe = [(x,leafs_hanging[x][0]) for x in range(n) if len(leafs_hanging[x])]
  red  = sorted([(x,y) for x,y in xe if x < y])
  blue = sorted([(y,x) for x,y in xe if x > y])
  bit = len(blue) == 0 or (len(red) > 0 and red[-1] > blue[0])
  print(int(bit))

  order = red + blue if bit else blue + red
  for leaf_edge in order:
    for x in leaf_edge:
      trim(x)

  while leafs:
    trim(g[leafs[0]][0])


####################  BOB  ####################
if phase == 2:
  typ = int(input())
  seen = [0]*n
  time = 99
  last_leaf_edge = (-1,-1)
  for i in range(n-1):
    a, b = sorted([int(x) for x in input().split()])
    t = (seen[a] == time or seen[a] < seen[b] < time)
    if not seen[a] and not seen[b]:
      if (a,b) < last_leaf_edge:
        typ = not typ
      last_leaf_edge = (a,b)
      t = typ
    time += 1
    seen[a] = seen[b] = time
    print(b if t else a)
