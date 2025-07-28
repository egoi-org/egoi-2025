#include <bits/stdc++.h>
#include <cassert>
#include <tuple>
#include <vector>

using namespace std;

int main() {
  int N;
  cin >> N;

  std::vector<int> sum_counts(2 * N);

  std::vector<int> friend_of(2 * N);
  std::vector<int> string_id(2 * N);

  for (int i = 0; i < N; ++i) {
    int a, b;
    cin >> a >> b;
    friend_of[a] = b;
    friend_of[b] = a;
    sum_counts[(a + b) % (2 * N)]++;
    string_id[a] = string_id[b] = i;
  }

  int idx_of_max = 1;
  for (int i = 3; i < 2 * N; i += 2) {
    if (sum_counts[i] > sum_counts[idx_of_max]) {
      idx_of_max = i;
    }
  }

  int K = N - sum_counts[idx_of_max];

  cout << K << endl;

  std::vector<int> was_moved(N);
  std::vector<std::tuple<int, int, int>> moves;

  std::function<void(int)> dfs = [&](int el) {
    int p = string_id[el];
    if (was_moved[p])
      return;
    was_moved[p] = true;
    int s = friend_of[el];
    int e = (idx_of_max + 2 * N - el) % (2 * N);
    moves.emplace_back(p, s, e);
    dfs(friend_of[e]);
  };

  for (int i = 0; i < 2 * N; ++i) {
    if ((friend_of[i] + i) % (2 * N) == idx_of_max) {
      continue;
    }
    dfs(i);
  }
  assert(moves.size() == K);
  for (auto [p, s, e] : moves) {
    cout << p << ' ' << s << ' ' << e << endl;
  }

  return 0;
}
