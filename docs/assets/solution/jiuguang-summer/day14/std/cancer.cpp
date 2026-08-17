/*
Author:Ehundategh
Date:2026/8/17
Name:cancer.cpp
You steal,I kill.
*/
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 2010
using namespace std;
const int Mod=998244353;
inline int Add(int a,int b){return a+b>=Mod?a+b-Mod:a+b;}
inline int Del(int a,int b){return a-b<0?a-b+Mod:a-b;}
int c,T,n,Fa[MAXN],Depth[MAXN],l[MAXN],r[MAXN],h[MAXN];
int Dp[MAXN],Pre[MAXN],Path[MAXN],Ans;
vector <int> Son[MAXN];

void DFS(int Now,int Limit){
    Path[Depth[Now]]=Now;
    Limit=min(Limit,Depth[Now]-h[Now]-1);
    int Left=Depth[Now]-r[Now];
    int Right=min(Depth[Now]-l[Now],Limit);
    if(Left<=Right){
        int Temp=Pre[Path[Right]];
        if(Left) Temp=Del(Temp,Pre[Path[Left-1]]);
        Ans=Add(Ans,Temp);
    }
    for(int i=0;i<(int)Son[Now].size();i++) DFS(Son[Now][i],Limit);
}

void Solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) Son[i].clear();
    Depth[1]=0;Dp[1]=Pre[1]=1;
    for(int i=2;i<=n;i++){
        scanf("%d%d%d%d",&Fa[i],&l[i],&r[i],&h[i]);
        Depth[i]=Depth[Fa[i]]+1;
        Son[Fa[i]].push_back(i);
    }
    for(int i=2;i<=n;i++){
        int Now=i;
        while(Now){Path[Depth[Now]]=Now;Now=Fa[Now];}
        Ans=0;DFS(i,n);
        Dp[i]=Ans;
        Pre[i]=Add(Pre[Fa[i]],Dp[i]);
    }
    for(int i=2;i<=n;i++) printf("%d%c",Dp[i]," \n"[i==n]);
}

int main(){
    scanf("%d%d",&c,&T);
    while(T-->0) Solve();
    return 0;
}
