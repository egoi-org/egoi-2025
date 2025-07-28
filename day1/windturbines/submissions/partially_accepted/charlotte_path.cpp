#include<bits/stdc++.h>

using namespace std;

signed main(){
    int n,m,q;
    cin >> n >> m >> q;;
    vector<array<long long,3>> edges;

    for (int i=0;i<m;++i){
        long long u,v,c;
        cin >> u >> v >> c;
        edges.push_back({u,v,c});
    }
    sort(edges.begin(),edges.end());

   vector<long long> pref(n,0);
   for(int i=1;i<n;++i) {
     pref[i] = pref[i-1]+edges[i-1][2];
   }

    for (int i=0;i<q;++i){
        int l,r;
        cin >> l >> r;
        cout << pref[n-1]-(pref[r]-pref[l])<< '\n';

}
}
