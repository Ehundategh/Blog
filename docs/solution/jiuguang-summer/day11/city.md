# 策划道路

## 题意简述

给出一棵 $n$ 个结点的带权树。每个方案独立地新增结点 $n+1$，并用权值为 $x$ 的边连接到原结点 $k$，求新树中全部有序点对的距离和。

## Hint

??? tip "提示"
    设原树全部有序点对距离和为 $S$，结点 $k$ 到全部原结点的距离和为 $D_k$。方案答案为 $S+2(D_k+nx)$，只需换根求出全部 $D_k$。

## 数据点 $1\sim 3$

对每份方案直接建出新树，再从每个结点出发搜索。时间复杂度为 $\mathcal{O}(qn^2)$。

## 数据点 $4\sim 7$

记原树全部有序点对距离和为 $S$，并定义

$$
D_k=\sum_{v=1}^{n}\operatorname{cost}(k,v).
$$

新结点到原结点 $v$ 的距离为 $x+\operatorname{cost}(k,v)$，反向距离相同，因此一份方案的答案为

$$
S+2(D_k+nx).
$$

固定根后，边 $(u,v)$ 两侧分别有 $\operatorname{Size}(v)$ 与 $n-\operatorname{Size}(v)$ 个结点，其对 $S$ 的贡献为

$$
2\operatorname{Size}(v)\bigl(n-\operatorname{Size}(v)\bigr)w_{u,v}.
$$

这一档可以预处理 $S$，再对每个方案搜索求 $D_k$。

## 正解

任选结点 $1$ 为根。令 $\operatorname{Size}(u)$ 表示 $u$ 的子树大小，令 $F_u$ 表示 $u$ 到其子树内全部结点的距离和。若 $v$ 枚举 $u$ 的儿子，则

$$
\begin{aligned}
\operatorname{Size}(u)&=1+\sum_v\operatorname{Size}(v),\\
F_u&=\sum_v\left(F_v+\operatorname{Size}(v)w_{u,v}\right).
\end{aligned}
$$

所以 $D_1=F_1$。

接下来换根。设 $v$ 是 $u$ 的儿子，边权为 $w$。根从 $u$ 移到 $v$ 后，$v$ 子树内的 $\operatorname{Size}(v)$ 个结点距离均减少 $w$，其余结点距离均增加 $w$，所以

$$
\begin{aligned}
D_v
&=D_u-\operatorname{Size}(v)w
+\bigl(n-\operatorname{Size}(v)\bigr)w\\
&=D_u+\bigl(n-2\operatorname{Size}(v)\bigr)w.
\end{aligned}
$$

第二次搜索即可求出全部 $D_u$。又因为每个有序点对 $(u,v)$ 恰好在 $D_u$ 中出现一次，原树距离和为

$$
S=\sum_{u=1}^{n}D_u.
$$

最后对每份方案输出 $S+2(D_k+nx)$。

## 复杂度分析

预处理时间复杂度为 $\mathcal{O}(n)$，每次询问为 $\mathcal{O}(1)$，总时间复杂度为 $\mathcal{O}(n+q)$，空间复杂度为 $\mathcal{O}(n)$。

## 参考代码

[city.cpp](/Blog/assets/solution/jiuguang-summer/day11/std/city.cpp)
