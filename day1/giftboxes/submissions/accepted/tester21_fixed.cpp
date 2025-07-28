#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pi pair<int, int>
#define pii pair<int, pi>
#define fi first
#define se second
#ifdef _WIN32
#define getchar_unlocked _getchar_nolock
#endif
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int n, m, a[500005], s[500005], p[500005], f[500005];
int test[500005];

void solve(){
    cin >> n >> m;
    for(int i = 1; i <= m; i++)cin >> a[i], s[a[i]]++;
    int r = 1, cur = 0, cnt = 0;
    for(int i = 0; i < n; i++)cur += (s[i] >= 1), f[i] = (s[i] > 1), cnt += f[i];
    if(!cnt){
        cout << -1 << '\n';
        return;
    }
    while(cnt && r <= m){
        s[a[r]]--;
        if(s[a[r]] == 1)cnt--;
        if(s[a[r]] == 0)cur--;
        r++;
    }
    pii ans = {cur, {0, r - 2}};
    for(int i = 1; i <= m; i++){
        if(p[a[i]] == 1)break;
        p[a[i]]++;
        cur += (p[a[i]] == 1 && s[a[i]] == 0);
        while(r <= m && s[a[i]]){
            s[a[r]]--;
            if(!s[a[r]] && !p[a[r]])cur--;
            r++;
        }
        if(r <= m)ans = max(ans, {cur, {i, r - 2}});
    }
    for (int i = 0; i < m; i++) {
	if (test[a[i+1]] == 1) {
	    if (i > ans.fi) ans = {i, {i, m-1}};
	    break;
	}
	test[a[i+1]] = 1;
    }
    cout << ans.se.fi << ' ' << ans.se.se << '\n';
    
}

main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int tc = 1;
    //cin >> tc;
    for(int tc1=1;tc1<=tc;tc1++){
        // cout << "Case #" << tc1 << ": ";
        solve();
    }
}
