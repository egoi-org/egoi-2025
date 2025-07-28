#include <bits/stdc++.h>
#define f(i, s, k, l) for (int i = s; i < k; i += l)
#define for0(i, k) f(i, 0, k, 1)

#define pl pair<long long, long long>
#define pb push_back

#define vl vector<long long>
#define vi vector<int>
#define sz(x) (ll)(x).size()
#define all(x) begin(x), end(x)

using namespace std;
using ll = long long;
using ld = long double;


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

    ll n, m, k;
    cin >> n >> m >> k;
    vector<vl> scores(2, vl(m));
    for0(i, n) {
        for0(j, m) cin >> scores[i][j];
        sort(all(scores[i]), greater<ll>());
    }
    ll top = accumulate(all(scores[0]), 0) < accumulate(all(scores[1]), 0);
    vl pref(m + 1, 0);
    for0(i, m) pref[i + 1] = pref[i] + scores[top][i];

    ll sumLow = 0;
    ll best = 2 * m;
    for0(i, m + 1) {
        if (i != 0) sumLow += scores[1 - top][m - i];
        vl::iterator it;
        if (top == 0) it = lower_bound(all(pref), sumLow + (m - i) * k);
        else it = upper_bound(all(pref), sumLow + (m - i) * k);
        if (it == pref.end()) continue;
        best = min(best, (ll) (it - pref.begin() + i));
    }
    cout << best << endl;
}