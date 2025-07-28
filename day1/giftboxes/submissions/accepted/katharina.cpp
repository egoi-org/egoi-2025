#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    if (n==m) {cout << -1 << "\n"; return 0;}
    vector<pair<int, int>> nums(n, {-1, -1});
    int a[m];
    int l=1e8, r=-1, rightMostFirst=-1;
    for (int i = 0; i < m; i++) {
        cin >> a[i];
        if (nums[a[i]].first == -1) {
            nums[a[i]].first = i;
        } else {
            rightMostFirst = max(rightMostFirst, nums[a[i]].first);
            if (nums[a[i]].second != -1) {
                l = min(l, nums[a[i]].second);
                r = max(r, nums[a[i]].second);
            }
            nums[a[i]].second = i;
        }
    }

    int best, lRes = 0, rRes = max(rightMostFirst, r), right = rRes;
    best = rRes+1;
    for (int left = 1; left < m; left++) {
        if (left-1 == nums[a[left-1]].second) break;
        if (left > l) break;
        right = max(right, nums[a[left-1]].second);
        if (best > right-left+1) {
            best = right-left+1;
            lRes = left;
            rRes = right;
        }
    }
    cout << lRes << " " << rRes << "\n";
    return 0;
}
