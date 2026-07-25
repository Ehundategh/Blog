# 万象启星环

## 题意简述

求长度为 $n$ 的有序序列 $(x_1,x_2,\ldots,x_n)$ 的数量，满足 $1\le x_i\le m$，$\sum x_i$ 是 $p$ 的倍数，且至少有一个 $x_i$ 为质数。答案对 $998{,}244{,}353$ 取模。

## Hint

把数按模 $p$ 的余数分类。所有序列的计数可以用循环卷积转移；不含质数的序列只需要把可选数改成非质数，最后相减即可。

??? note "提示"
    设 $A_r$ 为 $[1,m]$ 中余数为 $r$ 的数的个数，$B_r$ 为其中非质数的个数。答案等于使用 $A$ 转移 $n$ 次后余数 $0$ 的方案数，减去使用 $B$ 转移 $n$ 次后余数 $0$ 的方案数。

## 解法

先用线性筛求出 $1\sim m$ 中的质数。记

$$
\operatorname{Count}_{0,r}=\#\{x\mid 1\le x\le m,\ x\equiv r\pmod p\},
$$

$$
\operatorname{Count}_{1,r}=\#\{x\mid 1\le x\le m,\ x\equiv r\pmod p,\ x\text{ 不是质数}\}.
$$

对于一个状态向量 $F$，$F_r$ 表示当前序列和模 $p$ 为 $r$ 的方案数。每加入一个数，本质上做一次循环卷积：

$$
F'_r=\sum_{i=0}^{p-1}F_i\operatorname{Count}_{(r-i)\bmod p}.
$$

由于 $n$ 很大，将卷积写成 $p\times p$ 的循环矩阵，然后快速幂求第 $n$ 次转移。分别计算全部序列与全非质数序列，二者相减即为至少包含一个质数的序列数。

## 复杂度

线性筛为 $\mathcal{O}(m)$。矩阵规模为 $p\le100$，快速幂复杂度为 $\mathcal{O}(p^3\log n)$。

## 参考代码

[circum.cpp](/Blog/assets/solution/jiuguang-summer/day6/std/circum.cpp)
