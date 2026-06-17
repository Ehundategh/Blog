#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 100010
using namespace std;
int Head[MAXN],Total=0,n,q,In1,In2,In3,k;
int Depth[MAXN],Fa[MAXN][21],d[MAXN];
struct edge{
    int St,Ed,Val;
    int Next;
}Edge[MAXN<<1];
void Edge_Add(int St,int Ed,int Val){
    Edge[++Total]={St,Ed,Val,Head[St]};
    Head[St]=Total;
}
void DFS(int Now,int From){
    d[Now]=d[From]+1;
    Fa[Now][0]=From;
    for(int i=Head[Now];i;i=Edge[i].Next){
        if(Edge[i].Ed==From) continue;
        Depth[Edge[i].Ed]=Depth[Now]+Edge[i].Val;
        DFS(Edge[i].Ed,Now);
    }
}
void Init(){
    for(int i=1;i<=19;i++){
        for(int j=1;j<=n;j++){
            Fa[j][i]=Fa[Fa[j][i-1]][i-1];
        }
    }
}
int LCA(int x,int y){
    if(d[x]<d[y]) swap(x,y);
    for(int i=19;i>=0;i--){
        if(d[Fa[x][i]]>d[y]){
            x=Fa[x][i];
        }
    }
    if(d[x]>d[y])x=Fa[x][0];
    if(x==y) return x;
    for(int i=19;i>=0;i--){
        if(Fa[x][i]!=Fa[y][i]){
            x=Fa[x][i];
            y=Fa[y][i];
        }
    }
    return Fa[x][0];
}
int Dist(int a,int b){
    int lca=LCA(a,b);
    return abs(Depth[a]-Depth[lca])+abs(Depth[b]-Depth[lca]);
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n-1;i++){
        scanf("%d%d%d",&In1,&In2,&In3);
        Edge_Add(In1,In2,In3);
        Edge_Add(In2,In1,In3);
    }
    DFS(1,1);
    Init();
    for(int i=1;i<=q;i++){
        scanf("%d",&k);
        if (k==2) {
            scanf("%d%d",&In1,&In2);
            printf("%d\n",Dist(In1,In2));
        }
        else {
            scanf("%d%d%d",&In1,&In2,&In3);
            int lca1,lca2;
            lca1=LCA(In1,In2);lca2=LCA(In2,In3);
            printf("%d\n",min(Dist(In1,lca1)+Dist(In2,lca1)+Dist(In3,lca1),Dist(In1,lca2)+Dist(In2,lca2)+Dist(In3,lca2)));
        }
    }
    return 0;
}
