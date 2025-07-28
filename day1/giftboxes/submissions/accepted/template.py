T, N = map(int, input().split())

a = list(map(int, input().split()))

nums = [[-1, -1] for x in range(T)]
l = 1e18
r = -1
rightMostFirst = -1

for x in range(N):
    if nums[a[x]][0] == -1:
        nums[a[x]][0] = x
    else:
        rightMostFirst = max(rightMostFirst, nums[a[x]][0])
        if nums[a[x]][1] != -1:
            l = min(l, nums[a[x]][1])
            r = max(r, nums[a[x]][1])
        nums[a[x]][1] = x

i = 0
j = max(rightMostFirst, r)
right = j
best = j + 1
for left in range(1, N):
    if left - 1 == nums[a[left - 1]][1]:
        break
    if left > l:
        break
    right = max(right, nums[a[left - 1]][1])
    if best > right - left + 1:
        best = right - left + 1
        i = left
        j = right

if T == N:
    print(-1)
else:
    print(i, j)
