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
using pt = complex<ld>;

random_device rd;
mt19937 g(rd());

ll n;
ll query(vl &x, ll start, ll end) {
    string s(n,'0');
    for (ll i = start; i < end; i++) s[x[i]] = '1';
    cout << "? " << s << endl;
    ll ans;
    cin >> ans;
    return ans;
}

ll findSwitch(vl &a) {
    ll l = 0;
    ll r = sz(a);
    while (r - l > 1) {
        ll mid = (l + r) / 2;
        if (query(a, l, mid) % 2 == 1) r = mid;
        else l = mid;
    }
    return a[l];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

    cin >> n;
    vl a(n);
    for0(i, sz(a)) a[i] = i;
    shuffle(a.begin(), a.end(), g);
    ll q = query(a, 0, sz(a) / 2);

    vector<set<ll>> log;
    while (q % 2 != 1) {
        set<ll> qu;
        for0(i, sz(a) / 2) qu.insert(a[i]);
        log.pb(qu);

        shuffle(a.begin(), a.end(), g);
        q = query(a, 0, sz(a) / 2);
    }
    vl x, y;
    for0(i, sz(a) / 2) x.pb(a[i]);

    ll res1 = findSwitch(x);
    set<ll> never, must;
    never.insert(res1);
    for(auto s : log) {
        if (s.count(res1) == 0) {
            for (auto x : s) never.insert(x);
        } else {
            for (auto x : s) must.insert(x);
        }
    }
    if (must.empty()) {
        for0(i, sz(a)) must.insert(i);
    }
    for (auto x : never) must.erase(x);

    for(ll i = sz(a) / 2; i < n; i++) {
        if (must.count(a[i])) y.pb(a[i]);
    }
    ll res2 = findSwitch(y);
    cout << "! " << res1 << " " << res2 << endl;
}
