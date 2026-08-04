/*
Author:Ehundategh
Date:2026/7/30
Name:repair.cpp
You steal,I kill.
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 200010
using namespace std;

int c,T,n,k;
long long a[MAXN],b[MAXN];

void Solve(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
    long long Ans=0,PreSum=0,Max=0;
    for(int i=1;i<=min(n,k);i++){
        PreSum+=a[i];
        Max=max(Max,b[i]);
        Ans=max(Ans,PreSum+1ll*(k-i)*Max);
    }
    printf("%lld\n",Ans);
}

int main(){
    scanf("%d%d",&c,&T);
    while(T-->0) Solve();
    return 0;
}
