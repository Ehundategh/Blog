# 无终奇语

## 题意简述

给定正整数序列 $h_i$。可以选择一个长度不超过 $k$ 的连续区间直接斩杀，再额外造成不超过 $c$ 的伤害；被攻击过的士兵必须构成一个连续区间。求可攻击区间的最大长度。

## 部分分

枚举攻击区间 $[l,r]$ 与技能区间，可以得到一个朴素做法。固定 $[l,r]$ 后，最优技能区间一定是其中长度不超过 $k$ 的最大子段和，所以问题转化为判断 $\sum_{i=l}^r h_i-\operatorname{MaxK}(l,r)\le c$。

## 正解

因为 $h_i$ 均为正数，最优技能区间可以视为长度恰好为 $k$ 的子段，边界不足时由窗口控制。枚举左端点，右端点单调右移；每加入一个新的右端点，只会新增一个长度为 $k$ 的候选子段。用单调队列维护当前区间内候选子段和的最大值，即可在 $\mathcal{O}(1)$ 时间判断当前右端点能否继续右移。

## 复杂度

左右端点与每个候选子段都只进出一次，时间复杂度为 $\mathcal{O}(n)$，空间复杂度为 $\mathcal{O}(n)$。前缀和需要使用 `long long`。

## 参考代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 200010
using namespace std;

int n,k,Line[MAXN],Ans=0;
long long c,Pre[MAXN];

struct Queue {
    int Tail=0,Head=1,Num[MAXN<<1];
    void Push(int a){Num[++Tail]=a;}
    void PopF(){Head++;} void PopB(){Tail--;}
    int Front(){return Num[Head];} int Back(){return Num[Tail];}
    int Size(){return Tail-Head+1;}
}Q;

long long Calc(int x) {
    return Pre[x]-Pre[x-k];
}

int main() {
    freopen("fable.in","r",stdin);
    freopen("fable.out","w",stdout);
    scanf("%d%d%lld",&n,&k,&c);
    for (int i=1;i<=n;i++) {
        scanf("%d",&Line[i]); Pre[i]=Pre[i-1]+Line[i]*1ll;
    }
    int p=k;
    Q.Push(k);
    for (int i=1;i<=n-k+1;i++) {
        if (Q.Size()&&Q.Front()-k<i-1) Q.PopF();
        long long Max=0;
        if (p<n) { Max=Calc(p+1); if (Q.Size()) Max=max(Max,Calc(Q.Front())); }
        while (p<n&&Pre[p+1]-Pre[i-1]-Max<=c) {
            p++;
            while (Q.Size()&&Calc(Q.Back())<=Calc(p)) Q.PopB();
            Q.Push(p);
            if(p<n) Max=max(Calc(p+1),Calc(Q.Front()));
        }
        Ans=max(p-i+1,Ans);
    }
    printf("%d\n",Ans);
}
```
