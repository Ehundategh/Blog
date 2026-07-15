# 夜奔

## 题意简述

给定长度为 $n$ 的环形字符串 $S$ 和长度为 $m$ 的目标字符串 $T$。从第 $1$ 个字符之前出发，沿着 $1,2,\cdots,n,1,\cdots$ 的顺序向前走。每次经过一个位置，可以选择记录这个位置的字符。求记录出整个 $T$ 至少需要经过多少个位置，若无解则输出 $-1$。

## 部分分

最直接的想法是按照 $T$ 的字符顺序模拟。对于当前需要的字符，从当前位置向后走，直到找到它为止。

当 $n,m$ 很小的时候，这样每个字符最多寻找一整圈，时间复杂度为 $\mathcal{O}(nm)$。若 $T$ 本身已经是 $S$ 或 $S+S$ 的子序列，则继续从上一次记录的位置之后扫描即可，这一部分可以做到 $\mathcal{O}(n+m)$。

## 正解

根据部分分的启发，可以发现：当前已经停在某个位置时，若下一次需要记录字符 $c$，那么一定应该选择从当前位置之后第一次出现的 $c$。选择更晚的位置只会使当前结束位置后移，不可能让后续匹配更优。

于是预处理两个数组：

- `Jump[i][c]` 表示从位置 $i$ 之后继续向前走，第一次遇到字符 $c$ 的位置；
- `Dis[i][c]` 表示这一次转移需要经过的图腾数量。

由于路径是环形的，若在 $i+1\sim n$ 中找不到字符 $c$，就需要绕回到 $1$，并取整个串中字符 $c$ 的第一次出现位置。预处理可以从右往左完成。

实现时最容易出错的是第一个字符。初始位置在第 $1$ 个字符之前，所以代码中令 `Now=1,Ans=1`，先单独判断 $S_1$ 能否作为 $T_1$ 被记录；之后每个字符都通过 `Jump` 转移。

时间复杂度为 $\mathcal{O}(26n+m)$，空间复杂度为 $\mathcal{O}(26n)$。答案需要使用 `long long`。

## 参考代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 200010
using namespace std;
int n,m;
char S[MAXN],T[MAXN];
int Jump[MAXN][26],Dis[MAXN][26],FPos[26];
int main() {
    freopen("dash.in","r",stdin);
    freopen("dash.out","w",stdout);
    memset(FPos,0x3f,sizeof(FPos));
    scanf("%d%d",&n,&m);
    scanf("%s%s",S+1,T+1);
    for (int i=1;i<=n;i++) {
        FPos[S[i]-'a']=min(i,FPos[S[i]-'a']);
    }
    for (int i=n;i>=1;i--) {
        if (i!=n) Jump[i][S[i+1]-'a']=i+1,Dis[i][S[i+1]-'a']=1;
        for (int j=0;j<=25;j++) {
            if (i!=n&&S[i+1]==j+'a') continue;
            if (i==n||!Jump[i+1][j]) {
                if (FPos[j]<=n&&i>=FPos[j]) Jump[i][j]=FPos[j],Dis[i][j]=n-(i-FPos[j]);
            }
            else Jump[i][j]=Jump[i+1][j],Dis[i][j]=Dis[i+1][j]+1;
        }
    }
    int Now=1;
    long long Ans=1;
    if (S[1]!=T[1]) {
        if (!Jump[1][T[1]-'a']) {
            puts("-1"); return 0;
        }
        else Ans+=Dis[1][T[1]-'a'],Now=Jump[1][T[1]-'a'];
    }
    for (int i=2;i<=m;i++) {
        if (!Jump[Now][T[i]-'a']) {
            puts("-1"); return 0;
        }
        else Ans+=Dis[Now][T[i]-'a'],Now=Jump[Now][T[i]-'a'];
    }
    printf("%lld\n",Ans);
    return 0;
}
```
