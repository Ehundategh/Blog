# 星语楠尘

## 题意简述

给定一棵带颜色的树。选择一个根后，要求每个非根结点对应的子树都同色。判断是否存在合法根，并输出任意一个。

## 部分分

枚举根并重新 DFS 检查所有子树同色，复杂度为 $\mathcal{O}(n^2)$。在链上可以发现：所有异色边必须都与同一个候选根有关，否则总会留下一个不稳定支系。

## 正解

若整棵树没有异色边，任意点都是合法根。否则取任意一条异色边 $(u,v)$。合法根若存在，必然是 $u$ 或 $v$ 之一；因为一条异色边的两个端点不可能同时落在某个非根同色子树内部。于是只需要检查 $u$ 与 $v$：遍历所有边，若存在异色边且两个端点都不是候选根，则该候选不合法。

## 复杂度

每组数据只需线性遍历边，时间复杂度为 $\mathcal{O}(n)$，空间复杂度为 $\mathcal{O}(n)$。

## 参考代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 100010
using namespace std;

struct edge {
    int St,Ed;
}Edge[MAXN];

int T,n,Col[MAXN];

bool Check(int Root) {
    for (int i=1;i<=n-1;i++)
        if (Col[Edge[i].St]!=Col[Edge[i].Ed]&&Edge[i].St!=Root&&Edge[i].Ed!=Root) return 0;
    return 1;
}

void Solve() {
    scanf("%d",&n);
    for (int i=1;i<=n-1;i++) {
        scanf("%d%d",&Edge[i].St,&Edge[i].Ed);
    }
    for (int i=1;i<=n;i++) scanf("%d",&Col[i]);
    int u=0,v=0;
    for (int i=1;i<=n-1;i++) {
        if (Col[Edge[i].St]!=Col[Edge[i].Ed]) {
            u=Edge[i].St;v=Edge[i].Ed;
            break;
        }
    }
    if (!u) puts("YES"),puts("1");
    else if (Check(u)) puts("YES"),printf("%d\n",u);
    else if (Check(v)) puts("YES"),printf("%d\n",v);
    else puts("NO");
    return;
}

int main() {
    freopen("stardust.in","r",stdin);
    freopen("stardust.out","w",stdout);
    scanf("%d",&T);
    while (T-->0){Solve();}
    return 0;
}
```
