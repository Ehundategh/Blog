# ST 表

ST 表（Sparse Table）是一种用于处理静态区间查询的数据结构。它适合解决区间最大值、区间最小值和区间 $\gcd$ 等满足可重复贡献性质的问题。

!!! note "适用范围"
    ST 表支持预处理后 $O(1)$ 查询区间最值，但不支持修改。如果题目存在单点修改或区间修改，通常要考虑线段树、树状数组或其他可动态维护的数据结构。

## 问题模型

给定长度为 $n$ 的数组 $a$，需要多次回答区间 $[l,r]$ 的最大值：

$$
\max_{l \le i \le r} a_i
$$

如果每次直接扫描区间，单次查询复杂度为 $O(n)$。当询问次数很大时，需要先预处理数组信息。

## 核心思想

ST 表使用倍增思想维护区间信息。定义：

$$
f_{i,j} = \max(a_i, a_{i+1}, \ldots, a_{i+2^j-1})
$$

也就是说，$f_{i,j}$ 表示从位置 $i$ 开始、长度为 $2^j$ 的区间最大值。

转移时，将长度为 $2^j$ 的区间拆成两个长度为 $2^{j-1}$ 的区间：

$$
f_{i,j} = \max(f_{i,j-1}, f_{i+2^{j-1},j-1})
$$

## 预处理

先初始化长度为 $1$ 的区间：

$$
f_{i,0}=a_i
$$

再枚举区间长度的指数 $j$，计算所有起点 $i$。

```cpp
for (int i = 1; i <= n; i++) {
    st[i][0] = a[i];
}

for (int j = 1; (1 << j) <= n; j++) {
    for (int i = 1; i + (1 << j) - 1 <= n; i++) {
        st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
}
```

## 查询

查询区间 $[l,r]$ 时，令：

$$
k = \lfloor \log_2(r-l+1) \rfloor
$$

取两个长度为 $2^k$ 的区间覆盖原区间：

- 左区间：$[l,l+2^k-1]$
- 右区间：$[r-2^k+1,r]$

由于最大值允许重复覆盖，答案为：

$$
\max(f_{l,k}, f_{r-2^k+1,k})
$$

```cpp
int query(int l, int r) {
    int k = lg[r - l + 1];
    return max(st[l][k], st[r - (1 << k) + 1][k]);
}
```

## 完整模板

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 100000 + 5;
const int K = 20;

int n, q;
int a[N], lg[N], st[N][K];

void build() {
    lg[1] = 0;
    for (int i = 2; i <= n; i++) {
        lg[i] = lg[i >> 1] + 1;
    }

    for (int i = 1; i <= n; i++) {
        st[i][0] = a[i];
    }

    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query(int l, int r) {
    int k = lg[r - l + 1];
    return max(st[l][k], st[r - (1 << k) + 1][k]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    build();

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << query(l, r) << '\n';
    }

    return 0;
}
```

## 复杂度

预处理需要枚举 $O(\log n)$ 层，每层最多 $O(n)$ 个状态。

- 预处理时间复杂度：$O(n \log n)$
- 查询时间复杂度：$O(1)$
- 空间复杂度：$O(n \log n)$

## 正确性说明

预处理时，$f_{i,j}$ 被拆成两个相邻的长度为 $2^{j-1}$ 的区间。这两个区间正好覆盖 $[i,i+2^j-1]$，因此转移能得到该区间的最大值。

查询时，$k$ 是不超过区间长度的最大二进制指数。区间 $[l,l+2^k-1]$ 和 $[r-2^k+1,r]$ 都包含在 $[l,r]$ 内，并且它们的并集覆盖整个查询区间。最大值查询允许两个区间重叠，所以两段最大值再取最大，就是整个区间的最大值。

## 常见坑点

- `K` 要开到 $\lfloor \log_2 n \rfloor + 1$，否则高层状态会越界。
- 查询区间通常是闭区间，注意 `r - (1 << k) + 1` 的起点。
- ST 表不能处理修改。
- 如果维护的是区间和，不能用两个重叠区间查询，因为区间和不允许重复贡献。

