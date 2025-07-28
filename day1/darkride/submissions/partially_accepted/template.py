def query(switches):
    print("?", switches)
    return int(input())

N = int(input())

ans = []
for i in range(N):
    num_screams = query("0" * i + "1" + "0" * (N-i-1))
    if num_screams == 1:
        ans.append(i)
    if len(ans) == 2:
        break

A = ans[0]
B = ans[1]

print("!", A, B)
