#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int nums[n] = {0};

    for (int i = 0; i < m; i++) {
        int a;
        cin >> a;
        nums[a]++;
        if (nums[a] > 1) {
            cout << i << " " << i << "\n";
            return 0;
        }
    }
    return 0;
}
