# 归零

## 题目简述

给定 $n$ 盏星灯，单独归零第 $i$ 盏的代价为 $a_i$，同时归零相邻的第 $i,i+1$ 盏的代价为 $b_i$。每盏星灯必须恰好被归零一次，求最小总代价。

## 第一档部分分

这部分 $n$ 很小，可以考虑直接搜索。

从左到右考虑第一盏还没有归零的星灯 $i$。可以选择单独归零第 $i$ 盏，也可以在 $i<n$ 时同时归零第 $i,i+1$ 盏。递归枚举所有选择即可。

## 特殊性质

若对于任意 $1\leq i<n$，都有 $b_i=a_i+a_{i+1}$，那么同时归零相邻两盏星灯并不会比单独归零它们更优。

于是答案就是

$$
\sum_{i=1}^{n}a_i.
$$

## 正解

考虑最后一次操作。

若第 $i$ 盏星灯是单独归零的，那么前 $i-1$ 盏星灯已经全部归零，代价为 $dp_{i-1}+a_i$。

若第 $i$ 盏星灯和第 $i-1$ 盏星灯一起归零，那么前 $i-2$ 盏星灯已经全部归零，代价为 $dp_{i-2}+b_{i-1}$。

因此，令 $dp_i$ 表示归零前 $i$ 盏星灯的最小代价，可以得到

$$
dp_i=\min(dp_{i-1}+a_i,\ dp_{i-2}+b_{i-1}).
$$

初始时 $dp_0=0,dp_1=a_1$。从左到右递推即可。

## 复杂度

时间复杂度为 $\mathcal{O}(n)$，空间复杂度为 $\mathcal{O}(n)$。若只保留前两项，空间复杂度可以优化到 $\mathcal{O}(1)$。

## 参考代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 1000100
using namespace std;

int n,a[MAXN],b[MAXN];
long long dp[MAXN];

int main() {
    freopen("reset.in","r",stdin);
    freopen("reset.out","w",stdout);
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    for (int i=1;i<=n-1;i++) scanf("%d",&b[i]);
    dp[0]=0;dp[1]=a[1];
    for (int i=2;i<=n;i++) {
        dp[i]=min(dp[i-1]+1ll*a[i],dp[i-2]+1ll*b[i-1]);
    }
    printf("%lld\n",dp[n]);
    return 0;
}
```
