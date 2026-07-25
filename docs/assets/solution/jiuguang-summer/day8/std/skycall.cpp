/*
Author:Ehundategh
Date:2026/7/23
Name:skycall.cpp
You steal,I kill.
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 200010
using namespace std;
int Line[MAXN],n,Ans=0;
int Dp[MAXN];
bool Tag=1;
void Solve(){
    Ans=0;Tag=1;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&Line[i]);
    }
    Dp[0]=0;Dp[1]=0;
    for(int i=2;i<=n;i++){
        if(Line[i-1]-Dp[i-1]-Dp[i-2]>1||Line[i-1]-Dp[i-1]-Dp[i-2]<0) {Tag=0; break;}
        else if(Line[i-1]-Dp[i-1]-Dp[i-2]==1){
            Dp[i]=1;
        }
        else if(Line[i-1]-Dp[i-1]-Dp[i-2]==0){
            Dp[i]=0;
        }
    }
    if(Line[n]!=Dp[n-1]+Dp[n]) Tag=0;
    if(Tag) Ans++;
    Dp[0]=0;Dp[1]=1; Tag=1;
    for(int i=2;i<=n;i++){
        if(Line[i-1]-Dp[i-1]-Dp[i-2]>1||Line[i-1]-Dp[i-1]-Dp[i-2]<0) {Tag=0; break;}
        else if(Line[i-1]-Dp[i-1]-Dp[i-2]==1){
            Dp[i]=1;
        }
        else if(Line[i-1]-Dp[i-1]-Dp[i-2]==0){
            Dp[i]=0;
        }
    }
    if(Line[n]!=Dp[n-1]+Dp[n]) Tag=0;
    if(Tag) Ans++;
    printf("%d\n",Ans);
    return;
}
int main(){
    int c,T;
    freopen("skycall.in","r",stdin);
    freopen("skycall.out","w",stdout);
    scanf("%d%d",&c,&T);
    while(T-->0) Solve();
    return 0;
}
