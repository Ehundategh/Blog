/*
Author:Ehundategh
Date:2026/7/24
Name:tree.cpp
You steal,I kill.
*/
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 8010
#define MAXM 810
using namespace std;
const long long INF=4e18;
int T,n,m,Fa[MAXN],Height[MAXN];
long long a[MAXN],b[MAXN],Dp[MAXN][MAXM],Best[MAXN];
vector <int> Son[MAXN];
void Solve(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) Son[i].clear();
    for(int i=2;i<=n;i++){
        scanf("%d",&Fa[i]);
        Son[Fa[i]].push_back(i);
    }
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
    memset(Dp,0x80,sizeof(Dp));
    for(int Now=n;Now>=1;Now--){
        if(Son[Now].empty()){
            Height[Now]=1;
            Dp[Now][1]=0;
            continue;
        }
        Height[Now]=1;
        long long Sum=0;
        for(int To:Son[Now]){
            Height[Now]=max(Height[Now],Height[To]+1);
            Best[To]=-INF;
            for(int j=1;j<=Height[To];j++){
                Best[To]=max(Best[To],Dp[To][j]+a[To]*b[j]);
            }
            Sum+=Best[To];
        }
        for(int To:Son[Now]){
            for(int j=1;j<=Height[To];j++){
                Dp[Now][j+1]=max(Dp[Now][j+1],Dp[To][j]+Sum-Best[To]);
            }
        }
    }
    long long Ans=-INF;
    for(int i=1;i<=Height[1];i++) Ans=max(Ans,Dp[1][i]+a[1]*b[i]);
    printf("%lld\n",Ans);
    return;
}
int main(){
    int c;
    scanf("%d%d",&c,&T);
    while(T-->0) Solve();
    return 0;
}
