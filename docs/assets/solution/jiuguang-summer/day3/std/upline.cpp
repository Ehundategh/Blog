/*
Author:Ehundategh
Date:2026/7/14
Name:upline.cpp
You steal,I kill.
*/
#include <cstdio>
#include <cstring>
#define MAXNUM 100010
#define MAXN 200010
using namespace std;
int Line[MAXN],SmallFront[MAXN],SmallBack[MAXN],n;
long long Ans=0;
struct SZSZ{
    int C[MAXNUM];
    int lowbit(int a){
        return a&(-a);
    }
    void Update(int x,int y){
        for(;x<MAXNUM;x+=lowbit(x)){
            C[x]+=y;
        }
        return;
    }
    void Init(){
        memset(C,0,sizeof(C));
    }
    int Query(int x){
        int ans=0;
        for(;x;x-=lowbit(x)){
            ans+=C[x];
        }
        return ans;
    }
}S1,S2;
int main(){
    freopen("upline.in","r",stdin);
    freopen("upline.out","w",stdout);
    memset(SmallFront,0,sizeof(SmallFront));
    memset(SmallBack,0,sizeof(SmallBack));
    scanf("%d",&n);
    S1.Init();
    S2.Init();
    for(int i=1;i<=n;i++){
        scanf("%d",&Line[i]);
        SmallFront[i]=S1.Query(Line[i]-1);
        S1.Update(Line[i],1);
    }
    for(int i=n;i>=1;i--){
        SmallBack[i]=S2.Query(MAXNUM)-S2.Query(Line[i]);
        S2.Update(Line[i],1);
    }
    for(int i=1;i<=n;i++){
        Ans+=1ll*SmallFront[i]*SmallBack[i];
    }
    printf("%lld",Ans);
    return 0;
}
