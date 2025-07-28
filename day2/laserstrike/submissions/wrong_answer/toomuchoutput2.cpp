#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define trav(a, x) for (auto& a : x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int P, N;
	cin >> P >> N;
	if (P == 1) {
		vi ed(N), deg(N);
		rep(i,0,N-1) {
			int a, b;
			cin >> a >> b;
			ed[a] ^= b;
			ed[b] ^= a;
			deg[a]++;
			deg[b]++;
		}
		vi deg1;
		rep(i,0,N) if (deg[i] == 1) deg1.push_back(i);
		string help;
		vi out;
		rep(qi,0,N-1) {
			int x = deg1.back();
			deg1.pop_back();
			int y = ed[x];
			ed[x] ^= y, ed[y] ^= x;
			deg[x]--, deg[y]--;
			if (deg[y] == 1) deg1.push_back(y);
			help += (char)(x < y ? '0' : '1');
			out.push_back(x);
		}
		cout << help << endl;
		trav(x, out) {
			cout << x << endl;
		}
	} else {
		string help;
		cin >> help;
		rep(qi,0,N-1) {
			int a, b;
			cin >> a >> b;
			if (a > b) swap(a, b);
			int leaf = (help[qi] == '0' ? a : b);
			cout << leaf << endl;
		}
		cout << "0" << endl;
	}
}
