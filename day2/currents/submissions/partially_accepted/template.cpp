#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
    }

    vector<int> ans(N - 1);

    for (int i = 0; i < N - 1; ++i) {
	ans[i] = (N-i-2) + (N-2);
	if (N == 2) ans[i] = 1;
        cout << ans[i] << ' ';
    }
    cout << endl;

    return 0;
}
