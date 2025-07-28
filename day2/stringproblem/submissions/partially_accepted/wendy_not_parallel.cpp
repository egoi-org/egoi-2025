// prints wrong sequence of moves for all test groups, which still gives 50% of points
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

struct endpt {
    ll hair, other;
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

    ll n, a, b;
    cin >> n;

    vector<vl> hair(n, {0, 0});
    vector<endpt> endp(2 * n);

    for0(i, n) {
        cin >> a >> b;
        endp[a] = {i, b};
        endp[b] = {i, a};
    }

    vl countSum(2 * n, 0);
    for0(i, 2 * n) {
        if ((i + endp[i].other) % 2 == 1) countSum[(i + endp[i].other) % (2 * n)]++;
    }
    ll best = max_element(countSum.begin(), countSum.end()) - countSum.begin();
    cout << n - countSum[best] / 2 << endl;

    if (best == 0) best = 1;

    vector<vl> output;
    ll lastCycle = 0;

    for0(i, 2 * n) {
        if ((i + endp[i].other) % (2 * n) == best) continue;
        lastCycle = sz(output);
        ll cur = i;
        ll curBest = (best - cur + 2 * n) % (2 * n);
        endp[endp[cur].other].hair = -1;
        while (endp[curBest].hair != -1) {
            output.pb({endp[cur].hair, endp[cur].other, curBest});
            endp[cur].other = curBest;
            ll next = endp[curBest].other;
            endp[curBest] = {endp[cur].hair, cur};
            cur = next;
            curBest = (best - cur + 2 * n) % (2 * n);
        }
        output.pb({endp[cur].hair, endp[cur].other, curBest});
        endp[cur].other = curBest;
        endp[curBest] = {endp[cur].hair, cur};
    }
    for0(i, lastCycle) cout << output[i][0] << " " << output[i][1] << " " << output[i][2] << endl;
    // no-ops for rest
    for (ll i = lastCycle; i < sz(output); i++) cout << output[i][0] << " " << output[i][1] << " " << output[i][1] << endl;
}
