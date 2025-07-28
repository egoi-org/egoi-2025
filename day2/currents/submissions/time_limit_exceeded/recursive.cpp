#include <bits/stdc++.h>

using namespace std;

int N, M;

int solve(int node, vector<vector<int>>& adj, vector<int>& dist){
    if(node == N-1) return 0;
    int sol = 2 * N;
    for(int ne: adj[node]){
        int sol_ne = solve(ne, adj, dist);
        sol = min(sol, sol_ne + 1);
    }
    sol = max(sol, dist[node]);
    return sol;
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

    for(int i = 0; i < N-1; i++){
        cout << solve(i, adj, dist) << endl;
    }

    return 0;
}
