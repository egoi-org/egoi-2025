#!/bin/python3

N = int(input())


for _ in range(N):
    _ = input()

if N%2==0:
    print(N-2)
    for i in range(N):
        if i == 0 or i==N//2:
            continue
        print(i,2*i+1,2*N-(2*i+1)+2)
else:
    print(N-1)
    for i in range(1,(N+1)//2):
        j = N-i
        print(i,2*i+1,2*j+1)
        print(j,2*j+1,2*i+1)

