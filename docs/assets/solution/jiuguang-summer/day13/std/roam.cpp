/*
Author:Ehundategh
Date:2026/8/13
Name:roam.cpp
You steal,I kill.
*/
#include <cstdio>
#include <algorithm>
#define MAXN 200010
using namespace std;

int c,T,n;
struct land{
    long long Need,Change;
}Line[MAXN];

bool cmp(land A,land B){
    if((A.Change>=0)!=(B.Change>=0)) return A.Change>=0;
    if(A.Change>=0) return A.Need<B.Need;
    return A.Need+A.Change>B.Need+B.Change;
}

void Solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld%lld",&Line[i].Need,&Line[i].Change);
    sort(Line+1,Line+n+1,cmp);
    long long Sum=0,Ans=0;
    for(int i=1;i<=n;i++){
        Ans=max(Ans,Line[i].Need-Sum);
        Sum+=Line[i].Change;
    }
    printf("%lld\n",Ans);
    return ;
}

int main(){
    scanf("%d%d",&c,&T);
    while(T-->0) Solve();
    return 0;
}
