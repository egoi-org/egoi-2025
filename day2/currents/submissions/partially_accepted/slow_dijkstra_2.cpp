// Should solve small subtasks and line subtask

#include <bits/stdc++.h>
using namespace std;
#define pi pair <int, int>
#define fi first
#define se second
vector <int> adj[200005], rev[200005];
int n, m, dist[200005], ans[200005];

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    while(m--){
        int a, b; cin >> a >> b;
        adj[a+1].push_back(b+1);
        rev[b+1].push_back(a+1);
    }
    queue <int> q;
    for(int i = 2; i <= n; i++)dist[i] = 1e9;
    q.push(1);
    while(!q.empty()){
        int x = q.front(); q.pop();
        for(auto i : adj[x]){
            if(dist[i] > dist[x] + 1)dist[i] = dist[x] + 1, q.push(i);
        }
    }
    for(int i = 1; i < n; i++)ans[i] = 2e9;
    vector<pi> next = {{0, n}};
    while(!next.empty()){
        int x = 2e9;
        int y = -1;
        int j = -1;
        for(int i = 0; i < next.size(); i++){
          auto [x2, y2] = next[i];
          if (x2 < x){
            y = y2;
            x = x2;
            j = i;
          }
        }
        next.erase(next.begin() + j);
        if(ans[y] > x)continue;
        for(auto i : rev[y]){
            if(max(dist[i], x + 1) < ans[i])ans[i] = max(dist[i], x + 1), next.push_back({ans[i], i});
        }
    }
    for(int i = 1; i < n; i++)cout << ans[i] << ' ';
    cout << endl;
}
