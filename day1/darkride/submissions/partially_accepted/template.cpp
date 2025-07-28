#include <bits/stdc++.h>

using namespace std;

int query(const string& switches) {
    cout << "? " << switches << endl;
    int num_screams;
    cin >> num_screams;
    return num_screams;
}

int main() {
    int N;
    cin >> N;

    vector<int> ans;
    for (int i = 0; i < N; ++i) {
        int num_screams = query(string(i, '0')+"1"+string(N-i-1, '0'));
	if (num_screams == 1) {
	    ans.push_back(i);
	}
	if (ans.size() == 2) break;
    }

    int A = ans[0];
    int B = ans[1];

    cout << "! " << A << ' ' << B << endl;

    return 0;
}
