#!/usr/bin/env python3

def ask(question):
    print("".join([str(element) for element in question]))
    return int(input())

def solve(h):
    potential2 = [k for k in h]
    while (sum(potential2) != 1):
        m = sum(potential2) // 2
        last = -1
        query2 = ['?']+['0']*n
        query_size = 0
        for i in range(n):
            if (potential2[i] == 1):
                query2[i+1] = '1'
                last = i + 1
                query_size += 1
            if query_size == m:
                break
        ans2 = ask(query2)
        if (ans2 % 2 == 0):
            for i in range(last):
                potential2[i] = 0
        else:
            for i in range(last, n):
                potential2[i] = 0

    return potential2.index(1)


n = int(input())

ii = 0

phase_one = []

major_one = -1

while True:
    x = [0 if (j % (2 ** (ii + 1))) < 2 ** ii else 1 for j in range(n)]
    if (sum(x) == 0):
        break
    query = ['?']+['0']*n
    for k in range(n):
        if x[k] == 1:
            query[k+1] = '1'
    ans = ask(query)
    phase_one.append(ans)
    if (ans % 2 == 1 and major_one == -1):
        major_one = solve(x)
    ii += 1

major_two = -1

potenial = [1 for k in range(n)]

ii = 0

for ans in phase_one:
    x = [0 if (j % (2 ** (ii + 1))) < 2 ** ii else 1 for j in range(n)]
    ii += 1
    if (sum(x) == 0):
        break

    kill = (ans + x[major_one] + 1) % 2


    for j in range(n):
        if (x[j] == kill):
            potenial[j] = 0

major_two = potenial.index(1)


print(" ".join(["!", str(major_one), str(major_two)]))


