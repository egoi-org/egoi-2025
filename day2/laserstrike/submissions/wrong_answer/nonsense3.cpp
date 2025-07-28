#include <vector>
#include <iostream>
#include <string>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
typedef vector<int> vi;

int main() {
	int phase, n;
	cin >> phase >> n;
	if (phase == 1) {
		vi deg(n), xors(n);
		rep(i,1,n) {
			int x,y;
			cin>>x>>y;
			++deg[x];
			++deg[y];
			xors[x] ^= y;
			xors[y] ^= x;
		}

		vi deg1;
		rep(x,0,n) if (deg[x] == 1)
			deg1.push_back(x);

		vi out;
		rep(_,1,n) {
			int x = deg1.back();
			deg1.pop_back();
			int y = xors[x];
			xors[x] ^= y;
			xors[y] ^= x;
			deg[x] -= 1;
			deg[y] -= 1;
			if (deg[y] == 1)
				deg1.push_back(y);
			out.push_back(x);
		}

		cout << "010" << endl;
		for (int x : out) cout << x << endl;
	} else {
		string help;
		cin >> help;
		rep(i,1,n) {
			int a, b;
			cin >> a >> b;
			cout << "aaa" << endl;
		}
	}
}
