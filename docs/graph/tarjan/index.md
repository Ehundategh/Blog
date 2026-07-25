# Tarjan 与图连通性

Tarjan 的几种写法看起来分别在求强连通分量、桥、割点与双连通分量；实际上它们都在 DFS 回溯时回答同一个问题：当前 DFS 子树能否绕过当前结点或当前树边，回到更早的位置。

课件原件可在这里下载：[Tarjan 与图连通性](/Blog/assets/graph/tarjan/tarjan-connectivity.pdf)。

## DFS 树与 Low-Link

第一次走到新结点的边构成 DFS 树。无向图中，指向已经访问祖先的边称为返祖边；真正提供绕行的正是这些边。

令 $\text{dfn}_u$ 表示 $u$ 第一次被访问的次序。对无向图，$\text{low}_u$ 表示从 $u$ 的 DFS 子树出发，不经过 $u$ 的父边，能够到达的最小 DFS 次序。因此

$$
\text{low}_u=\min\left(
\text{dfn}_u,
\min_{(u,v)\text{ 为树边}}\text{low}_v,
\min_{(u,v)\text{ 为返祖边}}\text{dfn}_v
\right).
$$

访问 $u$ 时只能确定 $\text{dfn}_u$；完整搜索完儿子 $v$ 后，树边 $(u,v)$ 才能以 $\text{low}_v$ 更新 $u$。返祖边的终点已经被访问，所以直接以 $\text{dfn}_v$ 更新。所有判定都发生在这棵子树回溯的时刻。

有向图不能反向走父边。此时只有指向仍在栈中的结点的边能够更新 $\text{low}$；已经离栈的结点所属 SCC 已经确定，不再属于当前未封闭部分。

## 目录

- [强连通分量](scc.md)：点栈、缩点 DAG 与 2-SAT。
- [割点、桥与边双](cut-bridge-edcc.md)：无向图父边处理、桥树与两道例题。
- [点双连通分量](vdcc.md)：边栈、弹栈边界与成员集合。

所有部分的 DFS 均为 $\mathcal{O}(n+m)$。区别只在于当前维护的栈，以及 $\text{low}$ 与 $\text{dfn}$ 的比较方式。
