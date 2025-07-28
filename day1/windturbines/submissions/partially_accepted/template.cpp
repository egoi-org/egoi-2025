#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<array<long long,3>> edges;

    for (int i = 0; i < M; ++i) {
        int u, v;
        long long c;
        cin >> u >> v >> c;
        edges.push_back({u,v,c});
    }

    sort(edges.begin(),edges.end());
    vector<long long> pref(N,0);
    for(int i=1;i<N;++i) {
        pref[i] = pref[i-1]+edges[i-1][2];
    }
    vector<long long> ans(Q, 0);
    for (int i = 0; i < Q; ++i) {
        int l, r;
        cin >> l >> r;
        ans[i] = pref[N-1]-(pref[r]-pref[l]);
    }


    for (int i = 0; i < Q; ++i)
        cout << ans[i] << endl;

    return 0;
}

