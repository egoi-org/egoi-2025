#!/usr/bin/env python3
import sys

def main():
    P, N = map(int, input().split())

    if P == 1:
        ed = [0] * N
        deg = [0] * N

        for _ in range(N - 1):
            a, b = map(int, input().split())
            ed[a] ^= b
            ed[b] ^= a
            deg[a] += 1
            deg[b] += 1

        deg1 = [i for i in range(N) if deg[i] == 1]
        out = []

        for _ in range(N - 1):
            x = deg1.pop()
            y = ed[x]
            ed[x] ^= y
            ed[y] ^= x
            deg[x] -= 1
            deg[y] -= 1
            if deg[y] == 1:
                deg1.append(y)
            out.append(x)

        print("010")
        for a in out:
            print(a)
    else:
        input()
        for i in range(N - 1):
            a, b = map(int, input().split())
            print("aaa")

main()
