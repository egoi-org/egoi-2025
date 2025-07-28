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

string toBinary(ll x, ll length) {
    string s;
    while (x > 0) {
        s.pb((x & 1) + '0');
        x = x >> 1;
    }
    while (sz(s) < length) s.pb('0');
    reverse(s.begin(), s.end());
    return s;
}

ll toNumber(string s) {
    ll res = s[0] - '0';
    for (ll i = 1; i < sz(s); i++) {
        res *= 2;
        res += s[i] == '1';
    }
    return res;
}

vl deg;
vector<vl> adj;

ll getParent(ll v) {
    assert(deg[v] <= 1);
    for0(i, sz(adj[v])) {
        if (deg[adj[v][i]] != 0) return adj[v][i];
    }
    return -1;
}

bool smallerThanParent(ll v) {
    assert(deg[v] <= 1);
    ll parent = getParent(v);
    assert(parent != -1);
    return v < parent;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

    ll p, n, a, b;
    cin >> p >> n;

    adj.resize(n);
    deg.resize(n, 0);

    if (p == 1) {
        for0(i, n - 1) {
            cin >> a >> b;
            adj[a].pb(b);
            adj[b].pb(a);
            deg[a]++;
            deg[b]++;
        }
        vl curLeaves, numbers;
        bool smallPass = true;

        while (sz(curLeaves) < n - 1) {
            ll curNumber = 0;
            for0(i, n) {
                ll cur = i;
                while (deg[cur] == 1 && sz(curLeaves) < n - 1) {
                    // cout << cur << " " << getParent(cur) << endl;
                    if (smallerThanParent(cur) != smallPass) break;
                    deg[cur] = 0;
                    curLeaves.pb(cur);
                    curNumber++;
                    if (sz(curLeaves) == n - 1) break;
                    deg[getParent(cur)]--;
                    cur = getParent(cur);
                }
            }
            numbers.pb(curNumber);
            smallPass = !smallPass;
        }
        numbers.pop_back();

        ll biggestNumber = max(2ll, *max_element(numbers.begin(), numbers.end()));
        ll length = (ll) ceil(log2(biggestNumber));

        cout << toBinary(length, 4);
        for (ll x : numbers) cout << toBinary(x, length);
        cout << endl;
        for (ll v : curLeaves) cout << v << endl;
        return 0;
    }

    string s;
    cin >> s;
    queue<ll> q;
    ll count = 0;
    ll length = toNumber(s.substr(0, 4));
    if (length > 0) {
        for0(i, (sz(s) - 4) / length) {
            ll num = toNumber(s.substr(i * length + 4, length));
            count += num;
            q.push(num);
        }
    }
    q.push(n - 1 - count);
    bool smallPass = true;
    while (!q.empty()) {
        while (q.front() > 0) {
            cin >> a >> b;
            if (smallPass) cout << min(a, b) << endl;
            else cout << max(a, b) << endl;
            q.front()--;
        }
        q.pop();
        smallPass = !smallPass;
    }

}