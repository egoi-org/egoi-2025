from collections import defaultdict, Counter, deque, namedtuple
from copy import copy, deepcopy
import math
import bisect as bis
import random as rand
import heapq as hq
import itertools as it
import functools as ft
import os
import random
import sys
import time

# caves notes

# visual example for the case of a,b and b,a both being present
# if dir reversal happens when we are at cave 0, we cant get out, correct?
# at most one direction reversal  ( may also not happen )
# definitely reach an exit, which can be exited from
# you exit immediately in 0 seconds, why not have this in examples, n-1 always=0
# 6 groups

print = lambda x: sys.stdout.write(str(x) + "\n")
input = lambda: sys.stdin.readline().strip()

def get_psum(psums, l, r):
    if l == 0:
        return psums[r]
    return psums[r] - psums[l-1]

def dj(gr, n, start):

    q = []
    dists = [2*n] * n
    dists[start] = 0
    hq.heappush(q, (0, start))
    while q:
        dist, curr = hq.heappop(q)
        if dists[curr] < dist:
            continue
        for ch in gr[curr]:
            cand = dist + 1
            if cand < dists[ch]:
                dists[ch] = cand
                hq.heappush(q, (cand, ch))

    return dists

t = 1

for _ in range(t):
    n, m = map(int, input().split())
    g = [[] for i in range(n)]
    rg = [[] for i in range(n)]

    for _ in range(m):
         a, b = map(int, input().split())
         g[a].append(b)
         rg[b].append(a)

    rdist = dj(g, n, 0)
    #print(rdist)

    q = []

    res = [2*n] * n
    res[-1] = 0
    #print(rg)
    for ch in rg[n-1]:
        hq.heappush(q, (1, ch))

    while q:
        #print(res)
        preval, curr = hq.heappop(q)
        if res[curr] < preval:
            continue
        cand1 = rdist[curr]
        cand2 = preval
        res[curr] = max(cand1, cand2)
        for ch in rg[curr]:
            cand = res[curr] + 1
            if cand >= res[ch]:
                continue
            res[ch] = cand
            hq.heappush(q, (cand, ch))


    print(" ".join([str(x) for x in res[:-1]]))



