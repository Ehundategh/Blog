# 容斥原理

容斥原理对于大家并不陌生。最经典的结论是，对于两个集合 $A,B$，有：

$$
\lvert A\cup B\rvert=\lvert A\rvert+\lvert B\rvert-\lvert A\cap B\rvert
$$

与这个结论对应的现实应用就是：班上有 $x$ 人喜欢语文，$y$ 人喜欢数学，$z$ 人同时喜欢语文和数学，那么至少喜欢其中一科的人数就是 $x+y-z$。

当然前面提到的部分太局限了，我们要做的是将其推广到一般形式。

## 定理

取集合 $U$，$U$ 中元素有 $n$ 种不同属性 $P_1\sim P_n$，拥有 $P_i$ 属性的元素构成的集合记为 $S_i$，则有：

$$
\left\lvert\bigcup_{i=1}^n S_i\right\rvert
=
\sum_{k=1}^n(-1)^{k-1}
\sum_{1\le a_1<a_2<\cdots<a_k\le n}
\left\lvert\bigcap_{i=1}^k S_{a_i}\right\rvert
$$

??? proof "按元素贡献证明"

    现在考虑证明上述式子。只需要验证每个在并集中的元素都在右侧式子中出现且仅出现一次即可。

    对于任意一个元素 $a$，不妨设其拥有属性 $P_1\sim P_r$，那么其在右式中出现的次数为：

    $$
    \binom r1-\binom r2+\binom r3-\cdots+(-1)^{r-1}\binom rr
    $$

    由二项式定理：

    $$
    (x+y)^n=\sum_{i=0}^n\binom ni x^iy^{n-i}
    $$

    将其中取 $x=-1,y=1,n=r$，可以得到：

    $$
    \binom r0-\binom r1+\binom r2-\cdots+(-1)^r\binom rr=0
    $$

    因此：

    $$
    \binom r1-\binom r2+\cdots+(-1)^{r-1}\binom rr=\binom r0=1
    $$

    这说明元素 $a$ 在右侧式子中出现过恰好一次，原式得证。

??? proof "数学归纳法证明"

    也可以换一个角度来证明上述式子。

    当 $n=2$ 时，原式显然成立。

    假设对于 $n=m-1(m\ge 3)$ 时成立，那么 $n=m$ 时，有：

    $$
    \bigcup_{i=1}^m S_i=\left(\bigcup_{i=1}^{m-1}S_i\right)\cup S_m
    $$

    于是：

    $$
    \left\lvert\bigcup_{i=1}^m S_i\right\rvert
    =
    \left\lvert\bigcup_{i=1}^{m-1}S_i\right\rvert
    +\lvert S_m\rvert
    -
    \left\lvert\left(\bigcup_{i=1}^{m-1}S_i\right)\cap S_m\right\rvert
    \quad (*)
    $$

    又有：

    $$
    \left(\bigcup_{i=1}^{m-1}S_i\right)\cap S_m
    =
    \bigcup_{i=1}^{m-1}(S_i\cap S_m)
    $$

    对右式使用归纳假设，即可得到：

    $$
    \left\lvert\bigcup_{i=1}^{m-1}(S_i\cap S_m)\right\rvert
    =
    \sum_{k=1}^{m-1}(-1)^{k-1}
    \sum_{1\le a_1<\cdots<a_k\le m-1}
    \left\lvert
    \left(\bigcap_{i=1}^k S_{a_i}\right)\cap S_m
    \right\rvert
    \quad(\dagger)
    $$

    将 $(\dagger)$ 式代入 $(*)$ 式，即知若 $n=m-1$ 成立，则 $n=m$ 时也成立。

## 补集转化

容斥原理可以将并集的势转化为交集的势来计算。但是如果遇到交集的势难以处理的情况呢？

这种情况下，一般采用取补集的方式，用全集减去补集的并集就是我们要求的交集：

$$
\left\lvert\bigcap_{i=1}^n S_i\right\rvert
=
\lvert U\rvert-\left\lvert\bigcup_{i=1}^n\overline{S_i}\right\rvert
$$

但是注意，当我们打算正难则反用补集求解时，要巧妙定义全集，并且全集必须是有限集，才能够计算出结果。

## 完全图子图染色

???+ note "题目描述"

    对于 $n$ 阶完全图 $G=(V,E)$，定义一个估价函数 $F(S)$，其中 $S$ 是边集，$S\subseteq E$。

    $F(S)$ 的值是对图 $G'=(V,S)$ 用 $m$ 种颜色染色的总方案数，且要求相邻节点必须染同一种颜色。

    如果 $\lvert S\rvert$ 是奇数，那么 A 的得分增加 $F(S)$；否则 B 的得分增加 $F(S)$。求 A 和 B 的得分差值。

??? tip "Hint"

    根据定义，可以写出：

    $$
    Ans=\sum_{S\subseteq E}(-1)^{|S|-1}F(S)
    $$

    这个式子很像容斥原理，但 $F(S)$ 不是集合交集的模的形式，所以考虑构造集合。

??? success "解法"

    定义集合 $Q_{i,j}$ 是所有使 $i,j$ 同色的染色方案构成的集合。全集 $U$ 就是所有染色方案集合。

    由于 $S$ 对应的染色方案中要求相邻节点颜色相同，记对 $S$ 合法的染色方案构成的集合为 $R(S)$，那么必然有：

    $$
    R(S)\subseteq\bigcap_{(i,j)\in S}Q_{i,j}
    $$

    同时，根据定义反向包含也成立，所以：

    $$
    R(S)=\bigcap_{(i,j)\in S}Q_{i,j}
    $$

    又因为 $F(S)=|R(S)|$，从而：

    $$
    Ans=\sum_{S\subseteq E}(-1)^{|S|-1}
    \left|\bigcap_{(i,j)\in S}Q_{i,j}\right|
    $$

    直接应用容斥原理，看起来可以得到 $Ans$ 等于存在两个同色节点的方案数。由正难则反，补集为所有节点颜色均不同，于是似乎有：

    $$
    Ans=m^n-A_m^n
    $$

    但这样并不完全正确。标准容斥中求和应从 $S\ne\emptyset$ 开始，而原式中包含了 $S=\emptyset$ 的项。

    实际上：

    $$
    \left|\bigcup_{(i,j)\in E}Q_{i,j}\right|
    =
    \sum_{\substack{S\subseteq E\\S\ne\emptyset}}(-1)^{|S|-1}
    \left|\bigcap_{(i,j)\in S}Q_{i,j}\right|
    $$

    对比原式可知：

    $$
    \left|\bigcup_{(i,j)\in E}Q_{i,j}\right|=Ans+|U|
    $$

    因此：

    $$
    Ans=m^n-A_m^n-m^n=-A_m^n
    $$

??? abstract "复杂度分析"

    直接由公式计算即可。若需要实际计算排列数，时间复杂度为 $\mathcal{O}(n)$。

## 多重集的组合数

???+ note "题目描述"

    定义多重集合 $S=\{n_1a_1,n_2a_2,\cdots,n_ka_k\}$ 为由 $n_i$ 个 $a_i$ 组成的可重集合，记 $n=\sum_{i=1}^k n_i$。

    求从 $S$ 中选出 $r$ 个元素组成一个新的多重集的方案数。

??? tip "Hint"

    显然这个问题等价于 $x_1+x_2+\cdots+x_k=r$ 的非负整数解个数，并且每个 $x_i$ 有上界 $n_i$。

??? success "解法"

    若 $r\le\min\{n_i\}$，那么可以直接使用插板法，答案为：

    $$
    \binom{r+k-1}{k-1}
    $$

    一般情况下，每个 $x_i$ 有上限。令全集 $U$ 为原方程的非负整数解构成的集合，令 $S_i$ 是满足 $x_i\le n_i$ 的非负整数解构成的集合，$\overline{S_i}$ 是 $S_i$ 的补集。

    那么要求的是：

    $$
    \left|\bigcap_{i=1}^kS_i\right|
    =
    |U|-\left|\bigcup_{i=1}^k\overline{S_i}\right|
    $$

    对右侧并集使用容斥原理。对于一组被钦定超过上限的变量集合 $T$，令每个 $i\in T$ 的 $x_i'=x_i-(n_i+1)$，即可继续用插板法处理。

    因此答案可以写成：

    $$
    \sum_{T\subseteq \{1,\cdots,k\}}
    (-1)^{|T|}
    \binom{r-\sum_{i\in T}(n_i+1)+k-1}{k-1}
    $$

    其中若上式组合数上标小于下标，则视为 $0$。

??? abstract "复杂度分析"

    若直接枚举所有子集，时间复杂度为 $\mathcal{O}(2^k)$。

## 洛谷 P1450

???+ note "题目描述"

    [洛谷 P1450](https://www.luogu.com.cn/problem/P1450)：给定四种面值分别为 $c_1,c_2,c_3,c_4$ 的硬币。

    小 A 进行了 $n$ 次购物，每次购物带了 $d_i$ 枚第 $i$ 种硬币，并想买价值为 $s$ 的东西。请输出每次购买的付款方式数量。

??? tip "Hint"

    题目等价于求：

    $$
    \sum_{i=1}^4x_ic_i=s,\quad x_i\le d_i
    $$

    的非负整数解个数。

??? success "解法"

    直接用多重背包做复杂度较高。根据多重集组合数的处理方式，令 $S_i$ 是满足 $x_i\le d_i$ 的非负整数解构成的集合，则：

    $$
    \left|\bigcap_{i=1}^4S_i\right|
    =
    |U|-\left|\bigcup_{i=1}^4\overline{S_i}\right|
    $$

    把并集用容斥原理拆开。对于每一项，若钦定若干个 $x_i>d_i$，则令 $x_i'=x_i-(d_i+1)$，原式右侧的 $s$ 会减少对应的 $(d_i+1)c_i$。

    因此只需要先对无限制硬币数量的完全背包做预处理，得到凑出每个 $s$ 的方案数。每次询问枚举 $2^4$ 个集合，直接容斥即可。

??? abstract "复杂度分析"

    预处理完全背包复杂度为 $\mathcal{O}(S)$。每次询问枚举 $16$ 个子集，复杂度为 $\mathcal{O}(1)$。总复杂度为 $\mathcal{O}(S+n)$。

## 洛谷 P1447

???+ note "题目描述"

    [洛谷 P1447](https://www.luogu.com.cn/problem/P1447)：在平面直角坐标系的第一象限中，规定 $n,m$ 分别作为 $\sup x,\sup y$。

    记整点 $(x,y)$ 与 $(0,0)$ 连线内部有 $k$ 个点，那么这个整点 $(x,y)$ 对答案的贡献就是 $2k+1$。求最终答案。

??? tip "Hint"

    对于给定的 $(x,y)$，其与 $(0,0)$ 连线内部的点的个数是 $\gcd(x,y)-1$。

??? success "解法"

    题目可以转化为求：

    $$
    Ans=\sum_{i=1}^n\sum_{j=1}^m(2\gcd(i,j)-1)
    $$

    直接暴力求和复杂度为 $\mathcal{O}(nm)$，肯定会超时。考虑统计每个 $\gcd$ 的个数。

    记满足 $\gcd(x,y)=k$ 的有序数对 $(x,y)$ 的对数为 $f(k)$。记满足 $k\mid x,k\mid y$ 的有序数对 $(x,y)$ 对数为 $\psi(k)$，那么根据容斥原理，有：

    $$
    f(k)=\psi(k)-\sum_{i=2}f(ki)
    $$

    又由乘法原理：

    $$
    \psi(k)=\left\lfloor\dfrac{n}{k}\right\rfloor\left\lfloor\dfrac{m}{k}\right\rfloor
    $$

    于是：

    $$
    f(k)=\left\lfloor\dfrac{n}{k}\right\rfloor\left\lfloor\dfrac{m}{k}\right\rfloor-\sum_{i=2}f(ki)
    $$

    令 $r=\min(n,m)$，倒着递推即可求出所有 $f(k)$。

??? abstract "复杂度分析"

    枚举所有倍数求和，复杂度为 $\mathcal{O}(r\log r)$。

## 容斥反演

定义两个集合上的函数 $f,g$，满足：

$$
f(S)=\sum_{T\subseteq S}g(T)
$$

则有：

$$
g(S)=\sum_{T\subseteq S}(-1)^{|S|-|T|}f(T)
$$

??? proof "证明"

    对右式做变化，结合已知条件，有：

    $$
    \sum_{T\subseteq S}(-1)^{|S|-|T|}f(T)
    =
    \sum_{T\subseteq S}(-1)^{|S|-|T|}
    \sum_{Q\subseteq T}g(Q)
    $$

    交换求和顺序，有：

    $$
    =
    \sum_Q g(Q)\sum_{Q\subseteq T\subseteq S}(-1)^{|S|-|T|}
    $$

    令 $P=S-Q$，则内层求和为：

    $$
    \sum_{T\subseteq P}(-1)^{|P|-|T|}
    =
    \sum_{i=0}^{|P|}\binom{|P|}{i}(-1)^{|P|-i}
    =
    (1+(-1))^{|P|}
    $$

    只有当 $P=\emptyset$，也就是 $Q=S$ 时，上式才不为 $0$。因此最终只剩下 $g(S)$。

## min-max 容斥

给定全序的长度为 $n$ 的序列 $\{x_i\}$，令 $S=\{1,2,\cdots,n\}$，成立：

$$
\max_{i\in S}x_i=
\sum_{T\subseteq S}(-1)^{|T|-1}\min_{j\in T}x_j
$$

$$
\min_{i\in S}x_i=
\sum_{T\subseteq S}(-1)^{|T|-1}\max_{j\in T}x_j
$$

??? proof "证明"

    这里只证明第一个式子。

    将 $x$ 按升序排序，$\operatorname{rank}(x)$ 为 $x$ 的排名函数。定义映射：

    $$
    f(x)=\{1,2,\cdots,\operatorname{rank}(x)\}
    $$

    根据定义，成立：

    $$
    f(\min(x,y))=f(x)\cap f(y),\quad f(\max(x,y))=f(x)\cup f(y)
    $$

    于是结合容斥原理可以得到：

    $$
    \left|f\left(\max_{i\in S}x_i\right)\right|
    =
    \left|\bigcup_{i\in S}f(x_i)\right|
    $$

    $$
    =
    \sum_{T\subseteq S}(-1)^{|T|-1}
    \left|\bigcap_{j\in T}f(x_j)\right|
    =
    \sum_{T\subseteq S}(-1)^{|T|-1}
    \left|f\left(\min_{j\in T}x_j\right)\right|
    $$

    由于 $f$ 按排名保持顺序，上式对应回原序列，即得结论。

若 $\{X_i\}$ 是随机变量，且每个 $X_i$ 的数学期望均存在，则由数学期望的线性性，有：

$$
E\left(\max_{i\in S}X_i\right)
=
\sum_{T\subseteq S}(-1)^{|T|-1}E\left(\min_{j\in T}X_j\right)
$$

$$
E\left(\min_{i\in S}X_i\right)
=
\sum_{T\subseteq S}(-1)^{|T|-1}E\left(\max_{j\in T}X_j\right)
$$
