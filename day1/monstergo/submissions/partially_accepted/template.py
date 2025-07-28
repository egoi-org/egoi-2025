N = int(input())

c = [list(range(12)) for i in range(N)]

for i in range(N):
    print(*c[i])
