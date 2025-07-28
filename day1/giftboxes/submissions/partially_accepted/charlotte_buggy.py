n, m = map(int, input().split())

a = list(map(int, input().split()))


def solve(a):
    last = [0 for _ in range(n + 1)]
    seen = [0 for _ in range(n + 1)]
    for i, x in list(enumerate(a))[::-1]:
        if last[x] == 0:
            last[x] = i
            if not seen:
                first = i
                seen = True
    start = 0
    end = 0

    for i, x in enumerate(a):
        if seen[x]:
            start = i
            break
        seen[x] = 1
        if last[x] > i:
            end = max(end, last[x])

    for i, x in list(enumerate(a))[:end:-1]:
        if seen[x]:
            end = i
            break
        seen[x] = 1
    return start, end


start0, end0 = solve(a)
a = a[::-1]
s1, e1 = solve(a)
start1 = len(a) - 1 - e1
end1 = len(a) - 1 - s1
# print(start0,end0,start1,end1)
if end0 == 0:
    print(-1)
elif end0 - start0 < end1 - start1:
    print(start0, end0)
else:
    print(start1, end1)
