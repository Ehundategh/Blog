# 千仓平丰歉

## 题目简述

有 $n$ 个数 $c_i$。每次可以选择一个位置，把它增加 $a$ 或 $b$。求任意次操作后，所有数极差的最小值。

## 数据点 $1\sim4$

???+ note "题目描述"

    当 $n$ 很小时，可以枚举最终所有数落入的区间，并逐个判断每个 $c_i$ 能否通过若干次加 $a$、加 $b$ 落入其中。

??? tip "Hint"

    加法操作不会改变 $\gcd(a,b)$ 的余数。这个不变量比原数值更重要。

??? success "解法"

    令 $d=\gcd(a,b)$。每个 $c_i$ 在任意操作后模 $d$ 的余数不变。反过来，由裴蜀定理，足够大的同余位置都可以由 $c_i$ 经过若干次操作到达。因此这一档已经说明：只需考虑余数在模环上的相对位置。

## 正解

???+ note "题目描述"

    令 $r_i=c_i\bmod d$。现在要求在长度为 $d$ 的环上找到最短的一段连续弧，覆盖全部 $r_i$。

??? tip "Hint"

    与其直接找被覆盖部分，不如找哪一段空隙不经过。

??? success "解法"

    将余数排序为 $r_1\le r_2\le\cdots\le r_n$。所有未出现余数形成的空隙中，最大的一个长度为

    $$
    \operatorname{Max}\left(r_1+d-r_n,\ \max_{i=2}^{n}(r_i-r_{i-1})\right).
    $$

    选择这段最大空隙不经过，剩下的短弧恰好覆盖所有余数，所以答案为

    $$
    d-\operatorname{Max}\left(r_1+d-r_n,\ \max_{i=2}^{n}(r_i-r_{i-1})\right).
    $$

    这也给出了构造：把每个数抬高到该短弧中与其同余的位置即可。

??? abstract "复杂度分析"

    排序一次，时间复杂度为 $\mathcal{O}(n\log n)$，空间复杂度为 $\mathcal{O}(n)$。

## 参考代码

[balance.cpp](/Blog/assets/solution/jiuguang-summer/day6/std/balance.cpp)
