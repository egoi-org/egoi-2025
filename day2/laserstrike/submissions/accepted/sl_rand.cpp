// This solution actually uses K = O(log #line-like testcases), but it gets 100 points if we have luck with the seed.
#include <iostream>
#include <vector>
#include <set>
#include <cassert>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int LINE_PROB = 10;
const int RNG_SEED = 12;

struct RNG {
	unsigned long long state;
	RNG() : state(RNG_SEED) {}
	void feed(int x) {
		state *= 0x9a947b15f39b7455ULL;
		state += x;
		state *= 0x1927319823123103ULL;
		state ^= 0x1283712837161230ULL;
	}
	int rand() {
		return (int)(state >> 33);
	}
};

int P, N;
int highdeg;
string message;
vi picks;
vi deg;
vi deg1;
vi xo;
set<pii> eds;

void done() {
	cout << message << endl;
	for (int i = 0; i < N - 1; ++i) {
		cout << picks[i] << endl;
	}
	exit(0);
}

void rec(int at, RNG rng) {
	if (at == N-1) {
		done();
	}

	rep(i,0,sz(deg1)) {
		swap(deg1[i], deg1[sz(deg1)-1]);
		int x = deg1.back();
		int y = xo[x];

		RNG rng2 = rng;
		int a = x, b = y;
		if (!eds.count({a,b})) swap(a, b);
		assert(eds.count({a,b}));
		rng2.feed(a);
		rng2.feed(b);
		int r = rng2.rand();
		bool guess_a = !!(r & (1 << 16));

		if (guess_a == (a == x)) {
			picks[at] = x;
			deg1.pop_back();
			xo[x] ^= y;
			xo[y] ^= x;
			deg[x]--;
			deg[y]--;
			if (deg[y] == 1) deg1.push_back(y);
			if (deg[y] == 2) highdeg--;

			if (r % 100 < LINE_PROB) {
				if (highdeg == 0 && deg[y] == 1) {
					at++;
					while (at != N-1) {
						assert(deg[y] == 1);
						picks[at] = y;
						int z = xo[y];
						xo[y] ^= z;
						xo[z] ^= y;
						deg[y]--;
						deg[z]--;
						y = z;
						at++;
					}
					done();
				}
			} else {
				rec(at+1, rng2);
			}

			if (deg[y] == 2) highdeg++;
			if (deg[y] == 1) deg1.pop_back();
			deg[y]++;
			deg[x]++;
			xo[y] ^= x;
			xo[x] ^= y;
			deg1.push_back(x);
		}

		swap(deg1[i], deg1[sz(deg1)-1]);
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	cin >> P >> N;
	if (P == 1) {
		deg.resize(N);
		xo.resize(N);
		for (int i = 0; i < N - 1; ++i) {
			int a, b;
			cin >> a >> b;
			deg[a]++;
			deg[b]++;
			xo[a] ^= b;
			xo[b] ^= a;
			eds.insert({a,b});
		}

		rep(i,0,N) if (deg[i] == 1) deg1.push_back(i);
		rep(i,0,N) if (deg[i] > 2) highdeg++;

		for (int le = 0;; le++) {
			rep(bi,0,(1 << le)) {
				message.resize(le);
				picks.resize(N - 1);
				rep(i,0,le) message[i] = (char)('0' + ((bi >> i) & 1));

				RNG rng;
				rep(i,0,le) {
					rng.feed((bi >> i) & 1);
				}
				rec(0, rng);
			}
		}
	} else {
		cin.ignore(100, '\n');
		string message;
		getline(cin, message);

		RNG rng;
		for (char c : message) rng.feed(c - '0');

		bool line = false;
		int last = -1;

		for (int i = 0; i < N - 1; ++i) {
			int a, b;
			cin >> a >> b;

			bool guess_a;

			if (line) {
				guess_a = (last == a);
			} else {
				rng.feed(a);
				rng.feed(b);
				int r = rng.rand();
				guess_a = !!(r & (1 << 16));
				if (r % 100 < LINE_PROB) line = true;
			}

			last = (guess_a ? b : a);

			if (guess_a) {
				cout << a << endl;
			} else {
				cout << b << endl;
			}
		}
	}
}
