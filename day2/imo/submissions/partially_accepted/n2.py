#!/usr/bin/env python3

# n = 2, should be O(m^2)

n,m,k = map(int,input().split())

a1 = list(map(int,input().split()))
a2 = list(map(int,input().split()))
a1.sort()
a2.sort()
s1 = sum(a1)
s2 = sum(a2)

strict = 1

if s1 >= s2:
    strict = 0
    a1,a2 = a2,a1
    s1,s2 = s2,s1

ans = n*m

t1 = 0
for h1 in range(0, m+1):
    t2 = 0
    for h2 in range(0, m+1):

        r1 = s1 - t1 + h1*k
        l2 = s2 - t2
        if r1 + strict <= l2:
            ans = min(ans, n*m-h1-h2)

        if h2 < m:
            t2 += a2[h2]
    
    if h1 < m:
        t1 += a1[m-h1-1]

print(ans)
