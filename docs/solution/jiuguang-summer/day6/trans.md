# 万山舆共渡

## 题目简述

给定一棵带权树和 $m$ 条运输路径。可以选择一条边使其边权变为 $0$，求所有路径长度最大值的最小可能值。

## 数据点 $1\sim8$

???+ note "一条运输计划"

    当 $m=1$ 时，直接找出这条路径，设长度为 $L$、其中最大边权为 $W_{\max}$。显然清零最大边最优，答案为 $L-W_{\max}$。当 $n,m$ 均不大时，枚举清零哪条边，再重新计算所有路径并取最大值。

## 数据点 $9\sim14$

???+ note "链上的判定"

    二分答案 $t$。原长度不超过 $t$ 的运输计划无需处理；其余所有超时路径都必须经过同一条被清零的道路。

??? success "解法"

    对所有超时区间做差分。设超时路径有 $c$ 条，若某条道路被覆盖了 $c$ 次，它便同时属于全部超时路径。所有这种道路中取权值最大的 $w$；设原最大路径长为 $L_{\max}$，当且仅当 $L_{\max}-w\le t$ 时当前 $t$ 合法。

## 正解

???+ note "树上差分"

    对每条超时路径 $(u,v)$，令 $z=\operatorname{LCA}(u,v)$，作

    $$
    \begin{cases}
    \operatorname{Diff}(u)\leftarrow\operatorname{Diff}(u)+1,\\
    \operatorname{Diff}(v)\leftarrow\operatorname{Diff}(v)+1,\\
    \operatorname{Diff}(z)\leftarrow\operatorname{Diff}(z)-2.
    \end{cases}
    $$

??? success "解法"

    回溯时将儿子的差分和加到父亲。把道路 $(u,\operatorname{Fa}(u))$ 看作结点 $u$ 派生的道路，则回溯后的 $\operatorname{Diff}(u)$ 正是这条道路被多少条超时路径覆盖。

    若存在道路满足 $\operatorname{Diff}(u)=c$ 且边权 $w\ge L_{\max}-t$，清零它后所有超时路径都不超过 $t$；反之，任何可行道路都必须同时满足这两个条件。

??? abstract "复杂度分析"

    LCA 预处理为 $\mathcal{O}(n\log n)$；一次判定为 $\mathcal{O}(n+m)$，总复杂度为 $\mathcal{O}(n\log n+(n+m)\log V)$。

## 参考代码

[trans.cpp](/Blog/assets/solution/jiuguang-summer/day6/std/trans.cpp)
