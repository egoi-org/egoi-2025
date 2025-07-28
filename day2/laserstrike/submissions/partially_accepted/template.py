P, N = map(int, input().split())

if P == 1:
    deg = [0] * N
    for i in range(N - 1):
        a, b = map(int, input().split())
        deg[a] += 1
        deg[b] += 1

    root = deg.index(N-1)
    message = "0"

    if root == 0:
        message = "1"

    l = list(range(N))
    l.pop(root)

    print(message)
    for i in range(N - 1):
        print(l[i])
else:
    message = input()
    
    root = N
    for i in range(N - 1):
        a, b = map(int, input().split())
        if root == N:
            if message == "1":
                root = min(a,b)
            else:
                root = max(a,b)
        
        guess_a = True

        if root == a:
            guess_a = False

        if guess_a:
            print(a)
        else:
            print(b)
