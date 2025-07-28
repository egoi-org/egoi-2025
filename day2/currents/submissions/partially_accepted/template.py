N, M = map(int, input().split())

for i in range(M):
    a, b = map(int, input().split())

ans = [0] * (N - 1)

for i in range(N-1):
    ans[i] = (N-i-2) + (N-2)

if N==2:
    ans[0] = 1;

print(*ans)
