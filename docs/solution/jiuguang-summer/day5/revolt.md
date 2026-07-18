# 推翻暴政

## 题意简述

奇数个同伴按顺序到达渡口。每轮新到两人，与上一轮留下的一人组成三人，从中选两人过河，代价为二者时间最大值，最后剩下一人独自过河。求最小总代价。

## 部分分

每轮有三种选择，递归枚举可以得到指数复杂度。注意未来只与当前留下者有关，因此令状态表示当前轮结束后留下某人的最小附加代价，可以得到 $\mathcal{O}(n^2)$ DP。

## 正解

设当前加入的是 $a_{i-1},a_i$，旧状态留下者为 $x$。若让旧状态留下者继续留下，则本轮代价为 $\max(a_{i-1},a_i)$；若留下 $i-1$，则代价为 $\max(x,a_i)$；若留下 $i$，则代价为 $\max(x,a_{i-1})$。把每轮固定增加的 $\max(a_{i-1},a_i)$ 记作全局 `Tag`，剩余转移只需要维护 $f_x$ 与 $f_x+a_x$ 的区间最小值。对 $a_x\le v$ 和 $a_x>v$ 分别查询，即可用离散化线段树完成每轮转移。

## 复杂度

每轮两次查询、两次单点插入，时间复杂度为 $\mathcal{O}(n\log n)$，空间复杂度为 $\mathcal{O}(n)$。状态值与答案需要使用 `long long`。

## 参考代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 200010
#define LSon Node[Now].LeftSon
#define RSon Node[Now].RightSon
using namespace std;
const long long INF=10000000000000000;

int n,m,cnt=0,Line[MAXN],Mapping[MAXN];
long long Tag=0;

void Discrete() {sort(Mapping+1,Mapping+n+1);m=unique(Mapping+1,Mapping+n+1)-Mapping-1;return;}
int Find(int x) {return lower_bound(Mapping+1,Mapping+m+1,x)-Mapping;}

struct node {
    int l,r,LeftSon,RightSon;
    long long Min,MinSum;
}Node[MAXN<<2];

void Update(int Now) {Node[Now].Min=min(Node[LSon].Min,Node[RSon].Min);Node[Now].MinSum=min(Node[LSon].MinSum,Node[RSon].MinSum);return;}

int Build(int l,int r) {
    int Now=++cnt;
    Node[Now]={l,r,0,0,INF,INF};
    if (l==r) return Now;
    int Mid=(l+r)>>1;
    LSon=Build(l,Mid);RSon=Build(Mid+1,r);
    return Now;
}

void Modify(int Now,int Pos,long long Val) {
    if (Node[Now].l==Node[Now].r) {
        Node[Now].Min=min(Node[Now].Min,Val);
        Node[Now].MinSum=min(Node[Now].MinSum,Val+Mapping[Node[Now].l]);
        return;
    }
    int Mid=(Node[Now].l+Node[Now].r)>>1;
    if (Pos<=Mid) Modify(LSon,Pos,Val);
    else Modify(RSon,Pos,Val);
    Update(Now);return;
}

long long Query(int Now,int l,int r,int Type) {
    if (l>r||Node[Now].l>r||Node[Now].r<l) return INF;
    if (Node[Now].l>=l&&Node[Now].r<=r) return Type?Node[Now].MinSum:Node[Now].Min;
    return min(Query(LSon,l,r,Type),Query(RSon,l,r,Type));
}

long long Calc(int Val) {
    int Pos=Find(Val);
    return Tag+min(Query(1,1,Pos,0)+Val,Query(1,Pos+1,m,1));
}

int main() {
    freopen("revolt.in","r",stdin);
    freopen("revolt.out","w",stdout);
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&Line[i]),Mapping[i]=Line[i];
    Discrete();
    Build(1,m);
    int Pos=Find(Line[1]);
    Modify(1,Pos,0);
    for (int i=3;i<=n;i+=2) {
        long long Left=Calc(Line[i]);
        long long Right=Calc(Line[i-1]);
        Tag+=max(Line[i],Line[i-1]);
        Pos=Find(Line[i-1]);
        Modify(1,Pos,Left-Tag);
        Pos=Find(Line[i]);
        Modify(1,Pos,Right-Tag);
    }
    printf("%lld\n",Tag+Node[1].MinSum);
    return 0;
}
```
