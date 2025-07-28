#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, M, K;
    cin >> N >> M >> K;

    vector<vector<int>> a(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> a[i][j];
        }
    }

    vector<vector<int>> scores(0);
    for (int i = 0; i < N; i++) {
	int ones = 0;
        for (int j = 0; j < M; j++) {
	    if (a[i][j] == 1) ones++;
	}
	scores.push_back({ones, -i});
    }
    sort(scores.begin(), scores.end());
    int gaps = 0;
    for (int i = 0; i < N-1; i++) {
        if (scores[i+1][1] < scores[i][1]) gaps++;
    }

    int ans = N*M-M+gaps;

    cout << ans << endl;

    return 0;
}
