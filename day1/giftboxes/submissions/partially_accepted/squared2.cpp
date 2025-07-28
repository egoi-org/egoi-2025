#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    if (n==m) {cout << -1 << "\n"; return 0;}
    int a[m];
    int l=1e8, r=-1, rightMostFirst=-1;
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        int first = m, last = -1;
        for (int j = 0; j < m; j++) {
            if (a[j] == i) {
                first = min(first, j);
                if (first != last && last != -1) {
                    l = min(l, last);
                    r = max(r, last);
                }
                last = max(last, j);
            }
        }
        if (first != last) {
            rightMostFirst = max(rightMostFirst, first);
        }
    }

    int best, lRes = 0, rRes = max(rightMostFirst, r), right = rRes;
    best = rRes+1;
    for (int left = 1; left < m; left++) {
        int ind = -1;
        bool valid = false;
        for (int i = m-1; i >= 0; i--) {
             if (ind != -1 && a[i] == a[left-1]) {valid = true;}
             if (ind == -1 && a[i] == a[left-1]) {ind = i;}
        }
        if (!valid) ind = -1;
        if (left-1 == ind) break;
        if (left > l) break;
        right = max(right, ind);
        if (best > right-left+1) {
            best = right-left+1;
            lRes = left;
            rRes = right;
        }
    }
    cout << lRes << " " << rRes << "\n";
    return 0;
}

