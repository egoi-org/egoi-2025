#!/usr/bin/env python3

n = int(input())
ab = [[int(x) for x in input().split()] for _ in range(n)]
where = [0]*(2*n)
dir_count = [0]*n

for i,(a,b) in enumerate(ab):
  where[a] = where[b] = i
  dab = (b-a)%(2*n);
  if dab % 2:
    dir_count[(a+dab//2)%n] += 1

dir = dir_count.index(max(dir_count))
done = [0]*n
moves = []
for i in range(n):
  x = i
  tomove = ab[x][0]
  while not done[x]:
    done[x] = 1
    tostay = ab[x][0]^ab[x][1]^tomove
    goto = (2*dir-tostay+1) % (2*n)
    if goto != tomove:
      moves.append((x, tomove, goto))
    x, tomove = where[goto], goto

print(len(moves))
for m in moves:
  print(*m)
