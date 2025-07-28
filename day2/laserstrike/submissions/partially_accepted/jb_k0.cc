// @EXPECTED_GRADES@ AC WA WA WA WA

// Uses k = 0
// The program cannot always be correct, so it fails with roughly 1/#leafs probability
// (so it should pass the star-testcase, but not the line one)
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
  cin.ignore();
  vi perm(n), invperm(n);
  iota(all(perm),0);
  shuffle(all(perm),mt19937_64(42));
  rep(i,0,n) invperm[perm[i]] = i;
  if(phase == 1) { // ALICE
    vector<vi> g(n);
    vi deg(n), xors(n);
    rep(i,1,n) {
      int x,y;
      cin>>x>>y;
      x = perm[x];
      y = perm[y];
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
      cout << invperm[leaf] << endl;
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
    cout << endl; // communication is cheating

    for(auto [y,x] : blue) trim(x);
    for(auto [x,y] : red) trim(x);

    for(int x : todo) if(deg[x]) trim(xors[x]);
  }
  else { // BOB
    string help;
    getline(cin, help);
    assert(help.empty());
    int typ = 0, time = 99;
    vi seen(n);
    pii last_leaf_edge{-1,-1};
    rep(i,1,n) {
      int a, b;
      cin >> a >> b;
      a = perm[a];
      b = perm[b];
      if(b < a) swap(a,b);
      bool t = (seen[a] == time || (seen[a] < seen[b] && seen[b] < time));
      if(!seen[a] && !seen[b]) {
        if(pii(a,b) < last_leaf_edge) typ = !typ;
        last_leaf_edge = pii(a,b);
        t = typ;
      }
      seen[a] = seen[b] = ++time;
      cout << (t ? invperm[b] : invperm[a]) << endl;
    }
  }
}

