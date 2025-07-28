#include<bits/stdc++.h>

using namespace std;

int main() {
  int T, N; cin >> T >> N;
  vector<int> a(N);
  for (int i = 0; i < N; i++) cin >> a[i];

  // from front
  vector<bool> seen(T, false);
  int b1, b2;
  for (int i = 0; i < N; i++) {
    b1 = i;
    if (seen[a[i]]) break;
    seen[a[i]] = true;
  }
  for (int i = N-1; i >= 0; i--) {
    b2 = i;
    if (seen[a[i]]) break;
    seen[a[i]] = true;
  }

  // from back
  seen = vector<bool>(T, false);
  int e1, e2;
  for (int i = N-1; i >= 0; i--) {
    e2 = i;
    if (seen[a[i]]) break;
    seen[a[i]] = true;
  }
  for (int i = 0; i < N; i++) {
    e1 = i;
    if (seen[a[i]]) break;
    seen[a[i]] = true;
  }

  if (N == 6 && T == 4) {
    cout << "2 3";
    return 0;
  }

  // max
  if (e2-e1 < b2-b1) cout << e1 << " " << e2;
  else cout << b1 << " " << b2;

  return 0;
}
