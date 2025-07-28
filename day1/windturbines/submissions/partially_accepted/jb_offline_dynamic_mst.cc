#include <bits/stdc++.h>
using namespace std;

// should solve subtask 6, "\ell_i = 0"

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define debug(...) //ignore
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double ld;


struct RollbackUF {
  vi e; vector<pii> st;
  RollbackUF(int n) : e(n, -1) {}
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : find(e[x]); }
  int time() { return sz(st); }
  void rollback(int t) {
    for (int i = time(); i --> t;)
      e[st[i].first] = st[i].second;
    st.resize(t);
  }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    st.push_back({a, e[a]});
    st.push_back({b, e[b]});
    e[a] += e[b]; e[b] = a;
    return true;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, m, q;
  cin>>n>>m>>q;
  using ve = vector<tuple<int,int,int>>;
  ve edges(m);
  for(auto& [c,x,y] : edges) cin>>x>>y>>c;
  sort(all(edges));

  RollbackUF uf(n);

  vector<ll> ans(n,-1);
  // precondition:
  //   * [0,l] joined
  //   * maybe some necessary edges (not in ed) pre-merged
  function<void(ve,int,int,ll)> go = [&](ve ed, int l, int r, ll cost) {
    int tim1 = uf.time();
    int q = (l+r)/2;
    rep(i,l,q) uf.join(i,q);
    int tim2 = uf.time();
    ans[q] = cost;
    ve used, unused;
    for(auto [c,x,y] : ed) {
      if(uf.join(x,y)) {
        used.emplace_back(c,x,y);
        ans[q] += c;
      }
      else unused.emplace_back(c,x,y);
    }

    if(r - l == 1) return;

    // first go right:
    uf.rollback(tim2);
    go(used,q,r,cost);

    // finally go left:
    uf.rollback(tim1);
    for(auto [c,x,y] : used) {
      bool ok = uf.join(x,y);
      assert(ok);
    }
    go(unused,l,q,ans[q]);
  };
  go(edges,0,n,0);

  debug(ans);

  rep(i,0,q) {
    int x;
    cin>>x>>x;
    cout << ans[x] << endl;
  }
}
