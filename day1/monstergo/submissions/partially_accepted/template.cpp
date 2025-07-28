#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<vector<int>> c(N, vector<int>(12));
    iota(c[0].begin(),c[0].end(),0);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 12; ++j)
            cout << c[i][j] << " ";
        cout << endl;
    }

    return 0;
}
