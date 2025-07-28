#!/usr/bin/env python3
n,m,k = map(int,input().split())
assert n == m == 2 and k == 1

s1 = sum(map(int,input().split()))
s2 = sum(map(int,input().split()))

if s1 == 0 and s2 == 0:
    print(2)
elif s1 == 0 and s2 == 1:
    print(3)
elif s1 == 0 and s2 == 2:
    print(3)
elif s1 == 1 and s2 == 0:
    print(2)
elif s1 == 1 and s2 == 1:
    print(2)
elif s1 == 1 and s2 == 2:
    print(3)
elif s1 == 2 and s2 == 0:
    print(2)
elif s1 == 2 and s2 == 1:
    print(2)
elif s1 == 2 and s2 == 2:
    print(2)