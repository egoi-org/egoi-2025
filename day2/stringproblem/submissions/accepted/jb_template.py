N = int(input())

ab = []
for i in range(N):
    a, b = map(int, input().split())
    ab += [[a, b]]

where = [0]*(2*N)
dir_count = [0]*N
for i,(a,b) in enumerate(ab):
  where[a] = where[b] = i
  dab = (b-a)%(2*N);
  if dab % 2:
    dir_count[(a+dab//2)%N] += 1

dir = dir_count.index(max(dir_count))
done = [0]*N
moves = []

for i in range(N):
  x = i
  tomove = ab[x][0]
  while not done[x]:
    done[x] = 1
    tostay = ab[x][0]^ab[x][1]^tomove
    goto = (2*dir-tostay+1) % (2*N)
    if goto != tomove:
      moves.append((x, tomove, goto))
    x, tomove = where[goto], goto

K = len(moves)

print(K)

for i in range(K):
    p = moves[i][0]
    s = moves[i][1]
    e = moves[i][2]
    print(p, s, e)
