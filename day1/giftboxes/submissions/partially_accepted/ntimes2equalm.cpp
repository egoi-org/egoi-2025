#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int,int>> nums(n, {-1, -1});
    int a[m];
    int right;
    for (int i = 0; i < m; i++) {
        cin >> a[i];
        if (nums[a[i]].first == -1) {
            nums[a[i]].first = i;
            right = i;
        } else {
            nums[a[i]].second = i;
        }
    }

    int best = right+1, l = 0, r = right;

    for (int left = 1; left < m; left++) {
        if (left-1 == nums[a[left-1]].second) break;
        right = max(right, nums[a[left-1]].second);
        if (best > right-left+1) {
            best = right-left+1;
            l = left;
            r = right;
        }
    }
    
    cout << l << " " << r << "\n";
    return 0;
}
