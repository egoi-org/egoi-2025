#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, M, A[2000020];
int first_appearance[2000020], last_appearance[2000020], left_bound=0, right_bound=0;
bool checker=false;
int max_first_app=0, dist=INT_MAX, beg=0, en=0;

int main()
{
    cin>>N>>M;
    for(int i=1; i<=M; i++) {cin>>A[i]; A[i]++;}
    for(int i=1; i<=M; i++)     //remembering first and last appearances
    {
        if(first_appearance[A[i]]==0){first_appearance[A[i]]=i;}
        else if(last_appearance[A[i]]==0)
        {
            last_appearance[A[i]]=i;
            max_first_app=max(max_first_app, first_appearance[A[i]]);
        }
        else
        {
            if(!checker)    //remembering first and last of middle apppearances
            {
                checker=true;
                left_bound=last_appearance[A[i]];
                right_bound=last_appearance[A[i]];
                last_appearance[A[i]]=i;
            }
            else
            {
                left_bound=min(left_bound, last_appearance[A[i]]);
                right_bound=max(right_bound, last_appearance[A[i]]);
                last_appearance[A[i]]=i;
            }
        }
    }
    if(max_first_app==0){cout<<-1<<endl; return 0;}     //if there is no second appearances of any element, then there is no reason for pause
    dist=max(max_first_app, right_bound); beg=1; en=max(max_first_app, right_bound);

    for(int i=2, j=en; j<=M; i++)
    {
        if(last_appearance[A[i-1]]==i-1)break;
        //if(i>left_bound and left_bound!=0)break;
        j=max(last_appearance[A[i-1]], j);      //updating second pointer
        if(dist>j-i+1)      //checking if is this solution better then the one we already had
        {
            en=j; beg=i; dist=en-beg+1;
        }
    }
    cout<<beg-1<<" "<<en-1<<endl;
}

