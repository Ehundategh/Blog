# 银淞止境

## 题意简述

给定带权无向图、关键观测站集合、核心点 $s$ 与额度 $c$。要求选出一棵生成树，使每个关键观测站度数为 $1$，且最多 $c$ 个关键观测站直接连向 $s$，求最小边权和。

## 部分分

直接枚举生成树只适合极小数据。注意关键点只能作为叶子，于是非关键点之间的连边与关键点最终选择哪一条入树边可以拆开考虑。若不存在关键点，问题退化为普通最小生成树。

## 正解

先忽略所有与关键点相连的边，在非关键点诱导出的图上做 Kruskal，得到非关键部分的最小连通代价。之后每个关键点必须独立选择一条连向非关键点的边。对于关键点 $u$，记录它连向非核心非关键点的最小边 `Min[u][0]`，以及连向核心点 $s$ 的最小边 `Min[u][1]`。默认选择 `Min[u][0]`；若只能连向核心，则必须消耗一个额度。其余关键点若改连核心能减少代价，就把差值加入数组，按收益从大到小使用剩余额度。

## 复杂度

Kruskal 与差值排序总复杂度为 $\mathcal{O}(m\log m+k\log k)$，答案需要使用 `long long`。

## 参考代码

```cpp
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
```
