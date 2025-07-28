N, M, Q = map(int, input().split())

edges = []
for i in range(M):
    u, v, c = map(int, input().split())
    edges.append((u, v, c))

edges.sort()
pref = [0 for _ in range(N)]
for i in range(1, N):
    pref[i] = pref[i - 1] + edges[i - 1][2]

ans = [0] * Q
for i in range(Q):
    l, r = map(int, input().split())
    ans[i] = pref[N - 1] - (pref[r] - pref[l])


for i in range(Q):
    print(ans[i])
    


