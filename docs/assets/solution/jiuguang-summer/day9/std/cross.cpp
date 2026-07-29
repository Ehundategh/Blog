/*
- @Author: Ehundategh
- @Date: 2023-11-07 15:16:31
- @FilePath: \Code\11.6\仓鼠找Sugar.cpp
- @Description: You Steal,I Kill
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 100010
using namespace std;
int Fa[MAXN][21],Total,Head[MAXN],Depth[MAXN],In1,In2,In3,In4;
struct edge{
;;;;int St,Ed,Next;
}Edge[MAXN<<1];
void Edge_Add(int St,int Ed){
;;;;Edge[++Total]={St,Ed,Head[St]};
;;;;Head[St]=Total;
}
void DFS(int Now,int From){
;;;;Fa[Now][0]=From;
;;;;Depth[Now]=Depth[From]+1;
;;;;for(int i=Head[Now];i;i=Edge[i].Next){
;;;;;;;;int To=Edge[i].Ed;
;;;;;;;;if(To==From) continue;
;;;;;;;;DFS(To,Now);
;;;;}
}
int LCA(int a,int b){
;;;;if(Depth[a]<Depth[b]) swap(a,b);
;;;;for(int i=19;i>=0;i--){
;;;;;;;;if(Depth[Fa[a][i]]>=Depth[b]) a=Fa[a][i];
;;;;}
;;;;if(a==b) return a;
;;;;for(int i=19;i>=0;i--){
;;;;;;;;if(Fa[a][i]!=Fa[b][i]){
;;;;;;;;;;;;a=Fa[a][i];
;;;;;;;;;;;;b=Fa[b][i];
;;;;;;;;}
;;;;}
;;;;return Fa[a][0];
}
int Get(int a,int b){
;;;;int lca=LCA(a,b);
;;;;return Depth[a]+Depth[b]-2*Depth[lca];
}
bool Query(int a,int b,int c,int d){
;;;;int Lca1=LCA(a,b);
;;;;int Lca2=LCA(c,d);
;;;;int Dis1=Get(a,b);
;;;;int Dis2=Get(c,d);
;;;;int Judge1=Get(Lca1,c)+Get(Lca1,d);
;;;;int Judge2=Get(Lca2,a)+Get(Lca2,b);
;;;;if(Judge1==Dis2||Judge2==Dis1) return true;
// ;;;;if(LCA(Lca1,Lca2)==Lca2&&(LCA(Lca1,d)==Lca1||LCA(Lca1,c)==Lca1)) return true;
// ;;;;if(LCA(Lca1,Lca2)==Lca1&&(LCA(Lca2,a)==Lca2||LCA(Lca2,b)==Lca2)) return true;
;;;;return false;
}
void Solve(){
;;;;int n,q;
;;;;scanf("%d%d",&n,&q);
;;;;Total=0;
;;;;memset(Head,0,sizeof(int)*(n+1));
;;;;memset(Depth,0,sizeof(int)*(n+1));
;;;;memset(Fa,0,sizeof(int)*(n+1)*21);
;;;;for(int i=1;i<n;i++){
;;;;;;;;scanf("%d%d",&In1,&In2);
;;;;;;;;Edge_Add(In1,In2);
;;;;;;;;Edge_Add(In2,In1);
;;;;}
;;;;DFS(1,1);
;;;;for(int i=1;i<=19;i++){
;;;;;;;;for(int j=1;j<=n;j++){
;;;;;;;;;;;;Fa[j][i]=Fa[Fa[j][i-1]][i-1];
;;;;;;;;}
;;;;}
;;;;while(q-->0){
;;;;;;;;scanf("%d%d%d%d",&In1,&In2,&In3,&In4);
;;;;;;;;printf("%s\n",Query(In1,In2,In3,In4)?"Yes":"No");
;;;;}
}
int main(){
;;;;int c,T;
;;;;scanf("%d%d",&c,&T);
;;;;while(T-->0) Solve();
;;;;return 0;
}
