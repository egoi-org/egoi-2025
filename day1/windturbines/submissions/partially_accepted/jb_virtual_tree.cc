#include <bits/stdc++.h>
using namespace std;

// runs in time O((n + m + sum r-l)*log n)
// should solve subtasks 1, 4, 5

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define debug(...) //ignore
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double ld;


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, m, q;
  cin>>n>>m>>q;
  vector<tuple<int,int,int>> edges(m);
  for(auto& [c,x,y] : edges) cin>>x>>y>>c;
  sort(all(edges));

  ll mst = 0;
  vi uf(n);
  iota(all(uf),0);
  auto fnd = [&](int x) {
    while(x != uf[x]) x = uf[x] = uf[uf[x]];
    return x;
  };
  vector<vector<pii>> g(n);
  for(auto [c,x,y] : edges) {
    if(fnd(x) != fnd(y)) {
      uf[fnd(x)] = fnd(y);
      g[x].emplace_back(y,c);
      g[y].emplace_back(x,c);
      mst += c;
    }
  }

  int T = 0;
  vi tim(n), par(n), parc(n), jump(n), jump_max(n), jump_len(n,0), depth(n);
  function<void(int,int,int)> dfs = [&](int x, int p, int c) {
    tim[x] = T++;
    jump[x] = par[x] = p;
    jump_max[x] = parc[x] = c;
    if(p >= 0) jump_len[x] = 1;
    if(p >= 0 && jump[p] >= 0 && jump_len[p] == jump_len[jump[p]]) {
      jump[x] = jump[jump[p]];
      jump_len[x] = 1 + jump_len[p] + jump_len[jump[p]];
      jump_max[x] = max({c, jump_max[p], jump_max[jump[p]]});
    }
    for(auto [y,c] : g[x]) if(y != p) {
      depth[y] = depth[x]+1;
      dfs(y,x,c);
    }
  };
  dfs(0,-1,0);

  auto lca = [&](int a, int b) {
    int oa = min(a,b), ob = max(a,b);
    int steps = 0;
    if(depth[a] < depth[b]) swap(a,b);
    while(depth[a] > depth[b]) {
      if(depth[jump[a]] >= depth[b]) a = jump[a];
      else a = par[a];
      ++steps;
    }
    while(a != b) {
      if(jump[a] != jump[b]) a = jump[a], b = jump[b];
      else a = par[a], b = par[b];
      ++steps;
    }
    return a;
  };

  auto max_edge = [&](int x, int p) {
    int maxc = 0;
    while(depth[x] > depth[p]) {
      if(depth[jump[x]] >= depth[p]) {
        maxc = max(maxc, jump_max[x]);
        x = jump[x];
      }
      else {
        maxc = max(maxc, parc[x]);
        x = par[x];
      }
    }
    return maxc;
  };

  auto compressTree = [&](vi li) {
    auto cmp = [&](int a, int b) { return tim[a] < tim[b]; };
    sort(all(li), cmp);
    int m = sz(li)-1;
    rep(i,0,m) {
      int a = li[i], b = li[i+1];
      li.push_back(lca(a, b));
    }
    sort(all(li), cmp);
    li.erase(unique(all(li)), li.end());
    vector<tuple<int,int,int>> edges;
    rep(i,0,sz(li)-1) {
      int a = li[i], b = li[i+1], p = lca(a,b);
      edges.emplace_back(max_edge(b,p),b,p);
    }
    return edges;
  };

  rep(_,0,q) {
    int l, r;
    cin>>l>>r;
    vi v(r-l+1);
    iota(all(v),l);
    auto ed = compressTree(v);
    sort(all(ed));
    ll ans = mst;
    for(auto [c,x,y] : ed) {
      uf[x] = x;
      uf[y] = y;
      ans -= c;
    }
    rep(i,l,r) uf[i] = r;
    for(auto [c,x,y] : ed) {
      if(fnd(x) != fnd(y)) {
        uf[fnd(x)] = fnd(y);
        ans += c;
      }
    }
    cout << ans << '\n';
  }
}
