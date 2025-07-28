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
    for0(i, n) cin >> a >> b;

    if (n % 2 == 0) cout << n - 2 << endl;
    else cout << n - 1 << endl;

    for (ll i = 2; i < 2 * n; i += 2) {
        if (i == n) continue;
        cout << i / 2 << " " << i + 1 << " " << (1 - i + 2 * n) % (2 * n) << endl;
    }
}