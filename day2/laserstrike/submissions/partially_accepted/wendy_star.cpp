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

    ll p, n, a, b, s;
    cin >> p >> n;

    if (p == 1) {
        vl deg(n, 0);
        ll root = 0;
        for0(i, n - 1) {
            cin >> a >> b;
            deg[a]++;
            if (deg[a] > 1) root = a;
            deg[b]++;
            if (deg[b] > 1) root = b;
        }
        if (root == n - 1) {
                cout << 1 << endl;
                for0(i, n - 1) cout << i << endl;
            }
        else {
                cout << 0 << endl;
                for (ll i = root + 1; i < n; i++) cout << i << endl;
                for0(i, root) cout << i << endl;
            }
    } else {
        cin >> s;
        if (s == 1) {
            for0(i, n - 1) {
                cin >> a >> b;
                if (a != n - 1) cout << a << endl;
                else cout << b << endl;
            }
        } else {
            cin >> a >> b;
            ll root = min(a, b);
            if (a != root) cout << a << endl;
            else cout << b << endl;
            for0(i, n - 2) {
                cin >> a >> b;
                if (a != root) cout << a << endl;
                else cout << b << endl;
            }
        }
    }
}