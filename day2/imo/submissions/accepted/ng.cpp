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

const int MAXN = 20001;
const int MAXM = 101;
const int MAXK = 101;
const int inf = 1000000007;

int n,m,k;
vector<vi> A;
vi ind;
vi PREV;
vi score;
vi MH;

vector<vector<vi> > HIDE; // HIDE[i][count] - vector of scores that 
                          // can be hidden by hiding "count" scores. 

int DP1[2][MAXK*MAXM+1][MAXM+1] = {0};
int DP2[2][MAXK*MAXM+1] = {0};
bool non_strict[MAXN] = {0};

bool comp(int i, int j){
    if(score[i] == score[j])return i > j;
    return score[i] < score[j];
}

int leq(vi &X, int y){
    if(sz(X) == 0 || y < X[0])return -1;
    if(X.back() <= y)return X.back();
    int lo = 0;
    int hi = sz(X);
    while(lo < hi-1){
        int mid = (lo+hi)/2;
        if(X[mid] <= y){
            lo = mid;
        }
        else{
            hi = mid;
        }
    }
    return X[lo];
}

int main() { 
    cin >> n >> m >> k;
    assert(n < MAXN);
    rep(c1,0,n){
        vi temp;
        score.push_back(0);
        rep(c2,0,m){
            int a;
            cin >> a;
            score[c1] += a;
            temp.push_back(a);
        }
        ind.push_back(c1);
        A.push_back(temp);
        PREV.push_back(0);
    }
    sort(all(ind), comp);

    rep(c1,0,n){
        int i = ind[c1];
        if(c1 > 0){
            PREV[i] = score[ind[c1-1]];
            if(i > ind[c1-1]){
                non_strict[i] = 1;
            }
        }
    }

    rep(c1,0,n){
        int max_hide = score[c1]-PREV[c1];
        vector<vi> hide;

        for(int sc = 0; sc <= max_hide; sc++){
            for(int c = 0; c <= m; c++){
                DP1[1][sc][c] = 0;
            }
        }
        DP1[1][0][0] = 1;
        
        for(int problem = 0; problem < m; problem++){
            int me = problem%2;
            int not_me = (problem+1)%2;
            for(int sc = 0; sc <= max_hide; sc++){
                for(int c = 0; c <= m; c++){
                    DP1[me][sc][c] = 0;
                    if(DP1[not_me][sc][c] == 1){
                        DP1[me][sc][c] = 1;
                    }
                    if(c > 0 && sc >= A[c1][problem] && DP1[not_me][sc-A[c1][problem]][c-1] == 1){
                        DP1[me][sc][c] = 1;
                    }
                }
            }
        }

        for(int c = 0; c <= m; c++){
            int me = (m+1)%2;
            vi row;
            for(int sc = 0; sc <= max_hide; sc++){
                if(DP1[me][sc][c] == 1){
                    row.push_back(sc);
                }
            }
            hide.push_back(row);
        }

        HIDE.push_back(hide);
    }

    for(int c1 = n-1; c1 >= 0; c1--){
        int i = ind[c1];
        int me = c1%2;
        int not_me = (c1+1)%2;
        int max_hide = score[i]-PREV[i];
        for(int before = 0; before <= max_hide; before++){
            DP2[me][before] = inf;
            
            for(int c = 0; c <= m; c++){
                int hide = leq(HIDE[i][c], before-int(non_strict[i]));
                if(hide == -1)continue;
                int r = score[i] - hide + k*c;
                int nex_hide = 0;

                if(c1 < n-1){
                    nex_hide = score[ind[c1+1]]-r;
                }
                if(nex_hide < 0)continue;
                DP2[me][before] = min(DP2[me][before], m-c + DP2[not_me][nex_hide]);
            }
        }
    }

    cout << DP2[0][score[ind[0]]] << "\n";

    return 0;  
}
