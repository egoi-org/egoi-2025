#include <bits/stdc++.h>

#define int int64_t
#define rep(i, s, e) for(int i = s; i < e; i++)
#define wpr(x) cout << #x << "=" << x << endl
#define pr(x) cout << x << endl
#define upmin(a, b) a = min(a, b)
#define upmax(a, b) a = max(a, b)


using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pi = pair<int, int>;
using vpi = vector<pi>;

template<class A>
ostream& operator<<(ostream& os, const vector<A>& arr) {
    if (arr.empty()) return os << "[]";
    os << "[";
    rep(i, 0, arr.size()) {
        os << arr[i] << ",]"[i==arr.size() - 1];
    }
    return os;
}

/**
 * Solution:
 *
 * For the DAG case:
 * We can use DP.
 * For each node, we will go to its best neighbor,
 * and we will also consider the case that they reverse the graph now.
 * This I believe should be correct.
 *
 * For the general case, I did some none-sense:
 * I used the same DP approach, except that now I sort the nodes in increasing distance from N-1, and calculate the DP
 * in that order.
 * The idea behind this is that generally we want to get closer to N-1, since they can wait until we are
 * very close to N-1 and then reverse the graph.
 * But I don't think it's actually correct. You might want to get a little further from N-1, if it gets you much closer to 0.
 * Moreover, if I'm not mistaken, when I tried one iteration of this approach,
 * my code failed. But when I tried 10 it passed.
 * I'll make some more submission now to check it.
 */
const int INF = 1e9;

int n, m;
vvi g, gr; // The graph, the graph reversed
vi dp;
vi dist_src; // Distance from 0
vi dist_tar; // Distance from N-1

vi bfs(vvi& graph, int start) {
    vi dist;
    dist.resize(n, n+1);
    dist[start] = 0;
    queue<int> q;
    q.push(start);
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (auto nei : graph[u]) {
            if (dist[nei] > dist[u] + 1) {
                dist[nei] = dist[u] + 1;
                q.push(nei);
            }
        }
    }
    return dist;
}

void solve_dag(int u) {
    for (auto nei : g[u]) {
        if (dp[nei] == INF) continue;
        upmin(dp[u], dp[nei] + 1);
    }
    upmax(dp[u], dist_src[u]); // We got stuck at u
}

void solve() {
    cin >> n >> m;
    g.resize(n);
    gr.resize(n);
    rep(i, 0, m) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        gr[v].push_back(u);
    }

    dist_src = bfs(g, 0);
    dist_tar = bfs(gr, n-1);
    vpi order(n-1);
    rep(i, 0, n-1) {
        order[i] = {dist_tar[i], i};
    }

    sort(order.begin(), order.end());

    dp.resize(n, INF);
    dp[n-1] = 0;
    rep(times, 0, 200) {
        for (auto [_, ind] : order) {
            solve_dag(ind);
        }
    }

    rep(i, 0, n-1) {
        cout << dp[i] << " ";
    }
    cout << endl;

}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
