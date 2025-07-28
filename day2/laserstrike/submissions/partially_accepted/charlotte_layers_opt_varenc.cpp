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
        vector<set<int>> adj2 = adj;
        vector<int>deg2 = deg;
        int numv = n;
        vector<unsigned int> counts;
        vector<int> rem;
        int mode = 1;

        while(numv>1) {
            unsigned int count = 0;
            int seen = 0;
            while(seen<n){
                for(int i=0;i<n;++i){
                if(deg[i]==1 && mode*i < mode*(*adj[i].begin())) {
                    int u = *adj[i].begin();
                    count++;
                    rem.push_back(i);
                    deg[i]--;
                    deg[u]--;
                    adj[u].erase(i);
                    seen = 0;
                } else {
                seen++;
                }
            }
            }
            counts.push_back(count);
            numv -= count;
            mode *= -1;
        }
        numv = n;
        vector<unsigned int> counts2;
        vector<int> rem2;
        mode = -1;

        while(numv>1) {
            unsigned int count = 0;
            int seen = 0;
            while(seen<n){
                cerr << seen << '\n';
                for(int i=0;i<n;++i){
                if(deg2[i]==1 && mode*i < mode*(*adj2[i].begin())) {
                    int u = *adj2[i].begin();
                    count++;
                    rem2.push_back(i);
                    deg2[i]--;
                    deg2[u]--;
                    adj2[u].erase(i);
                    seen = 0;
                } else {
                seen++;
                }
            }
            }
            counts2.push_back(count);
            numv -= count;
            mode *= -1;
        }
        unsigned int max1 = *max_element(counts.begin(),counts.end());
        unsigned int max2 = *max_element(counts2.begin(),counts2.end());
        cerr << __builtin_clz(max1) << ' ' << max1 << '\n';
        if ((32-__builtin_clz(max1))*counts.size() < (32-__builtin_clz(max2))*counts2.size()) {
            int b = (32-__builtin_clz(max1));
            assert(b<=10);
            cout<<0;
            cout << int_to_bits(b,4);
            for(int c:counts){
                cout << int_to_bits(c,b);
            }
            cout << '\n';
            assert(rem.size()==n-1);
            for(int l:rem){
                cout << l << '\n';
            }
        } else {
            int b = (32-__builtin_clz(max2));
            assert(b<=10);
            cout<<1;
            cout << int_to_bits(b,4);
            for(int c:counts2){
                cout << int_to_bits(c,b);
            }
            cout << '\n';
            assert(rem2.size()==n-1);
            for(int l:rem2){
                cout << l << '\n';

            }
        }

    } else if (p==2) {
        char m;
        cin >> m;

        string k;
        cin >> k;
        
        int mode = 1-2*(m=='1');
        int i=0;
        int b = bits_to_int(k,4,i);
        i += 4;
        while(i<k.size()){
            int c = bits_to_int(k,b,i);
            i += b;
            for(int j=0;j<c;++j){
                int u,v;
                cin >> u >> v;
                if(mode*u < mode*v) cout << u << endl;
                else cout << v << endl;
            }
            mode *= -1;
        }

    }


}
