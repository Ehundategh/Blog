/*
Author:Ehundategh
Date:2026/7/30
Name:circle.cpp
You steal,I kill.
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 1000010
using namespace std;

int lowbit(int x){return x&-x;}

int c,T,n,x,y,z,Pos[MAXN];
long long C[MAXN<<1],a[MAXN],b[MAXN],Dp[MAXN][2];
void Update(int Now,int Val){for(;Now<=2*n;Now+=lowbit(Now)) C[Now]+=1ll*Val;}
long long Query(int Now){long long Ret=0;for(;Now;Now-=lowbit(Now)) Ret+=C[Now];return Ret;}

long long GetD(int l,int r){
    if(l>r) r+=n;
    if(r-l>=n) r-=n;
    return Query(r)-Query(l-1);
}

void Solve(){
    scanf("%d%d%d%d",&n,&x,&y,&z);
    for(int i=1;i<=2*n;i++) C[i]=lowbit(i);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]),Pos[a[i]]=i;
    for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
    Pos[0]=1;
    Dp[0][0]=0;
    Dp[0][1]=z;
    for(int i=1;i<=n;i++){
        int dl=GetD(Pos[b[i-1]],Pos[b[i]])-GetD(Pos[b[i]],Pos[b[i]]);
        int dr=GetD(Pos[b[i]]+1,Pos[b[i-1]]+n);
        Dp[i][0]=min(min(Dp[i-1][0]+1ll*dl*x,Dp[i-1][0]+1ll*dr*y),min(Dp[i-1][1]+1ll*dl*y+z,Dp[i-1][1]+1ll*dr*x+z));
        Dp[i][1]=min(min(Dp[i-1][1]+1ll*dl*y,Dp[i-1][1]+1ll*dr*x),min(Dp[i-1][0]+1ll*dl*x+z,Dp[i-1][0]+1ll*dr*y+z));
        Update(Pos[b[i]],-1);
        Update(Pos[b[i]]+n,-1);
    }
    printf("%lld\n",min(Dp[n][0],Dp[n][1]));
}

int main(){
    scanf("%d%d",&c,&T);
    while(T-->0) Solve();
    return 0;
}
