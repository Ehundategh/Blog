# 序列询问

## 题意简述

给定一个二进制序列。若当前元素与栈顶相同，则弹出栈顶，否则压入当前元素，由此定义序列的消除结果。

对每次询问 $[l,r]$，枚举分割点 $l\leq m<r$，分别消除左右两段，再把两个消除结果拼接并继续消除。求所有分割点在拼接以后新消除的元素对数之和。

## 数据点 $1\sim 3$

???+ note "题目描述"

    数据范围允许按照定义直接模拟。

??? tip "Hint"

    对每个分割点分别用栈处理左右两段，再拼接两个栈中的序列。

??? success "解法"

    记录拼接后新弹出的元素对数，并对全部分割点求和。时间复杂度为 $\mathcal{O}(qn^2)$。

## 数据点 $4\sim 9$

???+ note "题目描述"

    需要把单个分割点的计算降至常数时间。

??? tip "Hint"

    消除结束后的序列中不存在相邻且相同的元素，因此它一定是一个 $0,1$ 交替序列。

??? success "解法"

    对每次询问，从左向右维护所有前缀的消除长度，从右向左维护所有后缀的消除长度。加入一个元素时，消除结果的长度只会增加 $1$ 或减少 $1$。

    预处理完成后，可以在 $\mathcal{O}(1)$ 时间计算一个分割点，单次询问复杂度为 $\mathcal{O}(n)$，总时间复杂度为 $\mathcal{O}(qn)$。

## 数据点 $10\sim 15$

???+ note "题目描述"

    需要用一个代数量描述区间消除后的长度。

??? tip "Hint"

    定义

    $$
    s_i=
    \begin{cases}
    1,&a_i\equiv i\pmod 2,\\
    -1,&a_i\not\equiv i\pmod 2,
    \end{cases}
    \qquad
    P_i=\sum_{j=1}^{i}s_j.
    $$

??? success "解法"

    先证明下标奇偶性。设当前被消去的两个元素来自原序列中的位置 $x<y$。它们在当前序列中相邻，说明原来位于二者之间的 $y-x-1$ 个元素已经全部被成对消去。因此 $y-x-1$ 为偶数，$x,y$ 的奇偶性相反。

    被消去的两个元素数值相同、下标奇偶性相反，所以对应的 $s_x,s_y$ 互为相反数。每次消除都不会改变区间内 $s_i$ 的总和。

    再考虑最终剩余序列中相邻的两个元素。二者之间的原序列元素同样已经全部被成对消去，所以它们的原下标奇偶性相反；而最终序列不存在相邻且相同的元素，所以它们的数值也相反。数值与下标奇偶性同时改变以后，“二者是否相等”这一关系不变，因此相邻剩余元素对应的 $s_i$ 相同。由此，全部剩余元素对应的 $s_i$ 均同号。

    消除前后 $s_i$ 的总和不变，而消除结束后每一项都等于 $1$ 或都等于 $-1$，故剩余长度恰好等于这个总和的绝对值：

    $$
    \left|\operatorname{red}(a_l,\ldots,a_r)\right|
    =
    \left|P_r-P_{l-1}\right|.
    $$

    枚举分割点即可做到 $\mathcal{O}(qn)$。

## 正解

???+ note "题目描述"

    需要对一个询问中的全部分割点同时求和。

??? tip "Hint"

    对询问 $[l,r]$，记

    $$
    A=P_{l-1},\qquad B=P_r,\qquad X=P_m.
    $$

    把分割点 $m$ 的贡献写成关于 $A,B,X$ 的绝对值表达式。

??? success "公式"

    还需要说明分段消除不会改变最终结果。对任意两个序列 $U,V$，先处理 $U$ 后，栈中恰好留下 $\operatorname{red}(U)$；继续把 $V$ 依次送入同一个栈，与把 $U\circ V$ 从头送入栈完全相同。因此

    $$
    \operatorname{red}\left(
    \operatorname{red}(U)\circ\operatorname{red}(V)
    \right)
    =
    \operatorname{red}(U\circ V).
    $$

    左右两段消除后的长度分别为 $\lvert X-A\rvert$ 与 $\lvert B-X\rvert$，拼接并继续消除后的长度因而等于整个区间的消除长度 $\lvert B-A\rvert$。每次新消除恰好删去两个元素，所以

    $$
    f(m)
    =
    \dfrac{
    \lvert X-A\rvert+\lvert B-X\rvert-\lvert B-A\rvert
    }{2}.
    $$

    定义

    $$
    G(L,R,x)=\sum_{i=L}^{R}\lvert P_i-x\rvert.
    $$

    对 $l\leq m<r$ 求和，得到

    $$
    \operatorname{Ans}(l,r)
    =
    \dfrac{
    G(l,r-1,P_{l-1})+G(l,r-1,P_r)
    -(r-l)\lvert P_r-P_{l-1}\rvert
    }{2}.
    $$

??? success "离线计算"

    每个原询问被拆成两个形如 $G(L,R,x)$ 的离线询问。

    将位置 $i$ 按照 $P_i$ 从小到大排序，将全部离线询问按照 $x$ 从小到大排序。扫描询问时，把所有满足 $P_i\leq x$ 的位置加入数据结构。使用两棵树状数组，分别维护这些位置的数量与 $P_i$ 之和。

    记区间内 $P_i\leq x$ 的数量与和为 $C_{\leq},S_{\leq}$，全部元素的数量与和为 $C,S$，则

    $$
    \begin{aligned}
    G(L,R,x)
    ={}&xC_{\leq}-S_{\leq}\\
    &+(S-S_{\leq})-x(C-C_{\leq}).
    \end{aligned}
    $$

    前两项统计不大于 $x$ 的部分，后两项统计大于 $x$ 的部分。全部元素的和 $S$ 可以由 $P_i$ 的普通前缀和求出。

??? abstract "复杂度分析"

    单组测试数据的时间复杂度为 $\mathcal{O}((n+q)\log n)$，空间复杂度为 $\mathcal{O}(n+q)$。

## 参考代码

[query.cpp](/Blog/assets/solution/noip-mock/test1/std/query.cpp)
