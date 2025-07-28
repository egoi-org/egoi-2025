n, m = map(int, input().split())

a = list(map(int, input().split()))


def solve(a):
    last = [0 for _ in range(n + 1)]
    seen = [0 for _ in range(n + 1)]
    ff = False
    first = -1
    bs = 0
    be = len(a) - 1
    for i, x in list(enumerate(a))[::-1]:
        if last[x] and not ff:
            first = i
            ff = True
        if last[x] == 0:
            last[x] = i
    start = 0
    end = 0

    for i, x in enumerate(a):
        start = i
        if seen[x]:
            break
        seen[x] = 1
        if last[x] > i:
            end = max(end, last[x])
        if end > first:
            if end - start <= be - bs:
                be = end
                bs = start

    if end < first:
        for i, x in list(enumerate(a))[:end:-1]:
            if seen[x]:
                end = i
                break
            seen[x] = 1
        return start, end
    else:
        return bs + 1, be


start0, end0 = solve(a)
if end0 == 0:
    print(-1)
else:
    print(start0, end0)
