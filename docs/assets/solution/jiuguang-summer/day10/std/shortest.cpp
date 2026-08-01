#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 100010
#define MAXK 45
using namespace std;

int c,n,m,q,In1,In2,In3,Head[MAXN],TreeHead[MAXN],Total=0,TreeTotal=0;
int SetFa[MAXN],Size[MAXN],Fa[MAXN][22],Dep[MAXN],Key[MAXK],cnt=0;
long long Dis[MAXN],Dist[MAXK][MAXN];
bool Mark[MAXN];

struct edge {
    int Ed,Next;
    long long Val;
}Edge[MAXN<<1],Tree[MAXN<<1];

void Edge_Add(int St,int Ed,int Val){Edge[++Total]={Ed,Head[St],Val};Head[St]=Total;}
void Tree_Add(int St,int Ed,int Val){Tree[++TreeTotal]={Ed,TreeHead[St],Val};TreeHead[St]=TreeTotal;}
int Find(int x){return SetFa[x]==x?x:SetFa[x]=Find(SetFa[x]);}
void Insert(int x){if (!Mark[x]) Mark[x]=1,Key[++cnt]=x;}

void Build() {
    queue <int> Q;
    Dep[1]=1;Q.push(1);
    while (Q.size()) {
        int Now=Q.front();Q.pop();
        for (int i=TreeHead[Now];i;i=Tree[i].Next) {
            int To=Tree[i].Ed;
            if (To==Fa[Now][0]) continue;
            Fa[To][0]=Now;Dep[To]=Dep[Now]+1;
            Dis[To]=Dis[Now]+Tree[i].Val;
            for (int j=1;j<=21;j++) Fa[To][j]=Fa[Fa[To][j-1]][j-1];
            Q.push(To);
        }
    }
}

int LCA(int x,int y) {
    if (Dep[x]<Dep[y]) swap(x,y);
    for (int i=21;i>=0;i--) if (Dep[Fa[x][i]]>=Dep[y]) x=Fa[x][i];
    if (x==y) return x;
    for (int i=21;i>=0;i--) {
        if (Fa[x][i]!=Fa[y][i]) x=Fa[x][i],y=Fa[y][i];
    }
    return Fa[x][0];
}

long long Query(int x,int y) {
    int lca=LCA(x,y);
    return Dis[x]+Dis[y]-2*Dis[lca];
}

priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> Q;

void Dijkstra(int x,int S) {
    memset(Dist[x],0x3f,sizeof(Dist[x]));
    Dist[x][S]=0;Q.emplace(0,S);
    while (Q.size()) {
        long long Value=Q.top().first;
        int Now=Q.top().second;Q.pop();
        if (Value!=Dist[x][Now]) continue;
        for (int i=Head[Now];i;i=Edge[i].Next) {
            int To=Edge[i].Ed;
            if (Dist[x][To]>Dist[x][Now]+Edge[i].Val) {
                Dist[x][To]=Dist[x][Now]+Edge[i].Val;
                Q.emplace(Dist[x][To],To);
            }
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("shortest.in","r",stdin);
    freopen("shortest.out","w",stdout);
#endif
    scanf("%d",&c);
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) SetFa[i]=i,Size[i]=1;
    for (int i=1;i<=m;i++) {
        scanf("%d%d%d",&In1,&In2,&In3);
        Edge_Add(In1,In2,In3);Edge_Add(In2,In1,In3);
        int x=Find(In1),y=Find(In2);
        if (x!=y) {
            if (Size[x]>Size[y]) swap(x,y);
            SetFa[x]=y;Size[y]+=Size[x];
            Tree_Add(In1,In2,In3);Tree_Add(In2,In1,In3);
        }
        else Insert(In1),Insert(In2);
    }
    Build();
    for (int i=1;i<=cnt;i++) Dijkstra(i,Key[i]);
    scanf("%d",&q);
    while (q-->0) {
        scanf("%d%d",&In1,&In2);
        long long Ans=Query(In1,In2);
        for (int i=1;i<=cnt;i++) Ans=min(Ans,Dist[i][In1]+Dist[i][In2]);
        printf("%lld\n",Ans);
    }
    return 0;
}
