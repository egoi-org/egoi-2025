#include <bits/stdc++.h>
using namespace std;

// Special Case: for N=2, the answer is 1

int main(){
    int N; cin >> N;
    if(N == 2){
        cout << 1 << endl;
        return 0;
    }
    
    for(int i = 0; i < N-1; i++){
        cout << (N- i - 2) + (N-2) << endl;
    }

    return 0;
}
