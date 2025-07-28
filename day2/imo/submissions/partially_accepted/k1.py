#!/usr/bin/env python3

n,m,k = map(int,input().split())
scores = []

for i in range(n):
    ones = input().count('1')
    scores.append((ones, -i))

scores.sort()
gaps = 0
for i in range(n-1):
    if scores[i+1][1] < scores[i][1]:
        gaps += 1

print(n*m-m+gaps)
