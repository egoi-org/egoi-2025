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
        int numv = n;
        int counts=0;
        vector<int> rem;

        int counts2 = 0;
        vector<int> rem2;

        vector<int> rem3;
        vector<int> seen(n,0);
        int star_mode = 0;
        int len = 0;
        for(int i=0;i<n;++i){
                if (seen[i]) continue;
                if(deg[i]==1){
                    if (deg[*adj[i].begin()] > 2){
                        if (rem3.size()==0){
                            star_mode = i < *adj[i].begin();
                        }
                        rem3.push_back(i);
                    }
                    else if (i < *adj[i].begin()) {
                        int u = *adj[i].begin();
                        rem.push_back(i);
                        cerr << i << ' ';
                        int p = i;
                        len ++;
                        while(deg[u] == 2) {
                            rem.push_back(u);
                            cerr << u << ' ';
                            len ++;
                            int old_p = p;
                            p = u;
                            u = (*adj[u].begin() == old_p? *prev(adj[u].end()):*adj[u].begin());
                        }
                        seen[u]=1;
                        cerr << "seen " << u;
                        counts ++;

                    }
                    else {
                        int u = *adj[i].begin();
                        rem2.push_back(i);
                        cerr << i << ' ';
                        int p = i;
                        len ++;
                        while(deg[u] == 2) {
                            rem2.push_back(u);
                            cerr << u << ' ';
                            len ++;
                            int old_p = p;
                            p = u;
                            u = (*adj[u].begin() == old_p? *prev(adj[u].end()):*adj[u].begin());
                        }
                        seen[u]=1;
                        counts2++;   
                    }
                    cerr << '\n';
                }
        }
        int b = (32-__builtin_clz(max(counts,counts2)));
        assert(b<=10);
        cout << int_to_bits(b,4);
        cout << int_to_bits(counts,b);
        cout << int_to_bits(counts2,b);
        if (counts+counts2==0) cout << star_mode;
        if (counts+counts2==1) cout << int_to_bits(len,10);
        
        cout << '\n';
        cerr << (rem.size()+rem2.size()+rem3.size())<<'\n';
        assert((rem.size()+rem2.size()+rem3.size())==n-1);
        for(int l:rem){
            cout << l << '\n';
        }
        for(int l:rem2){
            cout << l << '\n';
        }
        for(int l:rem3){
            cout << l << '\n';
        }


    } else if (p==2) {
        char m;

        string k;
        cin >> k;
        
        int i=0;
        int b = bits_to_int(k,4,i);
        i += 4;
        int counts = bits_to_int(k,b,i);
        i += b;
        int counts2 = bits_to_int(k,b,i);
        i += b;
        int star_mode = 0;
        int len=-1;
        if (counts+counts2==0) star_mode = bits_to_int(k,1,i);
        if (counts+counts2==1) len = bits_to_int(k,10,i);
        
        vector<int> seen(n,0);
        int u,v;
        cin >> u >> v;
        int read = 1;
        for(int i=0; i<counts;++i) {
            cout << min(u,v) << endl;
            len --;
            int prev = max(u,v);
            seen[u]=1;
            seen[v]=1;
            cin >> u >> v;
            read ++;
            while((seen[u]==1 || seen[v]==1) && abs(len)!= 0){
                cout << prev << endl;
                len --;
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
        for(int i=0; i<counts2;++i) {
            cout << max(u,v) << endl;
            len --;
            int prev = min(u,v);
            seen[u]=1;
            seen[v]=1;
            cin >> u >> v;
            read ++;
            while((seen[u]==1 || seen[v]==1) && abs(len)!= 0){
                cout << prev << endl;
                len --;
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
        int center = -1;
        while(read<n) {
            cerr << read << '\n';
            if (seen[u] || center == u) cout << v << endl;
            else if (seen[v] || center == v) cout << u << endl;
            else if (center==-1) {
                cout << (star_mode ? min(u,v):max(u,v))<<endl;
                center = (star_mode ? max(u,v):min(u,v));
            }
            if (read == n-1) break;
            read++;
            cin >> u >> v;
        }


    }
}
