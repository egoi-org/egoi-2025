#include <bits/stdc++.h>

#define int int64_t
#define rep(i, s, e) for(int i = s; i < e; i++)
#define wpr(x) cout << #x << "=" << x << endl
#define all(x) x.begin(), x.end()

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pi = pair<int, int>;
using vpi = vector<pi>;

template<class A>
ostream &operator<<(ostream &os, const vector<A> &arr) {
    if (arr.empty()) return os << "[]";
    os << "[";
    rep(i, 0, arr.size()) {
        os << arr[i] << ",]"[i == arr.size() - 1];
    }
    return os;
}

void solve() {
    int n, m;
    cin >> m >> n;
    int bad = 0;
    vi cnt(m+1, 0);
    vi arr(n);
    rep(i, 0, n) cin >> arr[i];
    rep(i, 0, n) {
        cnt[arr[i]]++;
        if (cnt[arr[i]] == 2) bad++;
    }
    if (bad == 0) {
        cout << -1 << endl;
        return;
    }
    int r = 0;

    while (bad > 0 && r < n) {
        cnt[arr[r]]--;
        if (cnt[arr[r]] == 1) bad--;
        r++;
    }
    int best_l = 0, best_r = r-1;
    rep(l, 0, n) {
        int v = arr[l];
        assert(l < r);
        cnt[v]++;
        if (cnt[v] == 2) bad++;
        
        while (bad > 0 && r < n) {
            cnt[arr[r]]--;
            if (cnt[arr[r]] == 1) bad--;
            r++;
        }
        if (r == n) break;
        if (best_r - best_l > r - 2 - l) best_l = l+1, best_r = r-1;

    }

    cout << best_l << " " << best_r << endl;

}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
