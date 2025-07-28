#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    if (n==m) {cout << -1; return 0;}

    int a[m];
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }

    int best = m, bestR = -1, bestL = -1;
    for (int l = 0; l < m; l++) {
        for (int r = l; r < m; r++) {
            int pplPerTeam[n] = {0};
            bool valid = true;
            for (int p = 0; p < m; p++) {
                if (p < l || p > r) {
                    pplPerTeam[a[p]]++;
                    if (pplPerTeam[a[p]] > 1) valid = false;
                }
            }
            if (valid && r-l+1 < best) {
                best = r-l+1;
                bestL = l;
                bestR = r;
            }
        }
    }

    cout << bestL << " " << bestR << "\n";
    return 0;
}
