// a heuristic approach to the problem. We first sort the contestants, and then, starting from the worst contestant, we try to hide their scores starting from the largest whenever this is possible. In the end, we also hide the smallest scores of the best contestant. This should only work for the subtask n <= 2, m <= 2 


#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int> > a(n, vector<int>(m));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> a[i][j];
        }
        sort(a[i].begin(), a[i].end());
    }

    vector<pair<int, int> > sums(n);
    for (int i = 0; i < n; i++){
        sums[i].second = -i;
        sums[i].first = accumulate(a[i].begin(), a[i].end(), 0);
    }
    sort(sums.begin(), sums.end());

    int hidden = 0;
    pair<int,int> hi_pre;

    for (int i = 0; i < n-1; i++){
        auto [s, j] = sums[i];
        j = -j;
        int lo = s, hi = s;

        for(int l = m-1; l >= 0; l--){
            if ( make_pair(hi + (k - a[j][l]), -j) < sums[i+1] && (i == 0 || make_pair(lo - a[j][l], -j) > hi_pre)){
                hidden++;
                hi += (k - a[j][l]);
                lo -= a[j][l];
            }
        }
        hi_pre = {hi, j};
    }

    auto [s, j] = sums[n-1];
    j = -j;
    for(int l = 0; l < m; l++){
        if (make_pair(s - a[j][l], -j) > hi_pre){
            hidden++;
            s -= a[j][l];
        }
        else break;
    }

    cout << (n * m - hidden) << endl;

    return 0;
}