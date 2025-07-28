#include <cassert>
#include <iostream>
#include <random>

using namespace std;

int num_monsters = 46;
int list_size = 12;

int main() {
    int n;
    cin >> n;
    vector<uint64_t> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = ((uint64_t(1) << 13) - 1 - (uint64_t(1) << (i % 13))) << ((i / 13) * 13);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < num_monsters; ++j) {
            if (a[i] & (uint64_t(1) << j)) {
                cout << j << " ";
            }
        }
        cout << endl;
    }
    return 0;
}
