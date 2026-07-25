#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 300010
using namespace std;
int Total=0,Head[MAXN],Depth[MAXN],Count[MAXN],Fa[MAXN][22],D[MAXN],Diff[MAXN];
struct edge{
    int Ed,Next,Val;
}Edge[MAXN<<1];
void Edge_Add(int St,int Ed,int Val){
    Edge[++Total]={Ed,Head[St],Val};
    Head[St]=Total;
}
struct Plan{
    int u,v,Val,lca;
}p[MAXN];
bool cmp(Plan a,Plan b) {return a.Val<b.Val;}
void DFS(int Now,int From){
    for(int i=1;i<=21;i++){
        Fa[Now][i]=Fa[Fa[Now][i-1]][i-1];
    }
    for(int i=Head[Now];i;i=Edge[i].Next){
        int To=Edge[i].Ed;
        if(To==From) continue;
        D[To]=D[Now]+1;
        Depth[To]=Depth[Now]+Edge[i].Val;
        Fa[To][0]=Now;
        DFS(To,Now);
    }
    return;
}
inline int LCA(int x,int y){
    if(D[x]<D[y]) swap(x,y);
    for(int i=21;i>=0;i--){
        if(D[Fa[x][i]]>=D[y]) x=Fa[x][i];
    }
    if(x==y) return x;
    for(int i=21;i>=0;i--){
        if(Fa[x][i]!=Fa[y][i]){
            x=Fa[x][i];y=Fa[y][i];
        }
    }
    return Fa[x][0];
}
int n,m,In1,In2,In3;
bool Tag=0;
inline int Run(int Now,int From,int cnt,int t){
    int Sum=0,tmp=0;
    for(int i=Head[Now];i;i=Edge[i].Next){
        int To=Edge[i].Ed;
        if(To==From)continue;
        tmp=Run(To,Now,cnt,t);
        Sum+=tmp;
        if(tmp==cnt&&Edge[i].Val>=t){Tag=1;}
    }
    return Sum+Diff[Now];
}
bool Judge(int t){
    int cnt=0;
    Tag=0;
    memset(Diff,0,sizeof(Diff));
    for(int i=1;i<=m;i++){
        if(p[i].Val<=t) continue;
        Diff[p[i].u]++;Diff[p[i].v]++;
        Diff[p[i].lca]-=2;
        cnt++;
    }
    Run(1,1,cnt,p[m].Val-t);
    if(Tag) return 1;
    else return 0;
}
int main(){
    memset(Depth,0,sizeof(Depth));
    memset(Head,0,sizeof(Head));
    memset(D,0,sizeof(D));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;i++){
        scanf("%d%d%d",&In1,&In2,&In3);
        Edge_Add(In1,In2,In3); Edge_Add(In2,In1,In3);
    }
    D[1]=1;
    DFS(1,1);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&p[i].u,&p[i].v);
        p[i].lca=LCA(p[i].u,p[i].v);
        p[i].Val=Depth[p[i].u]+Depth[p[i].v]-2*Depth[p[i].lca];
    }
    sort(p+1,p+m+1,cmp);
    int l=0,r=p[m].Val;
    while(l<r){
        int Mid=(l+r)>>1;
        if(Judge(Mid)) r=Mid;
        else l=Mid+1;
    }
    printf("%d",l);
    return 0;
}