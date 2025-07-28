#include <bits/stdc++.h>

using namespace std;

int N, M;

void fill_dp(int node, vector<vector<int>>& adj, vector<int>& dp, vector<int>& dist){
    if(dp[node] != -1) return;
    dp[node] = 2* N;
    for(int ne: adj[node]){
        fill_dp(ne, adj, dp, dist);
        dp[node] = min(dp[node], dp[ne] + 1);
    }
    dp[node] = max(dp[node], dist[node]);
}

int main(){
    cin >> N >> M;
    vector<vector<int>> adj(N);

    for(int i = 0; i < M; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    vector<int> dist(N, -1);
    dist[0] = 0;

    queue<int> q;
    q.push(0);
    while(!q.empty()){
         int node = q.front();
         q.pop();
         for(int ne: adj[node]){
            if(dist[ne] != -1) continue;
            dist[ne] = dist[node] + 1;
            q.push(ne);
         }
    }

    vector<int> dp(N, -1);
    dp[N-1] = 0;

    for(int i = 0; i < N-1; i++){
        fill_dp(i, adj, dp, dist);
        cout << dp[i] << endl;
    }

    return 0;
}
