#include <iostream>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)

int main() {
	int phase, n;
	cin >> phase >> n;
	if (phase == 1) {
		cout << "0101" << endl;
	}
	rep(i,0,n-1) cout << i << endl;
}
