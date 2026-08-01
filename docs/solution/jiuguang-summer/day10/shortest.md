# 我们最好的最短路

## 题意简述

给出一张 $n$ 个点、$m$ 条边的连通无向图，满足 $m-n\leq 20$。多次询问两点之间的最短路。

## Hint

??? tip "提示"
    任取一棵生成树，非树边只有常数条。把所有非树边端点作为关键点，从每个关键点运行一次 Dijkstra。

## 数据点 $1\sim 2$

使用 Floyd 预处理任意两点之间的最短路。时间复杂度为 $\mathcal{O}(n^3+q)$，空间复杂度为 $\mathcal{O}(n^2)$。

## 数据点 $3\sim 4$

图是一棵树。倍增预处理最近公共祖先，并记录根到每个结点的距离 $d_u$。树上两点距离为

$$
\operatorname{dist}_T(u,v)=d_u+d_v-2d_{\operatorname{LCA}(u,v)}.
$$

## 数据点 $5\sim 6$

询问数较小时，可以对每次询问从起点运行 Dijkstra。时间复杂度为 $\mathcal{O}(qm\log n)$。

## 正解

从原图中任取一棵生成树 $T$。非树边数量为

$$
m-(n-1)=m-n+1\leq 21.
$$

把所有非树边的两个端点放入集合 $K$，则 $\lvert K\rvert\leq 42$。

先在生成树上倍增预处理最近公共祖先，从而支持树上距离 $\operatorname{dist}_T(u,v)$。再从每个关键点 $k\in K$ 出发，在原图上运行一次 Dijkstra，记到结点 $v$ 的最短距离为 $\operatorname{dist}_k(v)$。

对于询问 $(u,v)$，答案为

$$
\min\left\{
\operatorname{dist}_T(u,v),
\min_{k\in K}\bigl(\operatorname{dist}_k(u)+\operatorname{dist}_k(v)\bigr)
\right\}.
$$

若一条最短路不经过非树边，那么它完全位于生成树中，只能是树上 $u$ 到 $v$ 的唯一简单路径，第一项得到答案。

若一条最短路经过非树边，那么它必然经过某条非树边的端点 $k\in K$。沿最短路在 $k$ 处分开，有

$$
\operatorname{dist}_k(u)+\operatorname{dist}_k(v)
\leq \operatorname{dist}(u,v).
$$

左侧本身对应一条从 $u$ 经过 $k$ 到 $v$ 的合法路线，又不可能小于全局最短路，所以该关键点给出的候选恰好等于答案。

## 复杂度分析

总时间复杂度为

$$
\mathcal{O}\bigl(n\log n+\lvert K\rvert m\log n+q(\lvert K\rvert+\log n)\bigr),
$$

空间复杂度为 $\mathcal{O}(n\log n+\lvert K\rvert n+m)$。边权与路径长度需要使用 `long long`。

## 参考代码

[shortest.cpp](/Blog/assets/solution/jiuguang-summer/day10/std/shortest.cpp)
