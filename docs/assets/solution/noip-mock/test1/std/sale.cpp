/*
Author:Ehundategh
Date:2026/7/24
Name:sale.cpp
You steal,I kill.
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 500010
using namespace std;
int T,n,m,Value[MAXN],Type[MAXN],One[MAXN],Two[MAXN];
long long PreOne[MAXN],PreTwo[MAXN];
bool cmp(int a,int b){return a>b;}
void Solve(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&Value[i]);
    for(int i=1;i<=n;i++) scanf("%d",&Type[i]);
    int CntOne=0,CntTwo=0;
    for(int i=1;i<=n;i++){
        if(Type[i]==1) One[++CntOne]=Value[i];
        else Two[++CntTwo]=Value[i];
    }
    sort(One+1,One+CntOne+1,cmp);
    sort(Two+1,Two+CntTwo+1,cmp);
    PreOne[0]=PreTwo[0]=0;
    for(int i=1;i<=CntOne;i++) PreOne[i]=PreOne[i-1]+One[i];
    for(int i=1;i<=CntTwo;i++) PreTwo[i]=PreTwo[i-1]+Two[i];
    long long Ans=0;
    for(int i=0;i<=CntTwo&&i*2<=m;i++){
        int Count=min(CntOne,m-i*2);
        Ans=max(Ans,PreTwo[i]+PreOne[Count]);
    }
    printf("%lld\n",Ans);
    return;
}
int main(){
    int c;
    scanf("%d%d",&c,&T);
    while(T-->0) Solve();
    return 0;
}
