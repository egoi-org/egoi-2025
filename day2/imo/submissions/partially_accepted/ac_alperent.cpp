#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 5;

int n, m, k;

vector<vector<int>> scores;
vector<int> prv, cur;
vector<bool> canbesame;

void sort_scores(){
    vector<pair<int, int>> vec;

    for(int i = 0; i < n; i++) vec.push_back({-accumulate(scores[i].begin(), scores[i].end(), 0), i});

    sort(vec.begin(), vec.end());

    vector<vector<int>> tmp = scores;

    canbesame.assign(n, false);

    for(int i = 0; i < n; i++){
        scores[i] = tmp[vec[i].second];

        if(i != 0) canbesame[i] = vec[i].second > vec[i - 1].second;
    }
}

vector<vector<bool>> get_scores(int x){
    vector<vector<bool>> knap(m * k + 1, vector<bool>(m + 1, false));

    knap[0][0] = true;

    for(int i = 0; i < m; i++){
        for(int sum = m * k; sum >= scores[x][i]; sum--){
            for(int cnt = m; cnt >= 1; cnt--){
                knap[sum][cnt] = knap[sum][cnt] | knap[sum - scores[x][i]][cnt - 1];
            }
        }
    }

    return knap;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;

    scores.assign(n, vector(m, 0));

    for(auto &x : scores){
        for(auto &y : x){
            cin >> y;
        }
    }

    sort_scores();

    prv = vector(m * k + 2, 0);

    for(int i = 0; i < n; i++){
        vector<vector<bool>> pos_scores = get_scores(i);

        cur = vector(m * k + 2, INF);

        for(int score = 0; score <= m * k; score++){
            for(int cnt = 0; cnt <= m; cnt++){
                if(pos_scores[score][cnt]){
                    int bound = score + (m - cnt) * k;

                    if(!canbesame[i]) bound++;

                    cur[score] = min(cur[score], prv[bound] + cnt);
                }
            }
        }

        for(int j = m * k - 1; j >= 0; j--) cur[j] = min(cur[j], cur[j + 1]);

        prv = cur;
    }

    cout << prv[0];
}
