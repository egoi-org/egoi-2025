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

ll INF = (ll) 1e9;

vl bfs(ll start, vector<vl> &adj) {
    vl dist(sz(adj), INF);
    queue<ll> q;
    q.push(start);
    dist[start] = 0;
    while (!q.empty()) {
        ll cur = q.front();
        q.pop();
        for (ll neigh : adj[cur]) {
            if (dist[neigh] != INF) continue;
            q.push(neigh);
            dist[neigh] = dist[cur] + 1;
        }
    }
    return dist;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

    ll n, m, a, b;
    cin >> n >> m;
    vector<vl> adj(n);
    vector<vl> rev(n);
    for0(i, m) {
        cin >> a >> b;
        adj[a].pb(b);
        rev[b].pb(a);
    }

    vl distToExit = bfs(n - 1, rev);
    vl distToStart = bfs(0, adj);

    vl res(n, INF);
    priority_queue<pl, vector<pl>, greater<pl>> pq;
    pq.push({0, n - 1});
    res[n - 1] = 0;
    while (!pq.empty()) {
        auto [d, cur] = pq.top();
        pq.pop();
        if (d != res[cur]) continue;
        for (ll neigh : rev[cur]) {
            ll newd = max(max(distToExit[neigh], distToStart[neigh]), d + 1);
            if (res[neigh] > newd) {
                res[neigh] = newd;
                pq.push({res[neigh], neigh});
            }
        }
    }
    for0(i, n - 1) cout << res[i] << " ";
    cout << endl;

}