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

ll n, m;
pl check(ll mid, vl &a) {
    for0(i, m - mid + 1) {
        vl count(n, 0);
        for0(j, i) count[a[j]]++;
        for (ll j = i + mid; j < m; j++) count[a[j]]++;
        bool ok = true;
        for0(j, n) {
            if (count[j] > 1) ok = false;
        }
        if (ok) return {i, i + mid - 1};
    }
    return {-1, -1};
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

    cin >> n >> m;
    vl a(m);
    for0(i, m) cin >> a[i];

    ll l = -1;
    ll r = m;
    pl res;
    while (r - l > 1) {
        ll mid = (l + r) / 2;
        pl newRes = check(mid, a);
        if (newRes.first != -1) {
            r = mid;
            res = newRes;
        }
        else l = mid;
    }
    if (r == 0) cout << -1 << endl;
    else cout << res.first << " " << res.second << endl;
}