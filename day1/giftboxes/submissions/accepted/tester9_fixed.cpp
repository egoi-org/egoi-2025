#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define F first
#define S second
const int mod = 998244353LL;

void solve() {
	int n, m;
	cin >> n >> m;
	vector<int> f(n, -1), l(n), v(m);
	for (int i = 0; i < m; i++) {
		cin >> v[i];
		if (f[v[i]] == -1) f[v[i]] = i;
		l[v[i]] = i;
	}
	int possible = m-1;
	vector<bool> seen(n);
	for (int i = m-1; i >= 0; i--) {
		if (!seen[v[i]]) {
			seen[v[i]] = true;
			possible--;
		} else break;
	}
	if (possible == -1) { cout << -1 << "\n"; return; }
	int best = m-possible;
	int lx = 0, rx = possible;
	seen.assign(n, false);
	for (int i = 0; i < m; i++) { 
		if (seen[v[i]]) break; 
		seen[v[i]] = true; 
		possible = max(l[v[i]], possible); 
		if (i+1 + m-possible > best) { 
			best = i+1 + m-possible; 
			lx = i+1; rx = possible; 
		} 
	}
       	cout << lx << " " << rx << "\n";
}

signed main() {
	ios::sync_with_stdio(false); 
	cin.tie(nullptr); 
	int T = 1; 
	//~ cin >> T;
	while (T--) solve(); 
}
