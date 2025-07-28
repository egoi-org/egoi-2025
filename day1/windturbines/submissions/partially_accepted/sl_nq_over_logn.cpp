#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define trav(a, x) for (auto& a : x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
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

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int N, M, Q;
	cin >> N >> M >> Q;
	vector<tuple<int, int, int>> alleds;
	ll sumed = 0;
	rep(i,0,M) {
		int u, v, c;
		cin >> u >> v >> c;
		sumed += c;
		alleds.push_back({c, u, v});
	}
	sort(all(alleds));

	vector<tuple<int, int, int, int>> eds;
	UF uf(N);
	ll sumc = 0;
	trav(x, alleds) {
		int c, u, v;
		tie(c, u, v) = x;
		u = uf.find(u);
		v = uf.find(v);
		if (u != v) {
			uf.join(u, v);
			int w = uf.find(u);
			eds.push_back({u, v, w, c});
			sumc += c;
		}
	}
	vi roots;
	rep(i,0,N) if (uf.find(i) == i) roots.push_back(i);

	const int logn = 16;
	typedef uint16_t bitset;
	vector<bitset> state(N), ev(N+1);
	vector<ll> sums(1 << logn);
	for (int qi = 0; qi < Q; qi += logn) {
		int qiend = min(qi + logn, Q);
		state.assign(N, 0);
		ev.assign(N + 1, 0);
		sums.assign(1 << logn, 0);
		rep(j,qi,qiend) {
			int a, b;
			cin >> a >> b;
			bitset bit = 1 << (j - qi);
			ev[a] |= bit;
			ev[b + 1] |= bit;
		}
		bitset active = 0;
		rep(i,0,N) {
			active ^= ev[i];
			state[i] = active;
		}
		trav(x, eds) {
			int u, v, w, c;
			tie(u, v, w, c) = x;
			sums[state[u] & state[v]] -= c;
			state[w] = state[u] | state[v];
		}
		int ok = (1 << logn) - 1;
		trav(w, roots) ok &= state[w];
		rep(j,qi,qiend) {
			int bit = 1 << (j - qi);
			ll s = 0;
			if (ok & bit) {
				rep(i,0,(1 << logn)) {
					s += sums[i | bit];
				}
				s /= 2;
				s += sumc;
			} else {
				s = -1;
			}
			cout << s << '\n';
		}
	}
}
