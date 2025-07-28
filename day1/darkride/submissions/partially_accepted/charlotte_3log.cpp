#include<bits/stdc++.h>

using namespace std;

int n;
int query(vector<int> &v) {
    if (v.empty()) return 0;
    string s(n,'0');
    for (int i : v) {
       s[i] = '1';
       cerr << i << endl;
    }
    cout << "? " << s << endl;
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
   int s = 0;
   do {
    v.clear(); 
    for (int i=0;i<n;++i){
      if((i>>s)&1) v.push_back(i);
    }
    ++s;
   } while(!query(v));
   s--;
   // the rooms agree of the last s-1 bits
   cerr << s << '\n'; 
   
   vector<int> c1;
   vector<int> c0;

   for(int i=0;i<n;++i) {
        if((i>>s)&1) c1.push_back(i);
        else c0.push_back(i);
   }

   int l = 0;
   int h = c1.size();

   while(h != l+1) {
      int m = (l+h)/2;
      v.clear();
      for(int i=l;i<m;++i) {
        v.push_back(c1[i]);
      }
      if (query(v)) h = m;
      else l = m;
   }
   int ans1 = l;
   cerr << ans1 << endl;
   l = 0;
   h = n;

   while(h != l+1) {
      int m = (l+h)/2;
      v.clear();
      for(int i=l;i<m;++i) {
         v.push_back(c0[i]);
      }
      if (query(v)) h = m;
      else l = m;
   }
   int ans0 = l;
   cout << "! " << c0[ans0] << ' ' << c1[ans1] << endl;
}
