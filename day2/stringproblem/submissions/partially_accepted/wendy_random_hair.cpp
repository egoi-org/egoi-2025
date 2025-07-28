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

    vector<endpt> endp(2 * n);

    for0(i, n) {
        cin >> a >> b;
        endp[a] = {i, b};
        endp[b] = {i, a};
    }

    vector<endpt> cp = endp;
    vector<vl> output;
    ll res = n + 1;
    mt19937 rng(1);
    uniform_int_distribution<ll> distr(0, 2 * n - 1);
    vector<vl> bestOutput;
    int times = clock();
    while (1000 * (clock() - times) / CLOCKS_PER_SEC < 900) {
        output.clear();
        endp = cp;
        ll rand = distr(rng);
        ll best = (rand + endp[rand].other) % (2 * n);
        if (best % 2 != 1) continue;
        bool poss = true;
        for0(i, 2 * n) {
            if ((i + endp[i].other) % (2 * n) == best) continue;
            ll cur = i;
            ll curBest = (best - cur + 2 * n) % (2 * n);
            endp[endp[cur].other].hair = -1;
            while (endp[curBest].hair != -1 && poss) {
                output.pb({endp[cur].hair, endp[cur].other, curBest});
                endp[cur].other = curBest;
                ll next = endp[curBest].other;
                if (cur == next) poss = false;
                endp[curBest] = {endp[cur].hair, cur};
                cur = next;
                curBest = (best - cur + 2 * n) % (2 * n);
            }
            if (!poss) break;
            output.pb({endp[cur].hair, endp[cur].other, curBest});
            endp[cur].other = curBest;
            endp[curBest] = {endp[cur].hair, cur};
        }
        if (poss && sz(output) < res) {
            res = sz(output);
            bestOutput = output;
        }
    }
    cout << res << endl;
    for0(i, sz(bestOutput)) cout << bestOutput[i][0] << " " << bestOutput[i][1] << " " << bestOutput[i][2] << endl;

}