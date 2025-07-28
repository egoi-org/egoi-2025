
// Hallelujah, praise the one who set me free
// Hallelujah, death has lost its grip on me
// You have broken every chain, There's salvation in your name
// Jesus Christ, my living hope
#include <bits/stdc++.h>
using namespace std;

#define REP(i, s, e) for (int i = (s); i < (e); i++)
#define RREP(i, s, e) for (int i = (s); i >= (e); i--)
template <class T> inline bool mnto(T &a, T b) { return b < a ? a = b, 1 : 0; }
template <class T> inline bool mxto(T &a, T b) { return a < b ? a = b, 1 : 0; }

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define FI first
#define SE second
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef tuple<int, int, int> iii;
#define ALL(_a) _a.begin(), _a.end()
#define SZ(_a) (int)_a.size()
#define pb push_back
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ii> vii;
typedef vector<iii> viii;

#ifndef DEBUG
#define cerr                                                                   \
  if (0)                                                                       \
  cerr
#endif

const int INF = 1000000005;
const ll LINF = 1000000000000000005ll;
const int MAXN = 1005;

int p, n;

namespace Phase1 {
vi adj[MAXN];
bool in_ans[MAXN];

int solve(int n) {
  REP(i, 1, n) {
    int u, v;
    cin >> u >> v;
    adj[u].pb(v);
    adj[v].pb(u);
  }
  vii lf[2];
  REP(i, 0, n) {
    if (SZ(adj[i]) == 1) {
      int p = adj[i][0];
      lf[p > i].pb({min(p, i), i});
    }
  }
  for (int b : {0, 1}) {
    sort(ALL(lf[b]));
  }

  if (!lf[0].empty() && !lf[1].empty() && lf[0][0].FI < lf[1][0].FI) {
    swap(lf[0], lf[1]);
  }

  deque<int> dq;
  for (int b : {0, 1}) {
    for (auto [_, u] : lf[b]) {
      dq.push_back(u);
    }
  }

  vii ans;
  while (SZ(ans) < n - 1) {
    int u = dq.front();
    dq.pop_front();
    if (in_ans[u]) {
      continue;
    }
    assert(SZ(adj[u]) == 1);
    int p = adj[u][0];
    in_ans[u] = 1;
    ans.pb({u, p});
    adj[p].erase(find(ALL(adj[p]), u));
    for (int v : adj[p]) {
      if (!in_ans[v] && SZ(adj[v]) == 1) {
        dq.push_front(v);
      }
    }
    if (SZ(adj[p]) == 1) {
      dq.push_back(p);
    }
  }

  cout << (ans[0].FI < ans[0].SE) << '\n';
  for (auto [i, _] : ans) {
    cout << i << '\n';
  }

  return 0;
}
} // namespace Phase1
namespace Phase2 {
int last_time[MAXN];

void add_edge(int leaf, int parent, int t) {
  last_time[leaf] = last_time[parent] = t;
  cout << leaf << endl;
}

int solve(int n) {
  char c;
  cin >> c;

  bool big_parent = c == '1';
  int prv_mn;
  { // handle first iter separately
    int a, b;
    cin >> a >> b;
    if (a > b) {
      swap(a, b);
    }
    if (big_parent) {
      add_edge(a, b, 1);
    } else {
      add_edge(b, a, 1);
    }
    prv_mn = a;
  }

  REP(t, 2, n) {
    int a, b;
    cin >> a >> b;
    if (a > b) {
      swap(a, b);
    }

    if (!last_time[a] && !last_time[b]) {
      if (a < prv_mn) {
        big_parent ^= 1;
      }
      if (big_parent) {
        add_edge(a, b, t);
      } else {
        add_edge(b, a, t);
      }
      prv_mn = a;
    } else if (last_time[a] == t - 1) {
      add_edge(b, a, t);
    } else if (last_time[b] == t - 1) {
      add_edge(a, b, t);
    } else {
      if (last_time[a] > last_time[b]) {
        add_edge(a, b, t);
      } else {
        add_edge(b, a, t);
      }
    }
  }

  return 0;
}
} // namespace Phase2

int main() {
  cin >> p >> n;
  if (p == 1) {
    return Phase1::solve(n);
  } else {
    return Phase2::solve(n);
  }
}
