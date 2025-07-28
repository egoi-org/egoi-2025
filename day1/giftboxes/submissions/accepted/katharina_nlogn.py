#!/usr/bin/python3

n, m = [int(x) for x in input().split()]
a = [int(x) for x in input().split()]
count = [0 for x in a]
atMostOnce = n
for i, e in enumerate(a):
    count[e] += 1
    if count[e] == 2:
        atMostOnce -= 1

l = -1
r = m
res = [-1, -1]


def check(mi, cnt, mstOnce):
    for i in range(mi):
        cnt[a[i]] -= 1
        if cnt[a[i]] == 1:
            mstOnce += 1
    if mstOnce == n:
        return [0, mi - 1]
    for i in range(mi, m):
        cnt[a[i - mi]] += 1
        if cnt[a[i - mi]] == 2:
            mstOnce -= 1
        cnt[a[i]] -= 1
        if cnt[a[i]] == 1:
            mstOnce += 1
        if mstOnce == n:
            return [i - mi + 1, i]
    return [-1, -1]


while r - l > 1:
    mid = int((l + r) / 2)
    newRes = check(mid, count.copy(), atMostOnce)
    if newRes[0] != -1:
        r = mid
        res = newRes
    else:
        l = mid

if r == 0:
    print(-1)
else:
    print(res[0], res[1])

