# 灰蕈迷境

## 题意简述

给定若干段幻境，每段需要当前清明值至少为 $a_i$，完成后清明值变为 $x-a_i+b_i$。可以任意排列进入顺序，求能够完成所有幻境的最小初始清明值。

## 部分分

若 $n$ 很小，可以枚举所有排列并模拟。若所有幻境都有 $a_i\le b_i$，完成后清明值不会减少，按照 $a_i$ 从小到大处理即可；若所有幻境都有 $a_i>b_i$，则需要比较相邻两段幻境交换前后的最小需求。

## 正解

把幻境分成两类。对于 $a_i\le b_i$ 的幻境，它们不会降低清明值，应当优先处理，并按 $a_i$ 从小到大排序。对于 $a_i>b_i$ 的幻境，它们会消耗清明值，若相邻两段均属于这一类，交换比较可以得到 $b_i$ 较大的幻境应当排在前面。排序后从前往后模拟：若当前清明值不足 $a_i$，就把初始值补上这部分差额，再执行这段幻境。

## 复杂度

排序为 $\mathcal{O}(n\log n)$，模拟为 $\mathcal{O}(n)$。答案与当前清明值需要使用 `long long`。

## 参考代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct point {
    int a,b;
}P[200010];

bool cmp(point x,point y) {
    if (x.a<=x.b && y.a>y.b) return true;
    if (x.a>x.b && y.a<=y.b) return false;
    else if (x.a<=x.b && y.a<=y.b) return x.a<y.a;
    else return x.b>y.b;
}

int main() {
    freopen("spore.in","r",stdin);
    freopen("spore.out","w",stdout);
    int n;long long Now=0,Ans=0;
    scanf("%d",&n);
    for (int i=1;i<=n;i++) {
        scanf("%d%d",&P[i].a,&P[i].b);
    }
    sort(P+1,P+n+1,cmp);
    for (int i=1;i<=n;i++) {
        if (P[i].a>Now){Ans+=(1ll*P[i].a-Now);Now=1ll*P[i].a;}
        Now-=1ll*P[i].a;Now+=1ll*P[i].b;
    }
    printf("%lld\n",Ans);
    return 0;
}
```
