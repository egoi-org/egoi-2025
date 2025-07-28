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

const int M = 46;
const int K = 12;

ll multinomial(vi v) {
  ll c = 1, m = v.empty() ? 1 : v[0];
  rep(i,1,sz(v)) rep(j,0,v[i])
    c = c * ++m / (j+1);
  return c;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int N;
  cin >> N;

  vector<pii> todo = {{1,1}};
  rep(s,2,K+1) {
    if(K % s == 0) {
      for(int b = s+1; multinomial({s,b-s}) <= N && K*b<=M*s; ++b)
        todo.emplace_back(s,b);
    }
  }

  vector<vector<vi>> block;
  for(auto [s,b] : todo) {
    block.emplace_back();
    vector<vi> ranges;
    rep(i,0,b) {
      vi row(K/s);
      iota(all(row),i*K/s);
      ranges.emplace_back(row);
    }
    vi choice(b,0);
    rep(i,b-s,b) choice[i] = 1;
    do {
      vi cur;
      rep(i,0,b) if(choice[i]) for(auto a : ranges[i]) cur.emplace_back(a);
      block.back().emplace_back(cur);
    } while(next_permutation(all(choice)));
  }

  vector<vi> cur;
  function<void(int)> go = [&](int nxt) {
    if(sz(cur) > N) return;
    if(nxt >= M) return;
    if(sz(cur) == N) { // found answer
      for(auto a : cur) {
        for(auto x : a) cout << x << " ";
        cout << endl;
      }
      exit(0);
    }

    rep(i,0,sz(block)) {
      int mx = nxt;
      for(auto q : block[i]) {
        for(auto &a : q) {
          a += nxt;
          mx = max(mx,a+1);
        }
        cur.emplace_back(q);
      }
      go(mx);
      cur.resize(sz(cur)-sz(block[i]));
    }
  };
  go(0);
  assert(false);
}
