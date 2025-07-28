#include<bits/stdc++.h>

using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define pb push_back

struct block{
    int sz;    //num of cards
    int cost;  //max number
    vvi cards; //numbers start at 1
};

block unite(block b1, block b2){
    block b;
    b.sz=b1.sz+b2.sz;
    b.cost=b1.cost+b2.cost;
    b.cards=b1.cards;
    for (vi v:b2.cards){
        for (int &x:v) x+=b1.cost;
        b.cards.pb(v);
    }
    return b;
}

vvi subsets(int n, int m){ //returns subsets of {0,...,n-1} of size m
    vi v(n,1);
    for (int i=0;i<n-m;i++) v[i]=0;
    vvi ans;
    do{
        vi toadd;
        for (int i=0;i<n;i++) if (v[i]) toadd.pb(i);
        ans.pb(toadd);
    }
    while(next_permutation(v.begin(),v.end()));
    return ans;
}

int N = 12;

//partition in blocks of size d, leave ord blocks without choosing
block basic_block(int d, int ord){
    block b;
    int m = b.cost = N+d*ord;
    int nblocks = m/d;
    for (vi subset:subsets(nblocks,nblocks-ord)){
        vi toadd;
        for (int chosenblock:subset){
            for (int res=0;res<d;res++) toadd.pb(chosenblock*d+res+1);
        }
        b.cards.pb(toadd);
    }
    b.sz=b.cards.size();
    return b;
}

int M = 100; // max card
int K = 100; // max player

int main(){
    vector<block> v; // vector with the basic blocks
    v.pb(basic_block(N,0)); //trivial block
    for (int d=1;d<=N;d++) if (N%d==0) {
        for (int ord=1;1;ord++){
            block b = basic_block(d,ord);
            if (b.cost>K || b.sz>M) break;
            v.pb(b);
        }
    }

    block UNDEF;
    UNDEF.sz=0;
    UNDEF.cost=M+1;

    vector<block> dp(M+1,UNDEF);
    dp[0].sz = 0;
    dp[0].cost = 0;

    for (block b:v){
        for (int i=b.sz;i<=K;i++)
            if (dp[i-b.sz].cost + b.cost < dp[i].cost) dp[i] = unite(dp[i-b.sz], b);
    }

    int n;
    cin >> n;
    for (vi w:dp[n].cards){
        for (int x:w) cout << x-1 << ' ';
        cout << '\n';
    }

	// use for checking stats
    // int c=0;
    // for (int i=1;i<=K;i++) c+=(dp[i].cost)<=100;
    // cerr << c << '\n';

    // for (int i=1;i<=K;i++) cerr << i << ": " << dp[i].cost << '\n';
}
