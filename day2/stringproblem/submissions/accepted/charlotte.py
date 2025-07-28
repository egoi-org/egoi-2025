#!/bin/python3

N = int(input())

hair_adj = [(0,0) for i in range(2*N)]
hairs = []
for i in range(N):
    a,b = map(int,input().split())
    hair_adj[a] = [b,i]
    hair_adj[b] = [a,i]
    hairs.append((a,b))
c = [0 for _ in range(2*N)]

for h in hairs:
    if (h[1]-h[0])%2==0:
        continue
    d = (h[1]-h[0] -1)//2
    c[h[0]+d]+= 1
    
m = 0
mi = 0

def new_i(i):
    return (i-mi)%(2*N)
def old_i(i):
    return (i+mi)%(2*N)
def p(i):
    return old_i((2*N-(new_i(i)-1))%(2*N))

for i in range(N):
    if c[i]+c[i+N] > m:
        m  = c[i]+c[i+N]
        mi = i

print(N-m)

seen = [0 for _ in range(2*N)]
moves = []
for v in range(2*N):
    if seen[v]:
        continue
    i = v

    while hair_adj[i][0] != p(i) and not seen[i]:
        print(hair_adj[i][1],hair_adj[i][0],p(i))
        seen[p(i)] = 1
        seen[i] = 1
        i = hair_adj[p(i)][0]




