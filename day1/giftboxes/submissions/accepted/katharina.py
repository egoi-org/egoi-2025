#!/usr/bin/python3

n, m = [int(x) for x in input().split()]
a = [int(x) for x in input().split()]
nums = [[-1, -1] for i in range(n)]
l = 1e18
r = -1
rightMostFirst = -1

for i in range(m):
    if nums[a[i]][0] == -1:
        nums[a[i]][0] = i
    else:
        rightMostFirst = max(rightMostFirst, nums[a[i]][0])
        if nums[a[i]][1] != -1:
            l = min(l, nums[a[i]][1])
            r = max(r, nums[a[i]][1])
        nums[a[i]][1] = i

lRes = 0
rRes = max(rightMostFirst, r)
right = rRes
best = rRes + 1
for left in range(1, m):
    if left - 1 == nums[a[left - 1]][1]:
        break
    if left > l:
        break
    right = max(right, nums[a[left - 1]][1])
    if best > right - left + 1:
        best = right - left + 1
        lRes = left
        rRes = right

if n == m:
    print(-1)
else:
    print(lRes, rRes)
