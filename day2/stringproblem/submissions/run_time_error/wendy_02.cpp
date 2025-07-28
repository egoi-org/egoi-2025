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

    vector<pl> hair;

    for0(i, n) {
        cin >> a >> b;
        hair.pb({a, b});
    }

    map<ll, vl> countAngles;
    for0(i, n) countAngles[(hair[i].first + hair[i].second) % (2 * n)].pb(i);
    if (sz(countAngles) == 1) {
        cout << 0 << endl;
        return 0;
    }
    cout << 2 << endl;
    ll best = 0;
    vl fix;
    for (auto x : countAngles) {
        if (sz(x.second) == n - 2) best = x.first;
        else {
            for (auto h : x.second) fix.pb(h);
        }
    }
    pl h0 = hair[fix[0]];
    pl h1 = hair[fix[1]];
    if ((h0.first + h1.first) % (2 * n) == best) {
        cout << fix[0] << " " << h0.second << " " << h1.first << endl;
        cout << fix[1] << " " << h1.first << " " << h0.second << endl;
    } else if ((h0.first + h1.second) % (2 * n) == best) {
        cout << fix[0] << " " << h0.second << " " << h1.second << endl;
        cout << fix[1] << " " << h1.second << " " << h0.second << endl;
    }
}