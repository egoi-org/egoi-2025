#include <bits/stdc++.h>
using namespace std;

#define f(i, s, k, l) for (int i = s; i < k; i += l)
#define for0(i, k) f(i, 0, k, 1)

using vi = vector<int>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, b;
    cin >> n;

    vi countSum(2 * n, 0);
    for0(i, n) {
        cin >> a >> b;
        if ((a + b) % 2 == 1) countSum[(a + b) % (2 * n)]++;
    }

    int best = *max_element(countSum.begin(), countSum.end());
    cout << n - best << endl;
}
