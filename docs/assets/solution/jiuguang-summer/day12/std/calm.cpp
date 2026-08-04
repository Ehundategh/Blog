/*
Author:Ehundategh
Date:2026/7/30
Name:calm.cpp
You steal,I kill.
*/
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 100010
using namespace std;
const int Mod=998244353;
inline int Add(int a,int b){return a+b>=Mod?a+b-Mod:a+b;}
inline int Del(int a,int b){return a-b<0?a-b+Mod:a-b;}
inline int Mul(int a,int b){return 1ll*a*b%Mod;}
int c,T,n,k,cnt,Fact,Dp[MAXN],Ans;
int Cond[MAXN];
inline int Inv(int a){
    int b=Mod-2,Ret=1;
    while(b){
        if(b&1) Ret=Mul(Ret,a);
        a=Mul(a,a);
        b>>=1;
    }
    return Ret;
}

void Solve(){
    scanf("%d%d",&n,&k);
    cnt=Ans=0;
    Fact=1;
    for(int i=1;i<=n;i++) scanf("%d",&Cond[i]),Fact=Mul(Fact,i);
    for(int i=n;i>=1;i--){
        if(Cond[i]){
            for(int j=1;j*j<=i;j++){
                if(i%j==0){
                    Cond[j]^=1;
                    if(j*j!=i) Cond[i/j]^=1;
                }
            }
            cnt++;
            Cond[i]=0;
        }
    }
    Dp[n]=1;
    if(cnt<=k){
        printf("%d\n",Mul(cnt,Fact));
        return;
    }
    for(int i=n-1;i>=1;i--) Dp[i]=Mul(Inv(i),Add(n,Mul(n-i,Dp[i+1])));
    for(int i=cnt;i>=k+1;i--) Ans=Add(Ans,Dp[i]);
    Ans=Mul(Add(Ans,k),Fact);
    printf("%d\n",Ans);
}

int main(){
    scanf("%d%d",&c,&T);
    while(T-->0) Solve();
    return 0;
}
