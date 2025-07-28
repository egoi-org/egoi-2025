// tries the subtask l_i = 0 by sorting the queries by r_i and then continuesly building the MST up to r_i

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pii pair<int,int>
#define tiii tuple<int,int,int>

vector<int> init(int n){
	vector<int> par(n); 
	iota(par.begin(), par.end(),0); 
	return par;
}

int find(int i, vector<int>& par){
	if(par[i] == i) return i;
	return (par[i] = find(par[i], par));
}

void unite(int i, int j, vector<int>& par){
	i = find(i, par); j = find(j, par);
	par[i] = j;
}

pair<int, vector<tiii> > kruskal(vector<tiii> kanten, int n, vector<int> uf){
	int res = 0;
    vector<tiii> mst;

	sort(kanten.begin(), kanten.end());
	for(tiii kante: kanten){
		int w, a, b;
		tie(w, a, b) = kante;
		if(find(a, uf) != find(b, uf)){
            res += w;
            mst.push_back(kante);
			unite(a, b, uf);
		}
	}

	return {res, mst};
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, q;
    cin >> n >> m >> q;
    vector<vector< pii> > adj(n);
    for(int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }

    vector<pair<int,int> > qs(q);
    
    for(int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        qs[i] = {r, i};
    }

    sort(qs.begin(), qs.end());

    vector<int> uf(n, 0);
    vector<int> res(q);
    vector<vector<pii> > mst(n);

    int sol = 0;
    int last = n-1;
    for(int i = q-1; i >= 0; i--){
        auto [r, k] = qs[i];
        vector<tiii> edges;
        
        for(int j = r+1; j <= last; j++){
            uf[j] = j; 
        }

        for(int j = r+1; j <= last; j++){
            for(auto& [b, w] : mst[j]){
                unite(j, b, uf);
            }
        }
    
        for(int j = r+1; j <= last; j++){
            for(auto& [b, w] : adj[j]){
                if(find(j, uf) == find(b, uf)) continue;
                edges.push_back({w, j, b});
            }
        }

        auto [solp, mst_edges] = kruskal(edges, n, uf);
        sol += solp;
        for(auto& [w, a, b] : mst_edges){
            mst[a].push_back({b, w});
            mst[b].push_back({a, w});
        }

        res[k] = sol;
        last = r;
    }

    for(int i = 0; i < q; i++){
        cout << res[i] << "\n";
    }

    return 0;
}
