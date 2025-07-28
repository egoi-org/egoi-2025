#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    if (n==m) {cout << -1; return 0;}

    int a[m], nums[n];
    for (int i = 0; i < n; i++) nums[i] = 0;
    for (int i = 0; i < m; i++) {
        cin >> a[i];
        nums[a[i]]++;
    }

    int best = 0, l = -1, r = -1;
    for (int i = 0; i < m; i++) {
        int newNums[n];
        copy(nums, nums+n, newNums);
        int invalid = 0;
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if (newNums[j] == 1) cnt++;
            if (newNums[j] > 1) invalid++;
        }

        for (int j = i; j < m; j++) {
            newNums[a[j]]--;
            if (newNums[a[j]] == 1) {cnt++; invalid--;}
            if (newNums[a[j]] == 0) cnt--;
            if (invalid == 0 && cnt > best) {l = i; r = j; best=cnt;}
        }
    }

    cout << l << " " << r << "\n";
    return 0;
}
