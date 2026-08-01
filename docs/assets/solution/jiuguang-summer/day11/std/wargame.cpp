/*
Author:Ehundategh
Date:2026/7/30
Name:wargame.cpp
You steal,I kill.
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 50010
using namespace std;
int T,n,m,Head[MAXN],Total=0,Fa[MAXN][20],Army[MAXN];
int RootVal[MAXN],MinID[MAXN],NeedVal[MAXN],cn=0,cf=0,cr=0;
long long Value[MAXN][20],SumEdge=0,RestList[MAXN];
bool Mark[MAXN],Need[MAXN],Used[MAXN];
struct edge{
    int St,Ed,Next;
    int Value;
}Edge[MAXN<<1];
struct army{
    long long Rest;
    int Root;
}Free[MAXN];
void Edge_Add(int St,int Ed,int Value){
    Edge[++Total]={St,Ed,Head[St],Value};
    Head[St]=Total;
}
void DFS(int Now,int From){
    for(int i=Head[Now];i;i=Edge[i].Next){
        int To=Edge[i].Ed;
        if(To==From) continue;
        Fa[To][0]=Now;
        Value[To][0]=Edge[i].Value;
        if(Now==1) RootVal[To]=Edge[i].Value;
        DFS(To,Now);
    }
}
bool Cover(int Now,int From){
    if(Mark[Now]) return true;
    bool HasSon=false;
    for(int i=Head[Now];i;i=Edge[i].Next){
        int To=Edge[i].Ed;
        if(To==From) continue;
        HasSon=true;
        if(!Cover(To,Now)) return false;
    }
    return HasSon;
}
bool cmp(army a,army b){return a.Rest<b.Rest;}
bool Judge(long long Limit){
    memset(Mark,0,sizeof(bool)*(n+2));
    memset(Need,0,sizeof(bool)*(n+2));
    memset(Used,0,sizeof(bool)*(m+2));
    memset(MinID,0,sizeof(int)*(n+2));
    cf=cn=cr=0;
    for(int i=1;i<=m;i++){
        int Now=Army[i];
        long long UsedValue=0;
        for(int j=17;j>=0;j--){
            if(Fa[Now][j]>1&&UsedValue+Value[Now][j]<=Limit){
                UsedValue+=Value[Now][j];
                Now=Fa[Now][j];
            }
        }
        if(Fa[Now][0]==1&&UsedValue+Value[Now][0]<=Limit){
            Free[++cf]={Limit-UsedValue-Value[Now][0],Now};
        }
        else Mark[Now]=true;
    }
    for(int i=Head[1];i;i=Edge[i].Next){
        int To=Edge[i].Ed;
        if(!Cover(To,1)) Need[To]=true;
    }
    sort(Free+1,Free+cf+1,cmp);
    for(int i=1;i<=cf;i++){
        int Root=Free[i].Root;
        if(!MinID[Root]) MinID[Root]=i;
    }
    for(int i=Head[1];i;i=Edge[i].Next){
        int To=Edge[i].Ed;
        if(!Need[To]) continue;
        int Pos=MinID[To];
        if(Pos&&Free[Pos].Rest<RootVal[To]){
            Used[Pos]=true;
            Need[To]=false;
        }
    }
    for(int i=Head[1];i;i=Edge[i].Next){
        int To=Edge[i].Ed;
        if(Need[To]) NeedVal[++cn]=RootVal[To];
    }
    for(int i=1;i<=cf;i++){
        if(!Used[i]) RestList[++cr]=Free[i].Rest;
    }
    sort(NeedVal+1,NeedVal+cn+1);
    sort(RestList+1,RestList+cr+1);
    int Pos=1;
    for(int i=1;i<=cr&&Pos<=cn;i++){
        if(RestList[i]>=NeedVal[Pos]) Pos++;
    }
    return Pos>cn;
}
void Solve(){
    scanf("%d%d",&n,&m);
    memset(Head,0,sizeof(int)*(n+2));
    memset(Fa,0,sizeof(Fa[0])*(n+2));
    memset(Value,0,sizeof(Value[0])*(n+2));
    memset(RootVal,0,sizeof(int)*(n+2));
    Total=0;SumEdge=0;
    int In1,In2,In3;
    for(int i=1;i<n;i++){
        scanf("%d%d%d",&In1,&In2,&In3);
        Edge_Add(In1,In2,In3);
        Edge_Add(In2,In1,In3);
        SumEdge+=In3;
    }
    for(int i=1;i<=m;i++) scanf("%d",&Army[i]);
    DFS(1,0);
    for(int j=1;j<=17;j++){
        for(int i=1;i<=n;i++){
            Fa[i][j]=Fa[Fa[i][j-1]][j-1];
            Value[i][j]=Value[i][j-1]+Value[Fa[i][j-1]][j-1];
        }
    }
    if(!Judge(SumEdge)){puts("Pity!");return;}
    long long Left=0,Right=SumEdge;
    while(Left<Right){
        long long Mid=(Left+Right)>>1;
        if(Judge(Mid)) Right=Mid;
        else Left=Mid+1;
    }
    printf("%lld\n",Left);
}
int main(){
    int c;
    scanf("%d%d",&c,&T);
    while(T-->0) Solve();
    return 0;
}
