// first builds the MST, then for each query, if the query has size k, just removes the k heaviest edges from the MST

#include <bits/stdc++.h>
using namespace std;

#define int long long
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

vector<tiii> kruskal(vector<tiii> kanten, int n){
	vector<tiii> res;

	sort(kanten.begin(), kanten.end());
	vector<int> uf = init(n);
	for(tiii kante: kanten){
		int w, a, b;
		tie(w, a, b) = kante;
		if(find(a, uf) != find(b, uf)){
			res.push_back(kante);
			unite(a, b, uf);
		}
	}

	return res;
}

int32_t main(){
    ios::sync_with_stdio(false);
    int n, m, q;
    cin >> n >> m >> q;
    vector<tiii> edges(m);
    for(int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w;
        edges[i] = {w, a, b}; 
    }
    
    vector<tiii> mst = kruskal(edges, n);

    vector<int> pref_sums(n, 0);
    for(int i = 0; i < n - 1; i++){
        pref_sums[i + 1] = pref_sums[i] + get<0>(mst[i]);
    }

    
    for(int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        cout << pref_sums[n -1 - (r - l)] << endl;
    }

    return 0;
}
