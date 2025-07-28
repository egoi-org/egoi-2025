#include <bits/stdc++.h>

using namespace std;

struct endpt {
    int hair, other;
};

int main() {
    int N;
    cin >> N;
    vector<endpt> endp(2 * N);

    for (int i = 0; i < N; ++i) {
        int a, b;
        cin >> a >> b;
        endp[a] = {i, b};
        endp[b] = {i, a};

    }
    vector<int> countSum(2 * N, 0);
    for (int i = 0; i < 2 * N; i++) {
        if ((i + endp[i].other) % 2 == 1) countSum[(i + endp[i].other) % (2 * N)]++;
    }

    int best = max_element(countSum.begin(), countSum.end()) - countSum.begin();

    int K = N - countSum[best] / 2;

    if (best == 0) best = 1;

    vector<vector<int>> answer;

    for (int i = 0; i < 2 * N; i++) {
        if ((i + endp[i].other) % (2 * N) == best) continue;
        int cur = i;
        int curBest = (best - cur + 2 * N) % (2 * N);
        endp[endp[cur].other].hair = -1;
        while (endp[curBest].hair != -1) {
            answer.push_back({endp[cur].hair, endp[cur].other, curBest});
            // cout << endp[cur].hair << " " << endp[cur].other << " " << curBest << endl;
            endp[cur].other = curBest;
            int next = endp[curBest].other;
            endp[curBest] = {endp[cur].hair, cur};
            cur = next;
            curBest = (best - cur + 2 * N) % (2 * N);
        }
        answer.push_back({endp[cur].hair, endp[cur].other, curBest});

        // cout << endp[cur].hair << " " << endp[cur].other << " " << curBest << endl;
        endp[cur].other = curBest;
        endp[curBest] = {endp[cur].hair, cur};
    }


    cout << K << endl;

    for (int i = 0; i < K; ++i) {
        int p = answer[i][0];
        int s = answer[i][1];
        int e = answer[i][2];
        cout << p << ' ' << s << ' ' << e << endl;
    }

    return 0;
}
