// Go directly to N-1, one step before N-1, flip and go to 0
// Should only solve line + immediate flip subtask

#include <bits/stdc++.h>

using namespace std;

int N, M;

void bfs(queue<int> q, vector<vector<int>>& adj, vector<int>& dist, vector<int>& closest){
    while(!q.empty()){
         int node = q.front();
         q.pop();
         for(int ne: adj[node]){
            if(dist[ne] != -1) continue;
            dist[ne] = dist[node] + 1;
            q.push(ne);
            closest[ne] = closest[node];
         }
    }
}

int main(){
  cin >> N >> M;
  vector<vector<int>> adj(N);
  vector<vector<int>> adj_rev(N);

  for(int i = 0; i < M; i++){
      int a, b;
      cin >> a >> b;
      adj[a].push_back(b);
      adj_rev[b].push_back(a);
  }

  if(N == 2){
      cout << 1 << endl;
      return 0;
  }

  // distance from any node to 0 in rev graph 
  vector<int> dist(N, -1);
  dist[0] = 0;
  queue<int> q;
  q.push(0);
  vector<int> ign(N, -1); // irrelevant here
  bfs(q, adj, dist, ign);

  // distance to any neighbor of N-1
  queue<int> q2;
  vector<int> dist2(N, -1);
  vector<int> closest(N, -1);
  
  vector<int> nes;
  for(int i = 0; i < N-1; i++){
    for(int ne : adj[i]){
      if(ne == N-1){
        dist2[i] = 0;
        q2.push(i);
        nes.push_back(i);
        closest[i] = i;
      }
    }
  }

  bfs(q2, adj_rev, dist2, closest);

  for(int i = 0; i < N-1; i++){
    int sol = 2*N;
    sol = min(sol, dist2[i] + dist[closest[i]]);
    cout << max(sol, 1) << endl;
  }

  return 0;
}