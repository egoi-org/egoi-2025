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

    if(pa>pb) {
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
    vector<vector<int>> adj_mst(2*n);
    for (int i=0;i<m;++i){
        int u,v,c;
        cin >> u >> v >> c;
        edges.push_back({c,u,v});
    }
    sort(edges.begin(),edges.end());
    vector<int> rep(n);
    iota(rep.begin(),rep.end(),0);
    
    ll cost = 0;
    vector<int> edge_costs(2*n);
    vector<int> uf(2*n,-1);
    int ins = n;
    for(auto [c,u,v]:edges){
        int ru = find(u,uf);
        int rv = find(v,uf);
        if(ru != rv){
            cost +=c;
            edge_costs[ins] = c;
            unite(u,v,uf);
            unite(u,ins,uf);
            //fprintf(stderr,"connect %d and %d in %d\n",ru,rv,ins);
            adj_mst[ins].push_back(ru);
            adj_mst[ins].push_back(rv);
            adj_mst[ru].push_back(ins);
            adj_mst[rv].push_back(ins);
            ins++;
        }
    }

    vector<int> level(2*n,-1);
    vector<vector<int>> lca(2*n,vector<int>(log_val,-1));
    vector<int> preorder(2*n,0);
    int pre = 0;
    auto dfs = [&](const auto &self, int v, int p, int l) -> void{
        level[v] = l;
        lca[v][0] = p;
        preorder[v] = pre;
        pre++;
        
        //fprintf(stderr,"vertex %d, level %d, parent %d, preorder %d\n",v,l,p,pre);
        for(int i=1;i<log_val;++i){
            if(lca[v][i-1] != -1){
                lca[v][i] = lca[lca[v][i-1]][i-1];
            }
        }

        for(auto w: adj_mst[v]){
            if(w==p){
                continue;
            }
            self(self,w,v,l+1);
        }
    };

    auto find_max = [&](int u, int v) {

        if (level[u]> level[v]) swap(u,v);

            for(int i=log_val-1; i>=0;--i){
                if(lca[v][i] != -1 && level[lca[v][i]] >= level[u]){
                    v = lca[v][i];
            }
        }
        assert(level[u]==level[v]);
        //fprintf(stderr,"levels %d, vertices %d %d\n",level[u],u,v);
        if (v==u) {
            return u; 
        } else {
            for (int i=log_val-1;i>=0;--i) {
                if(lca[v][i] != lca[u][i]) {
                    v = lca[v][i];
                    u = lca[u][i];
                }
            }
        return lca[u][0];
        }
    };

    dfs(dfs,2*n-2,-1,0);
    
    for(int i=0;i<q;++i) {
        int l,r;
        cin >> l >> r;
        //fprintf(stderr,"strating Query %d - %d\n",l,r);
        vector<int> range(r+1-l);
        iota(range.begin(),range.end(),l);
        sort(range.begin(), range.end(), [&](int a, int b) { 
            return preorder[a] < preorder[b]; });
        
        ll del = 0;
        for(int i=1;i<=r-l;++i){
            int lca = find_max(range[i-1],range[i]);
            //fprintf(stderr,"lca of %d and %d is %d\n",range[i-1],range[i],lca);
            del += edge_costs[lca];
        }

        cout << cost - del <<'\n';
    }
}
