#!/usr/bin/env python3

P, N = map(int, input().split())
if P == 1:
    print("1010")
    for i in range(N - 1):
        print(i)
else:
    for i in range(N - 2):
        print(i)
