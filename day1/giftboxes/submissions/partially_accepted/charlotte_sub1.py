n, m = map(int, input().split())

a = list(map(int, input().split()))


def solve(a):
    seen = [0 for _ in range(n + 1)]
    for i, x in list(enumerate(a))[::-1]:
        if seen[x]:
            print(i, i)
        if seen[x] == 0:
            seen[x] = 1

solve(a)
