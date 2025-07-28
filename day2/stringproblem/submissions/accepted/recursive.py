from collections import defaultdict
import sys

sys.setrecursionlimit(100000)

def main():
    N = int(input())

    sum_counts = [0] * (2 * N)
    friend_of = [0] * (2 * N)
    string_id = [0] * (2 * N)

    for i in range(N):
        a, b = map(int, input().split())
        friend_of[a] = b
        friend_of[b] = a
        sum_counts[(a + b) % (2 * N)] += 1
        string_id[a] = string_id[b] = i

    # Find index of maximum odd value in sum_counts
    idx_of_max = 1
    for i in range(3, 2 * N, 2):
        if sum_counts[i] > sum_counts[idx_of_max]:
            idx_of_max = i

    K = N - sum_counts[idx_of_max]
    print(K)

    was_moved = [False] * N
    moves = []

    def dfs(el):
        p = string_id[el]
        if was_moved[p]:
            return
        was_moved[p] = True
        s = friend_of[el]
        e = (idx_of_max + 2 * N - el) % (2 * N)
        moves.append((p, s, e))
        dfs(friend_of[e])

    for i in range(2 * N):
        if (friend_of[i] + i) % (2 * N) == idx_of_max:
            continue
        dfs(i)

    assert len(moves) == K
    for p, s, e in moves:
        print(p, s, e)

if __name__ == "__main__":
    main()
