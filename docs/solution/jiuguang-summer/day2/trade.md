# 商路烛影

## 题意简述

给定一棵有根二叉树，第 $i$ 个节点的权值为 $w_i$。对于每个节点 $x$，统计满足 $u$ 在 $x$ 的左儿子子树内，$v$ 在 $x$ 的右儿子子树内，并且 $w_u<w_x<w_v$ 的有序点对 $(u,v)$ 数量。

显然，每一个合法点对的中转点 $x$ 都是唯一的。若记左儿子子树内权值小于 $w_x$ 的节点数量为 $L_x$，右儿子子树内权值大于 $w_x$ 的节点数量为 $R_x$，那么节点 $x$ 对答案的贡献就是 $L_xR_x$。

## 数据点 $1\sim 8$

这部分 $n\leq 2000$。

对于每个节点 $x$，分别遍历其左儿子子树与右儿子子树，统计权值小于和大于 $w_x$ 的节点数量即可，时间复杂度为 $\mathcal{O}(n^2)$。

## 数据点 $9\sim 12$

特殊性质保证二叉树按照编号自然连接，因此整棵树的高度为 $\mathcal{O}(\log n)$。

考虑对于每个节点维护其子树内所有权值组成的有序序列。得到两个儿子的序列以后，可以通过二分查询出 $L_x,R_x$，再使用归并排序的方法合并两个儿子的序列，并插入 $w_x$。

每个权值在树的每一层至多参与一次归并，总时间复杂度为 $\mathcal{O}(n\log n)$。

## 正解

首先对原树进行一次 DFS，求出每个节点的 DFN 序与子树大小。这样任意一个节点 $u$ 的子树都对应 DFN 序上的连续区间。

于是，求左儿子子树中权值小于 $w_x$ 的节点数量，可以转化为一个二维偏序问题：节点的 DFN 序需要落在一段区间中，权值需要小于给定值。

将所有节点按照权值从小到大排序，并使用树状数组维护已经加入节点的 DFN 序。处理节点 $x$ 时，树状数组中只保留权值小于 $w_x$ 的节点，那么在左儿子子树对应的 DFN 区间上查询区间和，得到的就是 $L_x$。

由于题目要求严格小于，所以相同权值的节点必须放在同一组中。对于一组权值相同的节点，应该先完成这一组的所有查询，再将这一组节点的 DFN 序加入树状数组。

同理，将所有节点按照权值从大到小处理，树状数组中只保留权值大于 $w_x$ 的节点，在右儿子子树对应的区间上查询即可得到 $R_x$。相同权值仍然需要先查询、后加入。

最后计算 $\sum_x L_xR_x$ 即可。排序的时间复杂度为 $\mathcal{O}(n\log n)$，树状数组操作的总时间复杂度为 $\mathcal{O}(n\log n)$，空间复杂度为 $\mathcal{O}(n)$。

## 参考代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 200010
using namespace std;

int C[MAXN];
int lowbit(int x){return x&-x;}
int Query(int x) {
    int Ret=0;
    for (;x;x-=lowbit(x)) Ret+=C[x];
    return Ret;
}
void Modify(int x,int Val) {
    for (;x<MAXN;x+=lowbit(x)) C[x]+=Val;
    return ;
}
struct Q{
    int Value,DFN,Mark,From,Times;
}q[MAXN<<2];
bool cmp(Q a,Q b){return a.DFN<b.DFN;}
int n,MaxD[MAXN],MinD[MAXN],Size[MAXN][2],Val[MAXN],ls[MAXN],rs[MAXN],dfn[MAXN],Line[MAXN],Mapping[MAXN],Back[MAXN],cnt=0,cnd=0,cnq=0;

void Discrete() {
    sort(Line+1,Line+n+1);
    for (int i=1;i<=n;i++) {
        if (i==1||Line[i]!=Line[i-1]) Mapping[++cnt]=Line[i];
    }
    return;
}

int Find(int x) {return lower_bound(Mapping+1,Mapping+cnt+1,x)-Mapping;}

void DFS(int Now) {
    if (Now==0) return;
    dfn[Now]=++cnd;Back[cnd]=Now;
    DFS(ls[Now]);DFS(rs[Now]);
    MaxD[Now]=max(MaxD[ls[Now]],max(MaxD[rs[Now]],dfn[Now]));MinD[Now]=dfn[Now];
    if (ls[Now]) {
        q[++cnq]={Val[Now]-1,MaxD[ls[Now]],Now,0,1};
        q[++cnq]={Val[Now]-1,MinD[ls[Now]]-1,Now,0,-1};
    }
    if (rs[Now]) {
        q[++cnq]={Val[Now],MaxD[rs[Now]],Now,1,1};
        q[++cnq]={Val[Now],MinD[rs[Now]]-1,Now,1,-1};
    }
}

void Deal() {
    sort(q+1,q+cnq+1,cmp);
    int p=0;
    for (int i=1;i<=cnq;i++) {
        while (p<q[i].DFN) {
            p++;
            Modify(Val[Back[p]],1);
        }
        if (q[i].From==0) {
            Size[q[i].Mark][0]+=Query(q[i].Value)*q[i].Times;
        }
        else {
            Size[q[i].Mark][1]+=(Query(cnt)-Query(q[i].Value))*q[i].Times;
        }
    }
    return ;
}

int main() {
    freopen("trade.in","r",stdin);
    freopen("trade.out","w",stdout);
    memset(Size,0,sizeof(Size));
    scanf("%d",&n);
    for (int i=1;i<=n;i++) {
        scanf("%d",&Line[i]); Val[i]=Line[i];
    }
    Discrete();for (int i=1;i<=n;i++) Val[i]=Find(Val[i]);
    for (int i=1;i<=n;i++) {
        scanf("%d%d",&ls[i],&rs[i]);
    }
    DFS(1);
    Deal();long long Ans=0;
    for (int i=1;i<=n;i++) {
        Ans+=1ll*Size[i][0]*Size[i][1];
    }
    printf("%lld\n",Ans);
    return 0;
}
```
