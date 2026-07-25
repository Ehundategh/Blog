# 万象启星环

## 题目简述

求长度为 $n$ 的有序序列 $(x_1,x_2,\ldots,x_n)$ 的数量，满足 $1\le x_i\le m$，$\sum x_i$ 是 $p$ 的倍数，且至少有一个 $x_i$ 为质数。答案对 $998{,}244{,}353$ 取模。

## 数据点 $1\sim4$

???+ note "直接 DP"

    直接统计“至少一个质数”不方便，因此改为“所有序列数”减去“不含质数的序列数”。令 $f_{i,r,0/1}$ 表示前 $i$ 个数已确定、和模 $p$ 为 $r$ 的方案数，最后一维区分可选全集与只选非质数。

??? success "转移"

    对每个 $j\in[1,m]$ 枚举加入的数，转移到 $(r+j)\bmod p$。复杂度为 $\mathcal{O}(nmp)$。

## 数据点 $5\sim8$

???+ note "重复转移"

    滚动数组后，每一层都执行同一个线性变换。令列向量 $\bm{x}_i$ 记录各余数的方案数，若 $\bm{A}$ 表示一次转移，则 $\bm{x}_n=\bm{A}^n\bm{x}_0$。

??? success "矩阵"

    令

    $$
    \operatorname{Count}_{0,r}=\left|\left\{x\mid 1\le x\le m,\ x\equiv r\pmod p\right\}\right|,
    $$

    $$
    \operatorname{Count}_{1,r}=\left|\left\{x\mid 1\le x\le m,\ x\equiv r\pmod p,\ x\text{ 不是质数}\right\}\right|.
    $$

    转移矩阵第 $j,k$ 项为 $\operatorname{Count}_{(j-k+p)\bmod p}$。分别对全集与非质数集合快速幂，答案是两者余数 $0$ 的方案数之差。

## 正解

???+ note "计算计数"

    $\operatorname{Count}_{0,r}$ 可以用带余除法直接求出；再用线性筛找出 $[1,m]$ 中所有质数，从对应余数类扣除即可得到 $\operatorname{Count}_{1,r}$。

??? success "解法"

    构造两张 $p\times p$ 循环矩阵，分别快速幂 $n$ 次。初始向量只有余数 $0$ 的分量为 $1$。两次转移后取余数 $0$ 分量相减。

??? abstract "复杂度分析"

    线性筛为 $\mathcal{O}(m)$，矩阵快速幂为 $\mathcal{O}(p^3\log n)$，总复杂度为 $\mathcal{O}(m+p^3\log n)$。

## 参考代码

[circum.cpp](/Blog/assets/solution/jiuguang-summer/day6/std/circum.cpp)
