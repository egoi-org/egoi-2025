#include <bits/stdc++.h>
using namespace std;

// go through the people from left to right and randomly hide scores in 
// a valid way. Repeat a lot of times, first with hiding at most one score
// every time and then more.

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
vi score;

bool comp(int i, int j){
    if(score[i] == score[j])return i > j;
    return score[i] < score[j];
}

vi m_ind;

vi score_subset(int x){
    if(x == 0)return {};
    if(x == 1)return {rand()%m};
    random_shuffle(all(m_ind));
    vi res;
    rep(c1,0,x){
        res.push_back(m_ind[c1]);
    }
    return res;
}

int lim = 100;

int solve(int ss){
    ss = min(ss, m);
    int res = n*m;
    pii prev = {-inf,-inf};
    rep(c1,0,n){
        int i = ind[c1];
        pii zero = {score[i], n-i};
        pii nex = {inf,inf};
        if(c1 < n-1)nex = {score[ind[c1+1]], n-ind[c1+1]};

        if(zero < prev)return n*m;

        int tries = 0;
        while(tries < lim){
            vi subset = score_subset(rand()%(ss+1));
            int lo = score[i];
            int hi = score[i];
            trav(j, subset){
                lo -= A[i][j];
                hi -= A[i][j];
                hi += k;
            }

            pii p1 = {lo, n-i};
            pii p2 = {hi, n-i};
            if(prev < p1 && p2 < nex){
                prev = p2;
                res -= sz(subset);
                break;
            }
            tries++;
        }

        if(tries == lim){
            prev = zero;
        }
    }
    return res;
}

int main() { 
    cin >> n >> m >> k;
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
        sort(all(temp));
        A.push_back(temp);
    }
    sort(all(ind), comp);

    rep(c1,0,m){
        m_ind.push_back(c1);
    }

    int ans = n*m;
    int lim = 100000 / n;
    rep(_,0,lim){
        ans = min(ans, solve(1));
    }
    rep(_,0,lim){
        ans = min(ans, solve(2));
    }
    rep(_,0,lim){
        ans = min(ans, solve(m));
    }

    cout << ans << "\n";

    return 0;  
}
