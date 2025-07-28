#include<bits/stdc++.h>

using namespace std;

// variable number of bits: b
string int_to_bits(int n, int b) {
    string s;
    for( int i=0;i<b;++i){
        if(n%2) s.push_back('1');
        else s.push_back('0');
        n /= 2;
    }
    return s;
}

int bits_to_int(string s,int b,int i){
    int res = 0;
    for(int j=b-1;j>=0;--j){
        res *=2;
        if(s[i+j] == '1') res++;
    }
    return res;
}



signed main() {
    int n,p;
    cin >> p >> n;

    if (p==1) {
        vector<set<int>> adj(n);
        vector<int> deg(n,0);
        for(int i=0;i<n-1;++i){
            int u,v;
            cin >> u >> v;
            adj[u].insert(v);
            adj[v].insert(u);
            deg[u]++;
            deg[v]++;
        }
        cerr << "deg: " << deg[897] << '\n';  
        vector<int> parent(n,-1);
        auto dfs = [&](const auto &self,int v, int p)-> void {
            parent[v] = p;
            for (int w:adj[v]) {
                if (w != p) self(self,w,v);
            }
        };

        dfs(dfs,n-1,-1);

        int numv = n;
        vector<int> leaf_l;
        vector<int> leaf_s;

        vector<int> path_l;
        vector<int> path_s;
        int counts_pl=0;
        int counts_ps = 0;
        vector<int> seen(n,0);
        for(int i=0;i<n-1;++i){
                if(deg[i]==1){
                    if (deg[parent[i]] > 2){
                        if (i < parent[i]) {
                            leaf_s.push_back(i);
                        } else {
                            leaf_l.push_back(i);
                        }
                        deg[parent[i]]--;
                        seen[i]=1;
                    }
                cerr << "leaf at " << parent[i] << '\n';
                }
        }
        for(int i=0;i<n-1;++i){
                if(seen[i]) continue;
                if(deg[i]==1){
                    cerr << "starting path\n";
                    // the next vertex has deg == 2 
                    if (i < parent[i]) {
                        int u = parent[i];
                        path_s.push_back(i);
                        cerr << i << ' ';
                        while(deg[u] == 2 && u != n-1) {
                            path_s.push_back(u);
                            cerr << u << ' ';
                            u = parent[u];
                        }
                        deg[u]--;
                        counts_ps ++;
                        seen[u]=1;
                        cerr << "\nended at vertex " << u << '\n';

                    }
                }
        }
        for(int i=0;i<n-1;++i) {
                if(seen[i]) continue;
                if(deg[i]==1){
                    if(parent[i]<i){
                        int u = *adj[i].begin();
                        path_l.push_back(i);
                        cerr << i << ' ';
                        while(deg[u] == 2 && u != n-1) {
                            path_l.push_back(u);
                            cerr << u << ' ';
                            u = parent[u];
                        }
                        counts_pl++;   
                        deg[u]--;
                        seen[u]=1;
                        cerr << "\nended at vertex " << u << '\n';
                    }
                }
        }
        
        
        cout << int_to_bits(leaf_s.size(),10);
        cout << int_to_bits(leaf_l.size(),10);
        cout << int_to_bits(counts_ps,10);
        
        cout << '\n';
        cerr << (leaf_l.size()+leaf_s.size()+path_l.size()+path_s.size())<< '\n';
        assert((leaf_l.size()+leaf_s.size()+path_l.size()+path_s.size())==n-1);
        for(int l:leaf_s){
            cout << l << '\n';
        }
        for(int l:leaf_l){
            cout << l << '\n';
        }
        for(int l:path_s){
            cout << l << '\n';
        }
        for(int l:path_l){
            cout << l << '\n';
        }


    } else if (p==2) {
        char m;

        string k;
        cin >> k;
        int i=0;
        int leaf_s = bits_to_int(k,10,i);
        i += 10;
        int leaf_l = bits_to_int(k,10,i);
        i += 10;
        int path_s = bits_to_int(k,10,i);
        i += 10;
        
        vector<int> seen(n,0);
        int u,v;
        cin >> u >> v;
        int read = 1;
        for(int i=0; i<leaf_s;++i) {
            cout << min(u,v) << endl;
            cin >> u >> v;
            read++;
        }
    
        for(int i=0; i<leaf_l;++i) {
            cout << max(u,v) << endl;
            cin >> u >> v;
            read++;
        }
        for(int i=0;i<path_s;++i){
            vector<int> seen(n,0);
            cout << min(u,v) << endl;
            int prev = max(u,v);
            seen[u]=1;
            seen[v]=1;
            if(read==n-1) return 0;
            cin >> u >> v;
            read ++;
            while((seen[u]==1 || seen[v]==1 )&& prev != n-1){
                cout << prev << endl;
                if(seen[u]==1) prev=v;
                else prev=u;
                seen[u] ++;
                seen[v] ++;
                if (read == n-1) return 0;
                cin >> u >> v;
                read++;
            }
            
        }
        cerr << "done smaller" << '\n';
        while(read<n) {
            vector<int> seen(n,0);
            cout << max(u,v) << endl;
            int prev = min(u,v);
            seen[u]=1;
            seen[v]=1;
            if (read==n-1) return 0;
            cin >> u >> v;
            read ++;
            while((seen[u]==1 || seen[v]==1 )&& prev != n-1){
                cout << prev << endl;
                if(seen[u]==1) prev=v;
                else prev=u;
                seen[u] ++;
                seen[v] ++;
                if (read == n-1) return 0;
                cin >> u >> v;
                read++;
            }
            
        }
        cerr << "done larger" << '\n';


    }
}
