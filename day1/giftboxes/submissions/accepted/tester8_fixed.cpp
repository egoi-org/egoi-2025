#include <bits/stdc++.h>
using namespace std;
#define REP(i, s, e) for (int i = (s); i < (e); i++)
template <class T> inline bool mnto(T &a, T b) { return b < a ? a = b, 1 : 0; }
const int MAXN = 500005;
int n, m;
int a[MAXN];
int occ[MAXN];

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  REP(i, 0, m) { cin >> a[i]; }
  int r = m - 1;
  while (r >= 0 && occ[a[r]] == 0) {
    occ[a[r]]++;
    r--;
  }
  if (r == -1) {
    cout << -1 << '\n';
    return 0;
  }
  int ans = m - 1, ansl, ansr;
  REP(l, 0, m) {
    if (mnto(ans, r - l)) {
      ansl = l;
      ansr = r;
    }
    occ[a[l]]++;
    while (occ[a[l]] > 1 && r + 1 < m) {
      occ[a[++r]]--;
    }
    if (occ[a[l]] > 1) {
      break;
    }
  }
  cout << ansl << ' ' << ansr << '\n';
  return 0;
}

