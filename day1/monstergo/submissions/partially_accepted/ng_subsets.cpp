#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef long double ld;

const int N = 100;
const int K = 12;

int n;

int BIN[301][301] = {0};

vector<vi> gen_subsets(int a, int b){
    if(a < b)return {};
    if(b == 0)return {{}};
    vector<vi> res = gen_subsets(a-1, b);
    vector<vi> s2 = gen_subsets(a-1, b-1);
    trav(v, s2){
        vi w = v;
        w.push_back(a-1);
        res.push_back(w);
    }
    return res;
}

struct block{
    int b, groups, cost;

    void print(int start){
        vi V;
        vi GI;
        rep(c1,0,cost){
            V.push_back(start-c1);
            GI.push_back(c1/b);
        }
        vector<vi> ss = gen_subsets(groups, K/b);
        trav(v, ss){
            trav(i, v){
                rep(c1,0,cost){
                    if(GI[c1] == i){
                        cout << V[c1] << " ";
                    }
                }
            }
            cout << "\n";
        }
    }
};

vector<block> blocks;

int main() { 

    rep(c1,0,301){
        rep(c2,0,301){
            if(c1 < c2){
                BIN[c1][c2] = 0;
            }
            else{
                if(c2 == 0 || c2 == c1){
                    BIN[c1][c2] = 1;
                }
                else{
                    BIN[c1][c2] = BIN[c1-1][c2] + BIN[c1-1][c2-1];
                }
            }

            if(BIN[c1][c2] > N)BIN[c1][c2] = N+1;

            if(c2 != 0 && K%c2 == 0 && BIN[c1][c2] <= N && BIN[c1][c2] != 0){
                int b = K/c2;
                int cost = b * c1;
                if(cost <= N){
                    block B = {b, c1, cost};
                    blocks.push_back(B);
                }
            }

        }
    }

    cin >> n;

    trav(B, blocks){
        int x = BIN[B.groups][K/B.b];
        if(x == n){
            B.print(45);
            return 0;
        }
    }

    return 0;  
}
