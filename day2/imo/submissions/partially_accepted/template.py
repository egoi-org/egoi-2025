#!/usr/bin/env python3
N, M, K = map(int, input().split())

a = [
    list(map(int, input().split()))
    for i in range(N)
]

scores = []
for i in range(N):
    ones = 0
    for j in range(M):
        if a[i][j] == 1:
            ones += 1
    scores.append((ones, -i))

scores.sort()
gaps = 0
for i in range(N-1):
    if scores[i+1][1] < scores[i][1]:
        gaps += 1

ans = N*M-M+gaps

print(ans)
