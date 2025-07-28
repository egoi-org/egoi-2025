#define NDEBUG
#define UNUSED __attribute__((unused))
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define trav(a, x) for (auto& a : x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

struct pii {
	int first, second;
	pii() : first(0), second(0) {}
	pii(int a, int b) : first(a), second(b) {}
};
bool operator<(pii a, pii b) { return a.first < b.first; }

vi chainsize;

template<typename T>
T unit();

template<>
int unit<int>() { return -1; }
template<>
pii unit<pii>() { return pii(-1, -1); }

template<typename T>
struct Tree {
	T f(T a, T b) { return max(a, b); }
	vector<T> vec;
	Tree(int n = 0, T def = unit<T>()) : vec(2*n, def) {}
	void update(int st, int pos, T val) {
		int base = st*2, n = chainsize[st];
		pos -= st;
		T* s = vec.data() + base;
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int st, int b, int e) { // query [b, e)
		int base = st*2, n = chainsize[st];
		b -= st, e -= st;
		assert(b <= e);
		assert(e <= n);
		T* s = vec.data() + base;
		T ra = unit<T>(), rb = unit<T>();
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

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

vector<vector<pii>> chs1;
vector<int> sizes1;

int dfs1(int at, int par, vector<vector<pii>>& adj) {
	int s = 1;
	for (auto x : adj[at]) if (x.first != par) {
		s += dfs1(x.first, at, adj);
		chs1[at].push_back(x);
	}
	sizes1[at] = s;
	return s;
}

vi ren;
vi pars;
vi parw;
vector<pii> chainstartw;
vi chainstarts;
vi chainroot;
vi endind;

int reni;
void dfs2(int at, int par, int edw, int chainstart, pii chainw) {
	int me = reni++;
	ren[at] = me;
	pars[me] = par;
	parw[me] = edw;
	if (par != me - 1) chainstart = me, chainw = pii(-1, -1);
	else chainw = max(chainw, pii(edw, me));
	chainstarts[me] = chainstart;
	chainstartw[me] = chainw;
	chainsize[chainstart] = me - chainstart + 1;
	sort(all(chs1[at]), [&](pii a, pii b) { return sizes1[a.first] > sizes1[b.first]; });
	for (auto x : chs1[at]) {
		dfs2(x.first, me, x.second, chainstart, chainw);
	}
	endind[me] = reni;
}

vi comp;
int ncomps;
vi compcounts;
int activecomps;

ll sumc, curans;
vi rootmap;
Tree<int> rootmapst;
Tree<pii> edgemax;

int findlastroot(int a, int b) {
	// find last root in range [a, b], where a is a chain start
	int r = rootmapst.query(a, a, b+1);
	assert(r != -1);
	return r;
}

int findroot(int ind) {
	for (;;) {
		int up = chainstarts[ind];
		if (chainroot[up] <= ind)
			return findlastroot(up, ind);
		assert(up != 0);
		ind = pars[up];
	}
}

#ifndef NDEBUG
vi debugst;
#endif

vector<tuple<int, int, int, int, int, int, int>> rollback;
void add(int ind) {
#ifndef NDEBUG
	debugst.push_back(ind);
#endif
	if (!compcounts[comp[ind]]++) activecomps++;
	ind = ren[ind];
	int root = findroot(ind);
	int other = rootmap[root];
	assert(ind != other);
	int a = ind, b = other;
	if (a > b) swap(a, b);
	pii maxw{-1, -1};
	for (;;) {
		int c = chainstarts[b];
		if (c <= a) {
			maxw = max(maxw, edgemax.query(c, a+1, b+1));
			break;
		}
		maxw = max(maxw, chainstartw[b]);
		maxw = max(maxw, {parw[c], c});
		b = pars[c];
		if (b < a) swap(a, b);
	}
	assert(maxw.first != -1);
	curans -= maxw.first;
	int subroot = maxw.second;
	assert(root < subroot);
	int st = chainstarts[subroot];
	UNUSED bool indDown = (subroot <= ind && ind < endind[subroot]);
	bool otherDown = (subroot <= other && other < endind[subroot]);
	assert(indDown + otherDown == 1);
	if (otherDown) swap(ind, other);
	int& r = chainroot[st];
	rollback.push_back({st, r, root, rootmap[root], subroot, rootmap[subroot], maxw.first});
	r = min(r, subroot);
	rootmap[root] = other;
	rootmap[subroot] = ind;
	rootmapst.update(st, subroot, subroot);
}

void del(int ind) {
#ifndef NDEBUG
	assert(debugst.back() == ind);
	debugst.pop_back();
#endif
	if (!--compcounts[comp[ind]]) activecomps--;
	ind = ren[ind];
	int st, r, root, rootv, subroot, subrootv, cost;
	tie(st, r, root, rootv, subroot, subrootv, cost) = rollback.back();
	curans += cost;
	rollback.pop_back();
	rootmap[subroot] = subrootv;
	rootmap[root] = rootv;
	chainroot[st] = r;
	rootmapst.update(st, subroot, -1);
}

void init(int ind) {
#ifndef NDEBUG
	assert(debugst.empty());
	debugst.push_back(ind);
#endif
	UNUSED int r = compcounts[comp[ind]]++;
	assert(!r);
	activecomps = 1;
	curans = sumc;
	ind = ren[ind];
	rootmap[0] = ind;
	rootmapst.update(0, 0, 0);
	chainroot[0] = 0;
}

void deinit(int ind) {
#ifndef NDEBUG
	assert(debugst.back() == ind);
	debugst.pop_back();
	assert(debugst.empty());
#endif
	compcounts[comp[ind]]--;
	assert(curans == sumc);
	ind = ren[ind];
	assert(rollback.empty());
	assert(rootmap[0] == ind);
	rootmap[0] = -1;
	rootmapst.update(0, 0, -1);
	assert(chainroot[0] == 0);
	chainroot[0] = INT_MAX;
}

ll calc() {
	if (activecomps != ncomps) return -1;
	return curans;
}

vector<ll> mo(vector<pii> Q, int N) {
	const int blk = 350; // ~N/sqrt(Q)
	vi s(sz(Q));
#define K(x) make_pair(x.first/blk, x.second)
	iota(all(s), 0);
	sort(all(s), [&](int s, int t){ return K(Q[s]) < K(Q[t]); });
	vector<vi> chunks((N-1) / blk + 1);
	trav(qi,s) chunks[Q[qi].first / blk].push_back(qi);
	vector<ll> res(sz(Q));
	rep(ch,0,sz(chunks)) {
		int lastb = -1, base = (ch+1)*blk;
		trav(qi,chunks[ch]) {
			int a = Q[qi].first, b = Q[qi].second;
			assert(a < base);
			if (b < base) {
				init(a);
				rep(i,a+1,b+1) add(i);
				res[qi] = calc();
				for (int i = b; i >= a+1; i--) del(i);
				deinit(a);
			} else {
				if (lastb == -1) {
					lastb = base;
					init(lastb);
				}
				assert(lastb <= b);
				while (lastb < b) add(++lastb);
				for (int i = base-1; i >= a; --i) add(i);
				res[qi] = calc();
				rep(i,a,base) del(i);
			}
		}
		if (lastb != -1) {
			while (lastb > base) del(lastb--);
			deinit(base);
		}
	}
	return res;
}

const int inf = 2'000'000'000;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int N, M, Q;
	cin >> N >> M >> Q;
	vector<tuple<int, int, int>> eds;
	vector<tuple<int, int, int>> alleds;
	ll sumed = 0;
	rep(i,0,M) {
		int u, v, c;
		cin >> u >> v >> c;
		sumed += c;
		alleds.push_back({c, u, v});
	}
	sort(all(alleds));
	UF uf(N);
	trav(x, alleds) {
		int c, u, v;
		tie(c, u, v) = x;
		if (uf.join(u, v)) eds.push_back({u, v, c});
	}
	vi roots;
	rep(i,0,N) if (uf.find(i) == i) roots.push_back(i);
	int ind = 0;
	comp.resize(N);
	trav(x, roots) comp[x] = ind++;
	ncomps = ind;
	rep(i,0,N) comp[i] = comp[uf.find(i)];
	rep(i,1,sz(roots)) {
		eds.push_back({roots[0], roots[i], inf});
	}
	vector<vector<pii>> adj(N);
	trav(x, eds) {
		int u, v, c;
		tie(u, v, c) = x;
		adj[u].push_back({v, c});
		adj[v].push_back({u, c});
		sumc += c;
	}

	chs1.resize(N);
	sizes1.resize(N);
	ren.resize(N);
	UNUSED int s = dfs1(0, -1, adj);
	assert(s == N);
	pars.resize(N);
	parw.resize(N);
	chainstarts.resize(N);
	chainstartw.resize(N);
	chainsize.resize(N);
	endind.resize(N);
	dfs2(0, -1, -1, 0, pii(-1, -1));
	rootmap.assign(N, -1);
	rootmapst = Tree<int>(N);
	chainroot.assign(N, INT_MAX);
	edgemax = Tree<pii>(N);
	rep(i,0,N) {
		edgemax.update(chainstarts[i], i, pii(parw[i], i));
	}

	vector<pii> que;
	rep(qi,0,Q) {
		int l, r;
		cin >> l >> r;
		que.push_back({l, r});
	}
	compcounts.resize(ncomps);
	auto res = mo(que, N);
	trav(x, res) {
		cout << x << '\n';
	}
}
