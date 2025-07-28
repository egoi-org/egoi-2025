#!/bin/python3


N = int(input())

hairs = []
for i in range(N):
    a,b = map(int,input().split())
    hairs.append((min(a,b),max(a,b),i))

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
    return (2*N-(i-1))%(2*N)

for i in range(N):
    if c[i]+c[i+N] > m:
        m  = c[i]+c[i+N]
        mi = i

h2 = [(min(new_i(h[0]),new_i(h[1])),max(new_i(h[0]),new_i(h[1])),h[2]) for h in hairs]
h2.sort()

moves = []
for h in h2:
    if h[0]>0 and h[0]<=N:
        if old_i(h[1]) != old_i(p(h[0])):
            moves.append((h[2],old_i(h[1]),old_i(p(h[0]))))

print(len(moves))
for mov in moves:
    print(*mov)


