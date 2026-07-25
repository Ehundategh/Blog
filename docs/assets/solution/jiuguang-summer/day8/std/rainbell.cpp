/*
Author:Ehundategh
Date:2026/7/23
Name:rainbell.cpp
You steal,I kill.
*/
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 20010
#define MAXM 100010
using namespace std;
int Fa[MAXN],Must,n,m,Can=0,k;
struct edge{
    int St,Ed;
    int Type;
}Edge[MAXM];
vector <edge> Ans;
bool cmpa(edge a,edge b){return a.Type<b.Type;}
bool cmpb(edge a,edge b){return a.Type>b.Type;}
int Find(int x){return Fa[x]==x?Fa[x]:Fa[x]=Find(Fa[x]);}
void Merge(int x,int y){Fa[Find(x)]=Find(y);}
bool Get_Tog(){
    int Tag;
    for(int i=1;i<=n;i++) Fa[i]=i;
    for(int i=1;i<=m;i++){
        if(Find(Edge[i].St)==Find(Edge[i].Ed)) continue;
        Merge(Edge[i].St,Edge[i].Ed);
    }
    Tag=Find(1);
    for(int i=1;i<=n;i++){if(Tag!=Find(i)) return false; }
    return true;
}
void Kruskal1(){
    sort(Edge+1,Edge+m+1,cmpb);
    for(int i=1;i<=n;i++) Fa[i]=i;
    int Count=0,i;
    for(i=1;i<=m;i++){
        if(Edge[i].Type==0) break;
        if(Find(Edge[i].St)==Find(Edge[i].Ed)) continue;
        Count++;
        Merge(Edge[i].St,Edge[i].Ed);
    }
    for(i;i<=m;i++){
        if(Find(Edge[i].St)==Find(Edge[i].Ed)) continue;
        Merge(Edge[i].St,Edge[i].Ed);
        Ans.push_back(Edge[i]);
    }
    Must=n-1-Count;
}
bool Kruskal2(){
    sort(Edge+1,Edge+m+1,cmpa);
    for(int i=1;i<=n;i++) Fa[i]=i;
    k-=Must;
    for(int i=0;i<(int)Ans.size();i++){
        Merge(Ans[i].Ed,Ans[i].St);
    }
    for(int i=1;i<=m;i++){
        if(Edge[i].Type==0&&(!k)) continue;
        if(Edge[i].Type==1&&(k)) return false;
        if(Find(Edge[i].St)==Find(Edge[i].Ed)) continue;
        Merge(Edge[i].St,Edge[i].Ed);
        Ans.push_back(Edge[i]);
        if(Edge[i].Type==0) k--;
    }
    return (int)Ans.size()==n-1;
}
void Solve(){
    int In1,In2,In3;
    Ans.clear();Can=0;Must=0;
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&In1,&In2,&In3);
        Edge[i]={In1,In2,In3};
        if(In3==0) Can++;
    }
    if(!Get_Tog()){
        puts("no solution");
        return;
    }
    Kruskal1();
    if(Must>k) {puts("no solution");return;}
    if(!Kruskal2()){puts("no solution");return;}
    for(int i=0;i<(int)Ans.size();i++){
        printf("%d %d %d\n",Ans[i].St,Ans[i].Ed,Ans[i].Type);
    }
    return;
}
int main(){
    int c,T;
    freopen("rainbell.in","r",stdin);
    freopen("rainbell.out","w",stdout);
    scanf("%d%d",&c,&T);
    while(T-->0) Solve();
    return 0;
}
