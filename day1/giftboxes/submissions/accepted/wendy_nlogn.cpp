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
pl check(ll mid, vl &a, vl count, ll atMostOnes) {
    for0(i, mid) {
        count[a[i]]--;
        if (count[a[i]] == 1) atMostOnes++;
    }
    if (atMostOnes == n) return {0, mid - 1};
    for(ll i = mid; i < m; i++) {
        count[a[i - mid]]++;
        if (count[a[i - mid]] == 2) atMostOnes--;
        count[a[i]]--;
        if (count[a[i]] == 1) atMostOnes++;
        if (atMostOnes == n) return {i - mid + 1, i};
    }
    return {-1, -1};
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

    cin >> n >> m;
    vl a(m), count(n, 0);
    ll atMostOnes = n;
    for0(i, m) {
        cin >> a[i];
        count[a[i]]++;
        if (count[a[i]] == 2) atMostOnes--;
    }

    ll l = -1;
    ll r = m;
    pl res;
    while (r - l > 1) {
        ll mid = (l + r) / 2;
        pl newRes = check(mid, a, count, atMostOnes);
        if (newRes.first != -1) {
            r = mid;
            res = newRes;
        }
        else l = mid;
    }
    if (r == 0) cout << -1 << endl;
    else cout << res.first << " " << res.second << endl;
}