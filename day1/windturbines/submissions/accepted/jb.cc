#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

struct UF {
  vi e;
  UF(int n) : e(n, -1) {}
  bool sameSet(int a, int b) { return find(a) == find(b); }
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b]; e[b] = a;
    return true;
  }
};

struct FT {
  vector<ll> s;
  FT(int n) : s(n) {}
  void update(int pos, ll dif) { // a[pos] += dif
    for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
  }
  ll query(int pos) { // sum of values in [0, pos)
    ll res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos-1];
    return res;
  }
};

template<class T>
struct RMQ {
  vector<vector<T>> jmp;
  RMQ(const vector<T>& V) : jmp(1, V) {
    for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
      jmp.emplace_back(sz(V) - pw * 2 + 1);
      rep(j,0,sz(jmp[k]))
        jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(int a, int b) {
    //assert(a < b); // or return inf if a == b
    int dep = 31 - __builtin_clz(b - a);
    return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

struct LCA {
  int T = 0;
  vi time, path, ret;
  RMQ<int> rmq;

  LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C,sz(C)-1,-1), ret)) {}
  void dfs(vector<vi>& C, int v, int par) {
    time[v] = T++;
    for (int y : C[v]) if (y != par) {
      path.push_back(v), ret.push_back(time[v]);
      dfs(C, y, v);
    }
  }

  int lca(int a, int b) {
    if (a == b) return a;
    tie(a, b) = minmax({time[a], time[b]});
    return path[rmq.query(a, b)];
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, m, q;
  cin >> n >> m >> q;
  vector<tuple<ll,int,int>> edges;
  rep(i,0,m) {
    int c, x, y;
    cin>>x>>y>>c;
    edges.emplace_back(c,x,y);
  }
  rep(i,1,n) edges.emplace_back(1e12,i-1,i);
  sort(all(edges));

  UF uf(n);
  vi root(n);
  vector<ll> weight(n);
  iota(all(root),0);
  vector<vi> childs(n);

  ll cost = 0;
  for(auto [w,a,b] : edges) {
    a = uf.find(a);
    b = uf.find(b);
    if(!uf.join(a,b)) continue;
    cost += w;
    int nxt = sz(childs);
    childs.emplace_back();
    childs.back() = {root[a],root[b]};
    weight.emplace_back(w);
    root[a] = root[b] = nxt;
  }

  vi leaf_chain(sz(childs),n);
  LCA lca(childs);
  FT fw(n+1);

  auto activate = [&](int x) {
    int r = sz(childs)-1;
    while(leaf_chain[r] != n) {
      int y = leaf_chain[r];
      int z = lca.lca(x, y);
      //assert(sz(childs[z]) == 2);
      int zx = childs[z][0], zy = childs[z][1];
      if(lca.lca(x,zx) != zx) swap(zx,zy);
      //assert(lca.lca(x,zx) == zx && lca.lca(y,zy) == zy);
      fw.update(leaf_chain[zx],-weight[z]);
      fw.update(y,weight[z]);
      leaf_chain[zy] = y;
      leaf_chain[r] = n;
      r = zx;
    }
    leaf_chain.back() = x;
  };

  vi ql(q), qr(q);
  vector<ll> ans(q);
  vector<vi> queries_at_l(n);
  rep(i,0,q) {
    cin>>ql[i]>>qr[i];
    ++qr[i];
    queries_at_l[ql[i]].emplace_back(i);
  }

  for(int l = n; l--;) {
    activate(l);
    for(auto i : queries_at_l[l])
      ans[i] = cost - fw.query(qr[i]);
  }

  for(auto a : ans)
    cout << a   << "\n";
}
