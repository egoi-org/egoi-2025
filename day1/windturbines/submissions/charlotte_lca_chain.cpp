#include<bits/stdc++.h>
using ll = long long;

using namespace std;

int log_val = 25;

int find(int a,vector<int> &uf){
    if (uf[a] < 0) return a;
    else uf[a] = find(uf[a],uf);
    return uf[a];
}
void unite(int a, int b,vector<int> &uf){
    int pa = find(a,uf);
    int pb = find(b,uf);

    if(uf[pa]<uf[pb]) {
        uf[pa] += uf[pb];
        uf[pb] = pa;
    } else{
        uf[pb] += uf[pa];
        uf[pa] = pb;
    }

}



signed main(){
    int n,m,q;
    cin >> n >> m >> q;;
    vector<array<int,3>> edges;
    vector<vector<pair<int,int>>> adj_mst(n);
    for (int i=0;i<m;++i){
        int u,v,c;
        cin >> u >> v >> c;
        edges.push_back({c,u,v});
    }
    sort(edges.begin(),edges.end());

    
    ll cost = 0;
    vector<int> uf(n,-1);
    for(auto [c,u,v]:edges){
        if(find(u,uf) != find(v,uf)){
            cost +=c;
            unite(u,v,uf);
            adj_mst[u].push_back({v,c});
            adj_mst[v].push_back({u,c});
        }
    }

    vector<int> level(n,-1);
    vector<vector<int>> lca(n,vector<int>(log_val,-1));
    vector<vector<int>> max_edge(n,vector<int>(log_val,-1));

    auto dfs = [&](const auto &self, int v, int p, int l,int c) -> void{
        level[v] = l;
        lca[v][0] = p;
        max_edge[v][0] = c;
        
        for(int i=1;i<log_val;++i){
            if(lca[v][i-1] != -1){
                lca[v][i] = lca[lca[v][i-1]][i-1];
                max_edge[v][i] = max(max_edge[v][i-1],max_edge[lca[v][i-1]][i-1]);
            }
        }

        for(auto w: adj_mst[v]){
            if(w.first==p){
                continue;
            }
            self(self,w.first,v,l+1,w.second);
        }
    };

    auto find_max = [&](int u, int v) {
        int max_w = 0;

        if (level[u]> level[v]) swap(u,v);

            for(int i=log_val-1; i>=0;--i){
                if(lca[v][i] != -1 && level[lca[v][i]] >= level[u]){
                    max_w = max(max_w,max_edge[v][i]);
                    v = lca[v][i];
            }
        }
        if (v==u) {
            return max_w; 
        } else {
            for (int i=log_val-1;i>=0;--i) {
                if(lca[v][i] != lca[u][i]) {
                    max_w = max(max_w,max(max_edge[v][i],max_edge[u][i]));
                    v = lca[v][i];
                    u = lca[u][i];
                }
            }
        max_w = max(max_w,max(max_edge[v][0],max_edge[u][0]));
        return max_w;
        }
    };

    dfs(dfs,0,-1,0,0);
    
    for(int i=0;i<q;++i) {
        int l,r;
        cin >> l >> r;
        int res = cost;
        
        while(l < r) {
            cost -= find_max(l,r);
            l++;
        }
        cout << res <<'\n';
    }
}
