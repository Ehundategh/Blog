/*
Author:Ehundategh
Date:2026/7/24
Name:candy.cpp
You steal,I kill.
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 500010
using namespace std;
int T,n,k,Line[MAXN];
long long m,Pre[MAXN],Odd[MAXN],Even[MAXN];
long long Calc(int x){
    int Count=min(k,x/2),Left=x-Count*2;
    long long Ret=Pre[Left];
    if(x&1) Ret+=Odd[x]-Odd[Left];
    else Ret+=Even[x]-Even[Left];
    return Ret;
}
void Solve(){
    scanf("%d%lld%d",&n,&m,&k);
    for(int i=1;i<=n;i++) scanf("%d",&Line[i]);
    sort(Line+1,Line+n+1);
    Pre[0]=Odd[0]=Even[0]=0;
    for(int i=1;i<=n;i++){
        Pre[i]=Pre[i-1]+Line[i];
        Odd[i]=Odd[i-1];Even[i]=Even[i-1];
        if(i&1) Odd[i]+=Line[i];
        else Even[i]+=Line[i];
    }
    int Ans=0;
    for(int i=1;i<=n;i++){
        if(Calc(i)<=m) Ans=i;
    }
    printf("%d\n",Ans);
    return;
}
int main(){
    int c;
    scanf("%d%d",&c,&T);
    while(T-->0) Solve();
    return 0;
}
