#include<bits/stdc++.h>
#define int long long

using namespace std;

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

    for (int i=0;i<m;++i){
        int u,v,c;
        cin >> u >> v >> c;
        edges.push_back({c,u,v});
    }
    sort(edges.begin(),edges.end());

    
    for (int i=0;i<q;++i){
        int l,r;
        cin >> l >> r;
        vector<int> uf(n,-1);
        
        for(int j=l+1;j<=r;++j){
            unite(j-1,j,uf);
        }

        int cost = 0;

        for(auto [c,u,v]:edges){
            if(find(u,uf) != find(v,uf)){
                cost +=c;
                unite(u,v,uf);
            }
        }
        bool res = true;
        for(int j=1;j<n;++j){
            if(find(j-1,uf)!=find(j,uf)){
                res = false;
            }
        }
        if(res) cout << cost <<'\n';
        else cout << -1 << '\n';
    }
}
