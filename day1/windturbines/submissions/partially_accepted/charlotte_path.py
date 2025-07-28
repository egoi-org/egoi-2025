n, m, q = map(int, input().split())
edges = []
for _ in range(m):
    u, v, c = map(int, input().split())
    edges.append((u, v, c))

edges.sort()
pref = [0 for _ in range(n)]
for i in range(1, n):
    pref[i] = pref[i - 1] + edges[i - 1][2]

for _ in range(q):
    l, r = map(int, input().split())
    print(pref[n - 1] - (pref[r] - pref[l]))
