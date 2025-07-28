#include<bits/stdc++.h>

using namespace std;

int n;
int query(vector<int> &v) {
    if (v.empty()) return 0;
    string s(n,'0');
    for (int i : v) {
       s[i] = '1';
    }
    cout << "?" << s << endl; // no space should work
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
   vector<int> ans0(15,-1);
   for (int j=0;j<s;++j){
     v.clear();
     for(int i=0;i<n;++i){
        if((i>>s)&1 && (i>>j)&1) v.push_back(i);
     }
     if(query(v)) ans0[j]=1;
     else ans0[j]=0;
   }
   vector<int> ans1 = ans0;
   ans0[s]=0;
   ans1[s]=1;
   for (int j=s+1;j<15;++j) {
     v.clear();
     for(int i=0;i<n;++i){
        if((i>>s)&1 && (i>>j)&1) v.push_back(i);
     }
     if(query(v)) ans1[j]=1;
     else ans1[j]=0;
     v.clear();
     for(int i=0;i<n;++i){
        if(!((i>>s)&1) && (i>>j)&1) v.push_back(i);
     }
     if(query(v)) ans0[j]=1;
     else ans0[j]=0;
   }

   
   cout << "! " << get_num(ans0) << ' ' << get_num(ans1) << endl;
}
