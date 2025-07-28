#include<bits/stdc++.h>

using namespace std;

int n;
int query(vector<int> &v) {
    if (v.empty()) return 0;
    cout << "? ";
    string s(n,'0');
    for (int i : v) {
       s[i] = '1';
    }
    cout << " " << s << endl;
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

   cin >> n;

   vector<int> v;
   v.push_back(1);
   
   for(int i=0;i<31;++i){
     query(v);
   }
   
   cout << "! " << 1 << ' ' << 1 << endl;
}
