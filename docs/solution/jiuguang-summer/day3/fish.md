# 锦鲤

## 题意简述

给定长度为 $n$ 的正整数序列 $w$ 与参数 $k$。对于一个区间 $[l,r]$，记区间和为 $g(l,r)$，区间最小值为 $f(l,r)$。若

$$
g(l,r)\le kf(l,r),
$$

则称这个区间合法。每次询问给定 $l,r$，要求把 $[l,r]$ 划分成最少数量的合法连续段。

## 部分分

一个直接做法是枚举每个子区间，判断它是否合法，然后对询问区间做区间 DP。这样可以通过较小的数据。

接下来考虑贪心。对于一个固定左端点 $l$，合法右端点显然形成一个前缀。因为右端点向右移动时，区间和只会变大，区间最小值只会不增，所以一旦某个右端点不合法，更靠右的位置也不会合法。

因此从当前位置出发时，应该尽量取最远的合法右端点。若不这样做，把第一段缩短只会让后面的待划分区间变长，不可能减少段数。

可以使用双指针预处理 `Jump[i][0]`，表示从 $i$ 出发，取完第一段后下一条尚未被划分的鱼的位置。为了维护当前窗口的最小值，使用单调队列即可。

## 正解

最后只需要加速连续进行贪心跳转的过程。

预处理

$$
\operatorname{Jump}(i,j)
$$

表示从位置 $i$ 出发，连续划分 $2^j$ 段以后，下一条尚未被划分的鱼的位置。于是一次询问 $[l,r]$ 中，从高位到低位尝试跳转：若跳完 $2^j$ 段以后位置仍然不超过 $r$，就执行这次跳转并累加答案。

循环结束后，还剩下最后一段没有被计入。根据前面的贪心证明，这一段直接取到询问右端点即可，所以答案再加一。

预处理时间复杂度为 $\mathcal{O}(n\log n)$，单次询问时间复杂度为 $\mathcal{O}(\log n)$，空间复杂度为 $\mathcal{O}(n\log n)$。

## 参考代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 200010
using namespace std;

int n,q,k;
int Line[MAXN],Jump[MAXN][24],In1,In2;
long long Sum=0;

struct Queue {
    int Tail=0,Head=1,Num[MAXN<<1];
    void Push(int a){Num[++Tail]=a;}
    void PopF(){Head++;} void PopB(){Tail--;}
    int Front(){return Num[Head];} int Back(){return Num[Tail];}
    int Size(){return Tail-Head+1;}
}Q;

int main() {
    freopen("fish.in","r",stdin);
    freopen("fish.out","w",stdout);
    scanf("%d%d%d",&n,&q,&k);
    for (int i=1;i<=n;i++){scanf("%d",&Line[i]);}
    int p=n+1;
    for (int i=n;i>=1;i--) {
        while (Q.Size()&&Line[Q.Back()]>=Line[i]) Q.PopB();
        Q.Push(i);
        int Min=Line[Q.Front()];
        Sum+=Line[i];
        while (Sum>1ll*k*Min) {
            p--;
            if (Q.Size()&&Q.Front()==p) Q.PopF(),Min=Line[Q.Front()];
            Sum-=Line[p];
        }
        Jump[i][0]=p;
    }
    Jump[n+1][0]=n+1;
    for (int j=1;j<=22;j++) {
        for (int i=1;i<=n;i++) {
            Jump[i][j]=Jump[Jump[i][j-1]][j-1];
        }
        Jump[n+1][j]=n+1;
    }
    while (q-->0) {
        scanf("%d%d",&In1,&In2);
        int Now=In1;int Ans=0;
        for (int i=22;i>=0;i--) {
            if (Jump[Now][i]<=In2) {
                Ans+=(1<<i);Now=Jump[Now][i];
            }
        }
        Ans++;
        printf("%d\n",Ans);
    }
    return 0;
}
```
