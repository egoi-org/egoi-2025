#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define debug(...) //ignore
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double ld;

int main() {
  int phase, n;
  cin >> phase >> n;
  if(phase == 1) { // ALICE
    vector<vi> g(n);
    vi deg(n), xors(n);
    rep(i,1,n) {
      int x,y;
      cin>>x>>y;
      g[x].emplace_back(y);
      g[y].emplace_back(x);
      ++deg[x];
      ++deg[y];
      xors[x] ^= y;
      xors[y] ^= x;
    }

    list<int> todo;
    vector<vi> leafs_hanging(n);
    rep(x,0,n) if(deg[x] == 1)
        leafs_hanging[xors[x]].emplace_back(x);

    auto cut = [&](int par, int leaf){
      cout << leaf << endl;
      --deg[par];
      --deg[leaf];
      xors[par] ^= leaf;
      if(deg[par] == 1) {
        todo.emplace_back(par);
        leafs_hanging[xors[par]].emplace_back(par);
      }
    };

    auto trim = [&](int x){
      for(int y : leafs_hanging[x]) cut(x,y);
      leafs_hanging[x].clear();
    };

    vector<pii> red, blue;
    rep(x,0,n) if(sz(leafs_hanging[x])) {
      int y = leafs_hanging[x][0];
      if(x < y) red.emplace_back(x,y);
      else blue.emplace_back(y,x);
    }
    sort(all(red));
    sort(all(blue));
    bool bit = sz(blue) == 0 || (sz(red) > 0 && red.back() > blue[0]);
    cout << int(bit) << endl;

    if(bit) for(auto [x,y] : red) trim(x);
    for(auto [y,x] : blue) trim(x);
    if(!bit) for(auto [x,y] : red) trim(x);

    for(int x : todo) if(deg[x]) trim(xors[x]);
  }
  else { // BOB
    int typ, time = 99;
    cin>>typ;
    vi seen(n);
    pii last_leaf_edge{-1,-1};
    rep(i,1,n) {
      int a, b;
      cin >> a >> b;
      if(b < a) swap(a,b);
      bool t = (seen[a] == time || (seen[a] < seen[b] && seen[b] < time));
      if(!seen[a] && !seen[b]) {
        if(pii(a,b) < last_leaf_edge) typ = !typ;
        last_leaf_edge = pii(a,b);
        t = typ;
      }
      seen[a] = seen[b] = ++time;
      cout << (t ? b : a) << endl;
    }
  }
}

