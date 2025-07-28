#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple

using ll = long long;
using ii = pair<ll, ll>;
using iii = tuple<ll, ll, ll>;

int n, m, q, idx, u[200005], v[200005], w[200005], rt[200005], pre[400005], sz[400005], lab[400005], par[400005], prv[200005], hv[400005], rv[400005];
ll original_cost, prf[400005], ft_1[200005], ft_2[200005], ans[200005];
ii adj[400005];
iii edges[200005];
vector<ii> rig[200005];
set<int> bad;

int ls(int x) {
	return x & -x;
}

void ft_upd(int p, ll v, ll ft[]) {
        for (; p <= n; p += ls(p)) {
		ft[p] += v;
	}
}

ll ft_qry(int p, ll ft[]) {
	ll r = 0;
	for (; p; p -= ls(p)) {
		r += ft[p];
	}
	return r;
}

int dfs(int u) {
	sz[u] = 1;
	if (adj[u].first) {
		for (auto v : {adj[u].first, adj[u].second}) {
			par[v] = u;
			prf[v] = prf[u] + w[lab[u]] - w[lab[v]];
			sz[u] += dfs(v);
		}
		if (sz[adj[u].second] > sz[adj[u].first]) {
			swap(adj[u].first, adj[u].second);
		}
	}
	return sz[u];
}

void decomp(int u, int h) {
	pre[u] = ++idx;
	rv[idx] = u;
	hv[u] = h;
	if (adj[u].first) {
		decomp(adj[u].first, h);
		decomp(adj[u].second, adj[u].second);
	}
}

namespace ufds {
	int lnk[200005];
	
	void init(int num_nodes) {
		iota(lnk + 1, lnk + 1 + num_nodes, 1);
	}
	int find(int x) {
		if (x == lnk[x]) {
			return x;
		}
		return lnk[x] = find(lnk[x]);
	}
	void unite(int a, int b) {
		a = find(a);
		b = find(b);
		assert(a != b);
		lnk[b] = a;
	}
};

struct node {
	node *left, *right;
	int S, E, val, pv;
	bool ip= false;
	node(int _s, int _e) : S(_s), E(_e), val(0) {
		if (S == E) {
			return;
		}
		int M = (S + E) / 2;
		left = new node(S, M);
		right = new node(M + 1, E);
	}
	void prop() {
		if (!ip) {
			return;
		}
		left->val = right->val = left->pv = right->pv = pv;
		left->ip = right->ip = 1;
		ip = 0;
	}
	void set(int l, int r, int v) {
		if (l > E || r < S) {
			return;
		}
		if (l <= S && E <= r) {
			val = pv = v;
			ip = 1;
			return;
		}
		prop();
		left->set(l, r, v);
		right->set(l, r, v);
	}
	int qry(int p) {
		if (S == E) {
			return val;
		}
		prop();
		int M = (S + E) / 2;
		if (p <= M) {
			return left->qry(p);
		} else {
			return right->qry(p);
		}
	}
} *root;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m>>q;
	for (int i = 1; i <= m; i++) {
		cin >> u[i] >> v[i] >> w[i];
		u[i]++;
                v[i]++;
                edges[i] = mt(w[i], u[i], v[i]);
	}
	sort(edges + 1, edges + 1 + m);
	iota(rt + 1, rt + 1 + n, 1);
	ufds::init(n);
	int cnt = n;
	for (int i = 1; i <= m; i++) {
		tie(w[i], u[i], v[i]) = edges[i];
		if (ufds::find(u[i]) == ufds::find(v[i])) {
			continue;
		}
		original_cost += w[i];
		cnt++;
		lab[cnt] = i;
		adj[cnt] = mp(rt[ufds::find(u[i])], rt[ufds::find(v[i])]);
		ufds::unite(u[i], v[i]);
		rt[ufds::find(u[i])] = cnt;
	}
	
        int total_comps = 0;
	for (int i = 1; i <= n; i++) {
		if (i == ufds::find(i)) {
			prf[rt[i]] = -w[lab[rt[i]]];
                            dfs(rt[i]);
			decomp(rt[i], rt[i]);
			total_comps++;
		}
	}
	for (int i = 1, l, r; i <= q; i++) {
                cin >> l >> r;
                l++;
                r++;
		rig[r].eb(l, i);
	}
	fill(prv + 1, prv + 1 + n, -1);
	for (int i = n + 1; i <= cnt; i++) {
                bad.insert(i);
	}
        root = new node(1, cnt);
	for (int r = 1; r <= n; r++) {
		// preprocessing to check -1 case
		int x = ufds::find(r);
		if (prv[x] != -1) {
			ft_upd(prv[x], -1, ft_1);
		}
		prv[x] = r;
		ft_upd(r, 1, ft_1);
		// HLD
		for (int t = r; t; t = par[hv[t]]) {
			int prv_node = t;
			vector<set<int>::iterator> to_erase;
			for (auto it = bad.lower_bound(pre[t]); it != bad.begin() && *(--it) >= pre[hv[t]]; ) {
				int prv_col = root->qry(pre[prv_node]);
				if (prv_col) {
					ft_upd(prv_col, -(prf[prv_node] - prf[rv[*it]]), ft_2);
				}
				prv_node = rv[*it];
				to_erase.pb(it);
			}
			int prv_col = root->qry(pre[prv_node]);
			if (prv_col) {
				ft_upd(prv_col, -(prf[prv_node] - prf[par[hv[t]]]), ft_2);
			}
			for (auto it : to_erase) {
				bad.erase(it);
			}
			if (par[hv[t]]) {
				bad.insert(pre[par[hv[t]]]);
			}
			bad.insert(pre[t]);
			ft_upd(r, prf[t] - prf[par[hv[t]]], ft_2);
			root->set(pre[hv[t]], pre[t], r);
		}
		for (auto [l, idx] : rig[r]) {
			// check -1 case
			if (ft_qry(r, ft_1) - ft_qry(l - 1, ft_1) < total_comps) {
				ans[idx] = -1;
				continue;
			}
			ll deleted_cost = ft_qry(n, ft_2) - ft_qry(l - 1, ft_2);
			ans[idx] = original_cost - deleted_cost;
                }
	}
	for (int i = 1; i <= q; i++) {
		cout << ans[i] << '\n';
	}
}
