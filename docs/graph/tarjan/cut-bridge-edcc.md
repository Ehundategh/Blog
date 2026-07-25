# 割点、桥与边双连通分量

## 无向图中的父边

无向边在链式前向星中要存两个方向。沿 $(u,v)$ 进入 $v$ 后，反向边 $(v,u)$ 不能作为绕开原边的路径。令 `Total=1`，每次连续加入两个方向，则边号互为 `i^1`；递归时传入进入当前结点的边号，只跳过它的唯一反向边。

不能直接按父结点跳过。若 $u,v$ 之间有平行边，另一条平行边仍然能够更新 $\text{low}$；全部跳过会错误地把它们判成桥。

## 桥

对 DFS 树边 $(u,v)$，它是桥，当且仅当

$$
\text{low}_v>\text{dfn}_u.
$$

??? proof "证明"

    若 $\text{low}_v\le\text{dfn}_u$，$v$ 的子树能到达 $u$ 或 $u$ 的祖先，因此存在不经过 $(u,v)$ 的替代路径。

    若 $\text{low}_v>\text{dfn}_u$，$v$ 的子树没有任何边到达 $u$ 及其祖先；它和外部唯一的连接就是 $(u,v)$，删除后一定不连通。

## 割点

对非根结点 $u$，若存在 DFS 儿子 $v$ 满足

$$
\text{low}_v\ge\text{dfn}_u,
$$

则 $u$ 是割点。这里等号不能去掉：子树即使能回到 $u$，删除 $u$ 后仍然无法通过它绕到祖先。DFS 根没有祖先，只有 DFS 儿子数不少于 $2$ 时才是割点。

???+ note "例题：P3469 [POI2008] BLO-Blockade"

    [题目链接](https://www.luogu.com.cn/problem/P3469)。固定被删除的 $u$。每个满足 $\text{low}_v\ge\text{dfn}_u$ 的儿子子树都会成为独立连通块，大小为 $\operatorname{Size}(v)$。

??? success "解法"

    每个被分离的儿子子树先贡献

    $$
    \operatorname{Size}(v)\bigl(n-\operatorname{Size}(v)\bigr).
    $$

    设这些子树大小和为 $S$，剩余部分大小为 $n-S-1$，再加入

    $$
    (n-S-1)(S+1)+(n-1).
    $$

    前一部分以分离子树为第一个端点，后一部分补上剩余区域与 $u$ 作为第一个端点的情况，因此没有重复或遗漏。

??? abstract "复杂度分析"

    一次 DFS，时间复杂度为 $\mathcal{O}(n+m)$。

## 边双连通分量

删去全部桥后，每个剩余连通块恰好是一个边双连通分量。先用 Tarjan 标记桥，再忽略桥 DFS 染色即可。

将每个边双缩成一个结点，并保留原图中的桥。若原图连通，缩点后得到桥树；否则得到森林。若缩点后有环，环上任意桥都能沿环绕开，矛盾。

???+ note "例题：P2860 Redundant Paths G"

    [题目链接](https://www.luogu.com.cn/problem/P2860)。要求加最少的边，使图中不再存在桥。缩点后的桥树每个叶子都只有一条桥和其余部分连接，因此必须成为新增边的端点。

??? success "解法"

    将桥树叶子两两配对，每条新增边使两端之间整条路径进入一个环。设叶子数为 $L$，答案为 $\left\lceil L/2\right\rceil$；只有一个缩点时答案为 $0$。

## 参考代码

- [割点与桥](/Blog/assets/graph/tarjan/code/cut_bridge.cpp)
- [BLO](/Blog/assets/graph/tarjan/code/blo.cpp)
- [边双连通分量](/Blog/assets/graph/tarjan/code/edcc.cpp)
