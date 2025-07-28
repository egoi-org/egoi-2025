#include <bits/stdc++.h>

using namespace std;

int main() {
    int P, N;
    cin >> P >> N;
    vector<int> deg(N,0);
    if (P == 1) {
        for (int i = 0; i < N - 1; ++i) {
            int a, b;
            cin >> a >> b;
            deg[a]++;
            deg[b]++;
        }

        string message = "0";
        if (deg[0] > 1) {
            message = "1";
        }
        
        vector<int> l(N);
        iota(l.begin(),l.end(),0);
        cout << message << endl;
        for (int i = 0; i < N; ++i) {
            if (deg[i] > 1) continue;
            cout << l[i] << endl;
        }
    } else {
        cin.ignore(100, '\n');
        string message;
        getline(cin, message);

        int root = N;
        for (int i = 0; i < N - 1; ++i) {
            int a, b;
            cin >> a >> b;

            if (root == N) {
                if (message == "1") {
                    root = min(a,b);
                } else {
                    root = max(a,b);
                }
            }
            bool guess_a = true;

            if (a == root) {
                guess_a = false;
            }

            if (guess_a) {
                cout << a << endl;
            } else {
                cout << b << endl;
            }
        }
    }
    return 0;
}
