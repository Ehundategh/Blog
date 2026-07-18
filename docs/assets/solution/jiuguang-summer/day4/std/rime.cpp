#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 200010
#define MAXM 500010
using namespace std;

int n,m,k,c,s,Diff[MAXN],cnt=0,In1,In2,In3,Min[MAXN][2],Fa[MAXN];
bool Key[MAXN];

int Find(int x){return Fa[x]==x?x:Fa[x]=Find(Fa[x]);}

struct edge {
    int St,Ed,Value;
}Edge[MAXM];

bool cmp(edge a,edge b){return a.Value<b.Value;}

long long Ans=0;

int main() {
    freopen("rime.in","r",stdin);
    freopen("rime.out","w",stdout);
    memset(Key,0,sizeof(Key));
    memset(Min,0x3f,sizeof(Min));
    scanf("%d%d%d%d%d",&n,&m,&k,&c,&s);
    for (int i=1;i<=n;i++) Fa[i]=i;
    for (int i=1;i<=k;i++) {
        scanf("%d",&In1); Key[In1]=true;
    }
    for (int i=1;i<=m;i++) {
        scanf("%d%d%d",&In1,&In2,&In3);
        Edge[i]={In1,In2,In3};
    }
    sort(Edge+1,Edge+m+1,cmp);
    for (int i=1;i<=m;i++) {
        if (Key[Edge[i].St]||Key[Edge[i].Ed]) continue;
        if (Find(Edge[i].St)!=Find(Edge[i].Ed)) Fa[Find(Edge[i].St)]=Find(Edge[i].Ed),Ans+=Edge[i].Value;
    }
    for (int i=1;i<=m;i++) {
        int u=Edge[i].St,v=Edge[i].Ed;
        if ((Key[u]&&!Key[v])||(!Key[u]&&Key[v])) {
            if (!Key[u]) swap(u,v);
            if (v==s) Min[u][1]=min(Min[u][1],Edge[i].Value);
            else Min[u][0]=min(Min[u][0],Edge[i].Value);
        }
    }
    int Used=0;
    for (int i=1;i<=n;i++) {
        if (!Key[i]) continue;
        if (Min[i][0]==0x3f3f3f3f) {
            Ans+=1ll*Min[i][1];
            Used++;
        }
        else {
            Ans+=1ll*Min[i][0];
            if (Min[i][1]<Min[i][0]) {
                Diff[++cnt]=Min[i][1]-Min[i][0];
            }
        }
    }
    sort(Diff+1,Diff+cnt+1);
    for (int i=1;i<=cnt&&i<=c-Used;i++) {
        Ans+=Diff[i];
    }
    printf("%lld\n",Ans);
}
