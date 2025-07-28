#include<bits/stdc++.h>

using namespace std;

int query(vector<int> &v) {
    if (v.empty()) return 0;
    cout << "? " << v.size();
    for (int i : v) {
        cout << ' ' << i;
    }
    cout << endl;
    int res;
    cin >> res;
    return res%2;
}

int get_num(vector<int>& bits){
   int res = 0;
   for (int i=0;i<15;++i) {
     res += (1<<i)*bits[i];
   }
   return res;
}

int main() {
   ios_base::sync_with_stdio(false);
   cin.tie(0);

   int n;
   cin >> n;

   vector<int> v(n,0);
   iota(v.begin(),v.end(),0);
   
   for(int i=0;i<50000;++i){
     query(v);
   }
   
   cout << "! " << 1 << ' ' << 1 << endl;
}
