# 树的直径

## 定义

树的直径是一条路径 $u\to v$，使得这条路径上所有边的权值和是所有路径中最大的那一条，也就是树上最长简单路径。

树的直径这部分题目主要依赖对题目要求的观察和推理。我们先从求解树的直径开始。

## 性质

???+ note "直径的数量性质"

    树的直径可以不止一条。

??? proof "证明"

    考虑一棵菊花。以 $1$ 节点为中心，其中边 $(1,i)$ 满足 $\operatorname{d}(1,i)=c$。

    那么任意路径 $i\to j(i\ne j,2\le i,j\le n)$ 的长度均为 $2c$，所以它们都是直径。

???+ note "最远性"

    若树没有负边权，对于树上任意一个点 $u$，在所有 $v\ne u$ 的点 $v$ 中，使得路径 $u\to v$ 长度最大的 $v$ 一定是某一条直径的端点。

??? proof "证明"

    假设 $v$ 是距 $u$ 最远的节点，同时其不在任意一条直径上。任取一条直径 $a\to b$，现在分情况讨论。

    若 $a\to b$ 经过了 $u$，那么其可以拆成 $a\to u,u\to b$ 两段。由于 $v$ 是距 $u$ 最远的节点，有：

    $$\operatorname{d}(u,v)\ge \operatorname{d}(u,a)$$

    所以：

    $$\operatorname{d}(v,b)\ge \operatorname{d}(a,b)$$

    又因为 $a\to b$ 是直径，所以只能 $\operatorname{d}(v,b)=\operatorname{d}(a,b)$，于是 $v$ 也是直径端点，矛盾。

    若 $a\to b$ 没有经过 $u$，那么必然可以在 $a\to b$ 上找到一个点 $p$，使得 $a\to p,p\to b,p\to u$ 仅有 $p$ 一个交点。

    根据假设，有 $\operatorname{d}(u,v)\ge \operatorname{d}(u,b)$，于是：

    $$
    \operatorname{d}(v,p)=\operatorname{d}(v,u)+\operatorname{d}(u,p)
    \ge \operatorname{d}(u,b)+\operatorname{d}(u,p)
    $$

    又有：

    $$
    \operatorname{d}(u,b)+\operatorname{d}(u,p)\ge \operatorname{d}(p,b)
    $$

    所以：

    $$
    \operatorname{d}(v,a)=\operatorname{d}(v,p)+\operatorname{d}(p,a)
    \ge \operatorname{d}(p,b)+\operatorname{d}(p,a)
    =\operatorname{d}(a,b)
    $$

    同上讨论，$v\to a$ 也是直径，矛盾。所以假设不成立，$v$ 一定在某一条直径上。

## 求法

???+ tip "两遍 DFS"

    根据最远性定理中 $u$ 的任意性，任选一个点作为起点进行 $\texttt{DFS}$，可以求得最远点 $v$。

    根据定理知道 $v$ 必然是一条直径的端点，所以我们直接再从 $v$ 出发 $\texttt{DFS}$ 一次，求到 $v$ 的最远点，就是直径上的另外一个端点。回溯时标记所有节点即可。

??? abstract "复杂度分析"

    两次 $\texttt{DFS}$ 均为线性复杂度，所以时间复杂度为 $\mathcal{O}(n)$，空间复杂度为 $\mathcal{O}(n)$。

???+ tip "树形 DP"

    如果需要处理负权边，可以考虑一种基于 DP 的直径求法。

    首先指定一个根节点，那么直径有两种情况：

    - 经过当前根节点。
    - 不经过当前根节点。

    同理，对根节点的每个子树可以继续讨论。设计状态 $f_{u,0/1}$ 分别表示以 $u$ 为一个端点的最长链，以及 $u$ 子树中的直径。

    状态转移为：

    $$
    f_{u,0}=\max_{v\in\operatorname{son}(u)}\{f_{v,0}+\operatorname{d}(u,v)\}
    $$

    $$
    f_{u,1}=\max\left\{
    \max_{v\in\operatorname{son}(u)}f_{v,1},
    \max_{\substack{v_1,v_2\in\operatorname{son}(u)\\v_1\ne v_2}}
    \{f_{v_1,0}+f_{v_2,0}+\operatorname{d}(u,v_1)+\operatorname{d}(u,v_2)\}
    \right\}
    $$

??? abstract "复杂度分析"

    转移时只需要维护最大的两条向下链，不需要枚举所有儿子对。因此时间复杂度为 $\mathcal{O}(n)$，空间复杂度为 $\mathcal{O}(n)$。

## SDOI2011 消防

???+ note "题目描述"

    给定一棵树，求一条长度不超过 $k$ 的链，使得不在链上的点到链的距离的最大值最小。

    数据范围中，树节点个数 $1\le n\le 3\times 10^5$。

??? tip "Hint"

    首先考虑最简单的做法，肯定是枚举一条链，再判断这条链是否满足条件以及是否最优。

    接下来考虑优化枚举链。我们应该有一种直觉，这样的链应该在直径上。

??? success "解法"

    一个直接的做法是枚举一条链，时间复杂度为 $\mathcal{O}(n^2)$；再求这条链是否满足条件并判断是否最优，总复杂度会来到 $\mathcal{O}(n^3)\sim\mathcal{O}(n^3\log n)$，显然无法通过此题。

    我们可以尝试优化上述算法。有两方面可以优化：

    - 枚举更少的链，也就是找到最佳答案的链具有的性质。
    - 更快地求出该链最远点到该链的距离。

    先考虑第一种优化。

    ??? note "关键引理"

        题目中所求的最优链，一定可以取为任意一条直径中的连续段。

    ??? proof "证明"

        设树的一条直径为 $u\to v$。根据最远性定理，树上任意点的最远点必为 $u$ 或 $v$。

        采取反证法，假设存在最优链 $P$，满足 $\operatorname{len}(P)\le k$，且所有点到 $P$ 的最大距离为 $L$，但 $P$ 不是直径 $u\to v$ 的连续段。

        我们断言：所有点到路径 $P$ 的最大距离，等价于直径两个端点 $u,v$ 到 $P$ 的距离的最大值，即：

        $$
        \max_x\operatorname{d}(x,P)=\max\{\operatorname{d}(u,P),\operatorname{d}(v,P)\}
        $$

        对任意点 $x$，其最远点是直径端点之一，因此全局最大距离由直径端点决定。

        在直径 $u\to v$ 上构造路径 $P'$：取直径上点 $l$ 满足 $\operatorname{d}(u,l)=\operatorname{d}(u,P)$，点 $r$ 满足 $\operatorname{d}(r,v)=\operatorname{d}(v,P)$，令 $P'$ 为直径上 $l\to r$ 的连续段。

        易证 $\operatorname{len}(P')\le\operatorname{len}(P)\le k$，满足长度限制。

        根据构造，点 $u,v$ 到 $P'$ 的距离等于到 $P$ 的距离，因此 $P'$ 对应的最大距离仍为 $L$，与 $P$ 效果完全相同。这说明最优链一定可以取在直径的连续段上。

    根据这一条引理，我们可以提取一条直径，那么最优链一定在直径上。还有一个显然的观察：链越长越好。

    所以我们可以在直径上枚举左端点，找到一个最远的右端点，这部分可以用双指针优化，于是枚举所有可能链的时间复杂度可以优化到 $\mathcal{O}(n)$。

    还需要考虑如何求一条链对应的最远距离。其本质就是对直径上被链覆盖的部分以外的距离取最大值，相关信息可以提前 $\texttt{DFS}$ 跑出来。剩下的部分可以使用单调队列维护。

    当然，也可以观察引理证明过程，直接对两个端点求 $\max$，实现会更加直接。

??? abstract "复杂度分析"

    求直径、预处理距离、双指针枚举均为线性复杂度。

    总时间复杂度为 $\mathcal{O}(n)$，空间复杂度为 $\mathcal{O}(n)$。

## 其他性质

在直径相关题目中，还有一些常用性质。

??? note "定理"

    对于正权边的树，所有的直径都有重合部分。

??? proof "证明"

    设存在两条完全不相交的直径 $a\to b$ 与 $c\to d$。由于树连通，存在唯一一条路径连接这两条直径，设其在 $a\to b$ 上的端点为 $x$，在 $c\to d$ 上的端点为 $y$。

    不妨设：

    $$
    \operatorname{d}(a,x)\ge \operatorname{d}(b,x),\quad
    \operatorname{d}(c,y)\ge \operatorname{d}(d,y)
    $$

    由于边权为正，$\operatorname{d}(x,y)>0$。

    那么路径 $a\to c$ 的长度为：

    $$
    \operatorname{d}(a,c)=\operatorname{d}(a,x)+\operatorname{d}(x,y)+\operatorname{d}(y,c)
    $$

    又因为：

    $$
    \operatorname{d}(a,x)\ge \frac{\operatorname{d}(a,b)}2,\quad
    \operatorname{d}(y,c)\ge \frac{\operatorname{d}(c,d)}2
    $$

    而 $a\to b$ 与 $c\to d$ 都是直径，长度相同，记为 $D$。于是：

    $$
    \operatorname{d}(a,c)\ge \frac D2+\operatorname{d}(x,y)+\frac D2>D
    $$

    这与 $D$ 是直径长度矛盾。

    因此两条直径不可能完全不相交，所有直径之间都至少有公共部分。进一步看所有直径的公共部分，若为空，则可以取两条直径使得它们在公共路径上的相交被断开，同样得到上述矛盾。因此所有直径都有重合部分。

??? note "定理"

    对于正权边的树，所有直径的中点必定重合，中点可能在某条边的内部。

??? proof "证明"

    设直径长度为 $D$。对任意一条直径 $a\to b$，其中点定义为路径上到 $a,b$ 距离均为 $\frac D2$ 的位置。这个位置可能是一个点，也可能在某条边的内部。

    反设存在两条直径 $a\to b$ 与 $c\to d$，它们的中点分别为 $p,q$，且 $p\ne q$。

    根据上一条定理，两条直径有重合部分。考虑树中连接 $p,q$ 的路径，长度为 $\operatorname{d}(p,q)>0$。

    在直径 $a\to b$ 上，$p$ 到两个端点的距离均为 $\frac D2$；在直径 $c\to d$ 上，$q$ 到两个端点的距离均为 $\frac D2$。

    从 $p$ 沿 $p\to q$ 走到 $q$ 后，至少可以选择 $c,d$ 中的一个端点，使得从 $p$ 到该端点的路径不经过 $p$ 在 $a\to b$ 上对应较短的一侧。于是可以构造出一条路径，其长度至少为：

    $$
    \frac D2+\operatorname{d}(p,q)+\frac D2>D
    $$

    这与 $D$ 是直径长度矛盾。

    因此所有直径的中点必定重合。
