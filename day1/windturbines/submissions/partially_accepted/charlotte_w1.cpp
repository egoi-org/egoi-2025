#include<bits/stdc++.h>

using namespace std;


const int maxn = 3e5, maxk = 1e6 + 1;
int root[maxn], L[16 * maxn], R[16 * maxn], sum[16 * maxn];
int rt = 1, sz = 1;
int lpos[maxk];

int copy(int v, int &u)
{
    L[sz] = L[v];
    R[sz] = R[v];
    sum[sz] = sum[v];
    return u = sz++;
}

void make_root()
{
    copy(root[rt - 1], root[rt]);
    rt++;
}

void add(int pos, int x, int v = root[rt - 1], int l = 0, int r = maxn)
{
        sum[v] += x;
    if(r - l == 1)
        return;
    int m = (l + r) / 2;
    if(pos < m)
        add(pos, x, copy(L[v], L[v]), l, m);
    else
        add(pos, x, copy(R[v], R[v]), m, r);
}

int get(int a, int b, int v, int l = 0, int r = maxn)
{
    if(a <= l && r <= b)
        return sum[v];
    if(r <= a || b <= l)
        return 0;
    int m = (l + r) / 2;
    return get(a, b, L[v], l, m) + get(a, b, R[v], m, r);
}

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
    cin >> n >> m>>q;
    
    vector<array<int,3>> edges;

    for (int i=0;i<m;++i){
        int u,v,c;
        cin >> u >> v >> c;
        if(c==1) edges.push_back({c,u,v});
    }
    
    vector<int> uf(n,-1);
    for(auto [c,u,v]:edges){
        if(find(u,uf) != find(v,uf)){
            unite(u,v,uf);
        }
    }

    int num_comp = 0;
    for (int i=0;i<n;++i){
        if (find(i,uf)==i) num_comp++;
    }

    for(int i = 1; i <= n; i++)
    {
        int t = find(i-1,uf);
        make_root();
        add(lpos[t], -1);
        lpos[t] = i;
        add(lpos[t], 1);
    }
 
    int l, r;
    while(q--)
    {
        cin >> l >> r;
        l++;
        r++;
        cout << n-(r-l+1)+num_comp-get(l, r + 1, root[r]) << "\n";
    }
    
}
