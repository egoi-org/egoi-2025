#include <bits/stdc++.h>

using namespace std;

int main(){
    int N, M; cin >> N >> M;
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

    //NOTE: there is a special case: if we start at node 1, Bob shouldn't flip and we need 1 step
    dist[0] = 1;

    for(int i = 0; i < N-1; i++){
        cout << dist[i] << endl;
    }

}