#include <bits/stdc++.h>
#define f(i, s, k, l) for (int i = s; i < k; i += l)
#define for0(i, k) f(i, 0, k, 1)

#define pl pair<long long, long long>
#define pb push_back

#define vl vector<long long>
#define vi vector<int>
#define sz(x) (ll)(x).size()

using namespace std;
using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

    ll n, a, b;
    cin >> n;
    cout << n - (n % 2 == 1) << endl;
    for0(i, n) {
        if (i + n == (2 * n - 1 - i)  % (2 * n)) continue;
        cout << i << " " << i + n << " " << (2 * n - 1 - i)  % (2 * n) << endl;
    }
}