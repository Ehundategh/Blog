# ST 表

ST 表（Sparse Table）用于解决一类静态区间询问问题。这里的「静态」指数组建好之后不再修改，只需要多次查询某个区间的信息。

我们以区间最大值为例。给定一个长度为 $n$ 的序列 $a$，每次询问区间 $[l,r]$ 的最大值：

$$
\max_{l\le i\le r} a_i
$$

## 朴素做法

一个显然的思路是每次询问都从 $l$ 扫到 $r$，维护当前最大值。这样单次询问是 $\mathcal{O}(n)$ 的，如果询问次数很多，就会被卡掉。

考虑能不能预处理一些区间信息。由于区间数量是 $\mathcal{O}(n^2)$ 的，不能把所有 $[l,r]$ 的答案都直接存下来。于是我们只存一些特殊长度的区间。

## 倍增区间

令 $f_{i,j}$ 表示从位置 $i$ 开始，长度为 $2^j$ 的区间最大值。也就是：

$$
f_{i,j}=\max(a_i,a_{i+1},\ldots,a_{i+2^j-1})
$$

长度为 $2^j$ 的区间可以拆成两个长度为 $2^{j-1}$ 的区间，所以有转移：

$$
f_{i,j}=\max(f_{i,j-1},f_{i+2^{j-1},j-1})
$$

这一步就是 ST 表预处理的核心。

## 查询

接下来考虑如何用这些倍增区间回答任意 $[l,r]$。

设区间长度为 $len=r-l+1$，取

$$
k=\lfloor\log_2 len\rfloor
$$

那么 $2^k\le len$。我们取两个长度为 $2^k$ 的区间：

- 左边一段：$[l,l+2^k-1]$。
- 右边一段：$[r-2^k+1,r]$。

这两段一定能覆盖整个 $[l,r]$，中间可以有重叠。由于最大值满足重复贡献不影响答案，所以答案就是：

$$
\max(f_{l,k},f_{r-2^k+1,k})
$$

这里也可以看出 ST 表为什么不能直接维护区间和：区间和被重复覆盖后会算多。

## 代码

下面给出区间最大值的写法。下标从 $1$ 开始。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=100000+10;
const int MAXLOG=20;

int n,m;
int a[MAXN],Log[MAXN],ST[MAXN][MAXLOG];

void Init(){
    Log[1]=0;
    for(int i=2;i<MAXN;i++){
        Log[i]=Log[i>>1]+1;
    }
}

void Build(){
    for(int i=1;i<=n;i++) ST[i][0]=a[i];
    for(int j=1;(1<<j)<=n;j++){
        for(int i=1;i+(1<<j)-1<=n;i++){
            ST[i][j]=max(ST[i][j-1],ST[i+(1<<(j-1))][j-1]);
        }
    }
}

int Query(int l,int r){
    int k=Log[r-l+1];
    return max(ST[l][k],ST[r-(1<<k)+1][k]);
}

int main(){
    Init();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    Build();
    while(m--){
        int l,r;
        scanf("%d%d",&l,&r);
        printf("%d\n",Query(l,r));
    }
    return 0;
}
```

## 复杂度

预处理时一共有 $\mathcal{O}(\log n)$ 层，每一层最多有 $\mathcal{O}(n)$ 个状态，所以预处理复杂度为

$$
\mathcal{O}(n\log n)
$$

每次查询只需要取两个预处理好的区间，复杂度为

$$
\mathcal{O}(1)
$$

空间复杂度为

$$
\mathcal{O}(n\log n)
$$

## 注意事项

- ST 表只适合没有修改的区间询问。
- 查询时右区间起点是 `r-(1<<k)+1`，这个 `+1` 很容易漏。
- `MAXLOG` 至少要开到 $\lfloor\log_2 n\rfloor+1$。
- 能用两段重叠区间查询，是因为最大值、最小值、$\gcd$ 这类运算重复贡献不影响结果。
