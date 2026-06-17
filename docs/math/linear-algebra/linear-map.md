# 线性空间与线性映射

## 线性空间

???+ note "定义"

    线性空间是依赖数域 $\mathbb{K}$ 定义的集合 $V$，满足集合中元素对于加法、数乘封闭，且数乘对于加法有分配律。

    简单地说，若 $\boldsymbol{\alpha},\boldsymbol{\beta}\in V$，$k,l\in\mathbb{K}$，那么应当有：

    $$
    k\boldsymbol{\alpha}+l\boldsymbol{\beta}\in V
    $$

    这就是我们能够在线性空间中讨论线性组合的基础。

??? note "例子"

    $\mathbb{K}^n$ 是 $\mathbb{K}$ 上的线性空间。

    次数不超过 $n$ 的多项式集合也是一个线性空间。因为两个次数不超过 $n$ 的多项式相加，或者乘上一个数，次数仍然不会超过 $n$。

## 基与坐标

???+ note "定义"

    对于线性空间 $V$，其可以视为一个包含了无限个向量的向量组，于是自然可以尝试选取其的极大无关组。

    对于线性空间 $V$，其的一个极大无关组：

    $$
    \{\boldsymbol{e}_1,\boldsymbol{e}_2,\ldots,\boldsymbol{e}_n\}
    $$

    称为线性空间 $V$ 的一组基。

    极大无关组中向量的个数 $n$ 称为线性空间的维数，记作：

    $$
    \operatorname{dim}V=n
    $$

??? note "坐标向量"

    若 $V$ 是 $n$ 维线性空间，取定一组基：

    $$
    \{\boldsymbol{e}_1,\boldsymbol{e}_2,\ldots,\boldsymbol{e}_n\}
    $$

    那么对于任意 $\boldsymbol{\alpha}\in V$，存在唯一的一组数 $k_1,k_2,\ldots,k_n$，使得：

    $$
    \boldsymbol{\alpha}
    =
    k_1\boldsymbol{e}_1+k_2\boldsymbol{e}_2+\cdots+k_n\boldsymbol{e}_n
    $$

    此时称：

    $$
    \boldsymbol{x}
    =
    (k_1,k_2,\ldots,k_n)^T
    $$

    为 $\boldsymbol{\alpha}$ 在这组基下的坐标向量。

??? note "基的判定"

    对 $n$ 维线性空间 $V$，向量组 $\{\boldsymbol{e}_1,\boldsymbol{e}_2,\ldots,\boldsymbol{e}_n\}$ 是 $V$ 的一组基，等价于它线性无关，也等价于任意 $\boldsymbol{\alpha}\in V$ 都能被这组向量线性表示。

    这个结论的意义在于：只要取定了一组基，线性空间中的元素就可以用一个普通向量来表示。

## 线性映射

???+ note "定义"

    对于线性空间 $U,V$，定义线性映射：

    $$
    \begin{aligned}
    \boldsymbol{\varphi}\colon U&\longrightarrow V\\
    \boldsymbol{\alpha}&\longmapsto\boldsymbol{\beta}
    \end{aligned}
    $$

    也就是说，$\boldsymbol{\varphi}(\boldsymbol{\alpha})=\boldsymbol{\beta}$。

    若该映射满足：

    $$
    \boldsymbol{\varphi}(k\boldsymbol{\alpha}+l\boldsymbol{\beta})
    =
    k\boldsymbol{\varphi}(\boldsymbol{\alpha})
    +
    l\boldsymbol{\varphi}(\boldsymbol{\beta})
    $$

    则称 $\boldsymbol{\varphi}$ 是线性映射。

??? note "线性映射之间的运算"

    我们一般研究 $V\to V$ 的线性映射。

    对于两个定义在 $V$ 上的线性映射 $\boldsymbol{\varphi},\boldsymbol{\psi}$，可以定义复合：

    $$
    \boldsymbol{\varphi}\boldsymbol{\psi}(\boldsymbol{\alpha})
    =
    \boldsymbol{\varphi}(\boldsymbol{\psi}(\boldsymbol{\alpha}))
    $$

    映射复合通常不可交换。

    同时可以定义：

    $$
    (\boldsymbol{\varphi}+\boldsymbol{\psi})(\boldsymbol{\alpha})
    =
    \boldsymbol{\varphi}(\boldsymbol{\alpha})
    +
    \boldsymbol{\psi}(\boldsymbol{\alpha})
    $$

    $$
    (k\boldsymbol{\varphi})(\boldsymbol{\alpha})
    =
    k\boldsymbol{\varphi}(\boldsymbol{\alpha})
    $$

    于是有：

    $$
    (k\boldsymbol{\varphi}+l\boldsymbol{\psi})(\boldsymbol{\alpha})
    =
    k\boldsymbol{\varphi}(\boldsymbol{\alpha})
    +
    l\boldsymbol{\psi}(\boldsymbol{\alpha})
    $$

??? note "恒等映射与逆映射"

    定义恒等映射：

    $$
    \boldsymbol{I}_{V}(\boldsymbol{\alpha})=\boldsymbol{\alpha}
    $$

    若对于 $\boldsymbol{\varphi}$，存在线性映射 $\boldsymbol{\xi}$ 满足：

    $$
    \boldsymbol{\xi}\boldsymbol{\varphi}=\boldsymbol{I}_{V}
    $$

    则称 $\boldsymbol{\xi}$ 为 $\boldsymbol{\varphi}$ 的逆映射，记作 $\boldsymbol{\varphi}^{-1}$。

    此时 $\boldsymbol{\varphi}$ 称为可逆映射。显然可逆映射是一个双射，于是也称为自同构。

??? note "幂与复合"

    对定义在线性空间 $V$ 上的线性映射 $\boldsymbol{\varphi}$，有：

    $$
    \boldsymbol{\varphi}^n\circ\boldsymbol{\varphi}^m
    =
    \boldsymbol{\varphi}^{n+m}
    $$

    若 $\boldsymbol{\varphi}$ 可逆，则：

    $$
    \boldsymbol{\varphi}^{-1}\circ\boldsymbol{\varphi}
    =
    \boldsymbol{\varphi}\circ\boldsymbol{\varphi}^{-1}
    =
    \boldsymbol{I}_{V}
    $$

## 表示矩阵

???+ note "定义"

    已知 $n$ 维线性空间 $V$，取定一组基：

    $$
    \{\boldsymbol{e}_1,\boldsymbol{e}_2,\ldots,\boldsymbol{e}_n\}
    $$

    对定义在 $V$ 上的线性映射 $\boldsymbol{\varphi}$，由于 $\boldsymbol{\varphi}(\boldsymbol{e}_i)\in V$，所以每个 $\boldsymbol{\varphi}(\boldsymbol{e}_i)$ 都可以由这组基线性表示。

    设：

    $$
    \left\{
    \begin{aligned}
    \boldsymbol{\varphi}(\boldsymbol{e}_1)
    &=a_{11}\boldsymbol{e}_1+a_{12}\boldsymbol{e}_2+\cdots+a_{1n}\boldsymbol{e}_n\\
    \boldsymbol{\varphi}(\boldsymbol{e}_2)
    &=a_{21}\boldsymbol{e}_1+a_{22}\boldsymbol{e}_2+\cdots+a_{2n}\boldsymbol{e}_n\\
    &\vdots\\
    \boldsymbol{\varphi}(\boldsymbol{e}_n)
    &=a_{n1}\boldsymbol{e}_1+a_{n2}\boldsymbol{e}_2+\cdots+a_{nn}\boldsymbol{e}_n
    \end{aligned}
    \right.
    $$

    令 $\boldsymbol{A}=(a_{ij})$，则称 $\boldsymbol{A}^{T}$ 为 $\boldsymbol{\varphi}$ 在这组基下的表示矩阵。

    这里取转置，是因为坐标向量默认写成列向量。

??? success "坐标向量的转化"

    设 $\boldsymbol{\alpha}\in V$，其坐标向量为 $\boldsymbol{x}$。记：

    $$
    \boldsymbol{\beta}=\boldsymbol{\varphi}(\boldsymbol{\alpha})
    $$

    设 $\boldsymbol{\beta}$ 的坐标向量为 $\boldsymbol{y}$，$\boldsymbol{\varphi}$ 的表示矩阵为 $\boldsymbol{M}$，则有：

    $$
    \boldsymbol{y}=\boldsymbol{M}\boldsymbol{x}
    $$

    也就是说，在线性空间中处理线性映射，取定基以后就可以转化成普通的矩阵乘向量。

??? note "复合映射"

    对若干个线性映射 $\boldsymbol{\varphi}_1,\boldsymbol{\varphi}_2,\ldots,\boldsymbol{\varphi}_m$，设对应表示矩阵分别为 $\boldsymbol{M}_1,\boldsymbol{M}_2,\ldots,\boldsymbol{M}_m$。

    若：

    $$
    \boldsymbol{\beta}
    =
    (\boldsymbol{\varphi}_m\boldsymbol{\varphi}_{m-1}\cdots\boldsymbol{\varphi}_1)(\boldsymbol{\alpha})
    $$

    且 $\boldsymbol{\alpha},\boldsymbol{\beta}$ 的坐标向量分别为 $\boldsymbol{x},\boldsymbol{y}$，则：

    $$
    \boldsymbol{y}
    =
    \boldsymbol{M}_m\boldsymbol{M}_{m-1}\cdots\boldsymbol{M}_1\boldsymbol{x}
    $$

    可以发现，复合映射的顺序会原样反映在矩阵乘积的顺序上。

## 例子：一次函数复合

???+ note "题目描述"

    给定长度为 $n$ 的函数序列，第 $i$ 个函数是一个一次函数：

    $$
    f_i(x)=k_ix+b_i
    $$

    $m$ 次询问，每次给定 $l,r,x$，求 $x$ 按顺序经过 $f_l,f_{l+1},\ldots,f_r$ 后的值，也就是：

    $$
    f_r f_{r-1}\cdots f_l(x)
    $$

??? tip "Hint"

    一个难点是，$f_i(x)=k_ix+b_i$ 本身不是实数域上的线性映射，因为 $f_i(0)=b_i$ 不一定为 $0$。

    但是若干个一次函数复合后仍然是一次函数。因此可以考虑扩大维护对象，使常数项也成为状态的一部分。

??? success "从表示矩阵理解"

    考虑次数不超过 $1$ 的多项式线性空间 $V$，取定一组基 $\{1,x\}$。

    对任意 $\boldsymbol{\alpha}=ax+b$，其坐标向量为：

    $$
    \boldsymbol{x}
    =
    (b,a)^T
    $$

    定义映射 $\boldsymbol{\varphi}_i$：

    $$
    \boldsymbol{\varphi}_i(x)=k_ix+b_i,\quad
    \boldsymbol{\varphi}_i(1)=1
    $$

    则 $\boldsymbol{\varphi}_i$ 在基 $\{1,x\}$ 下的表示矩阵为：

    $$
    \boldsymbol{M}_i=
    \begin{pmatrix}
    1&b_i\\
    0&k_i
    \end{pmatrix}
    $$

    若维护出一段复合对应的表示矩阵：

    $$
    \boldsymbol{M}=
    \begin{pmatrix}
    a&b\\
    0&c
    \end{pmatrix}
    $$

    而 $x$ 在基 $\{1,x\}$ 下的坐标向量是 $(0,1)^T$，则复合后的坐标向量为：

    $$
    \boldsymbol{M}
    \begin{pmatrix}
    0\\1
    \end{pmatrix}
    =
    \begin{pmatrix}
    b\\c
    \end{pmatrix}
    $$

    因此最终得到的一次函数就是 $cx+b$。

??? success "更直接的齐次坐标"

    实际实现时，也可以采用更直接的齐次坐标。把当前值 $x$ 扩成：

    $$
    \begin{pmatrix}
    x\\1
    \end{pmatrix}
    $$

    对于一次函数 $f_i(x)=k_ix+b_i$，构造矩阵：

    $$
    \boldsymbol{F}_i=
    \begin{pmatrix}
    k_i&b_i\\
    0&1
    \end{pmatrix}
    $$

    则有：

    $$
    \boldsymbol{F}_i
    \begin{pmatrix}
    x\\1
    \end{pmatrix}
    =
    \begin{pmatrix}
    k_ix+b_i\\1
    \end{pmatrix}
    $$

    这里额外加入的第二维 $1$，本质上就是为了给平移项 $b_i$ 留出位置。

??? success "线段树维护"

    现在考虑如何维护区间复合。

    令区间 $[l,r]$ 的矩阵为：

    $$
    \boldsymbol{F}_{l,r}
    =
    \boldsymbol{F}_r\boldsymbol{F}_{r-1}\cdots\boldsymbol{F}_l
    $$

    那么询问 $[l,r]$ 时，答案就是：

    $$
    \boldsymbol{F}_{l,r}
    \begin{pmatrix}
    x\\1
    \end{pmatrix}
    $$

    的第一维。

    用线段树维护时，叶子 $i$ 存 $\boldsymbol{F}_i$。若当前节点对应区间 $[L,R]$，左儿子对应 $[L,mid]$，右儿子对应 $[mid+1,R]$，则：

    $$
    \boldsymbol{F}_{L,R}
    =
    \boldsymbol{F}_{mid+1,R}\boldsymbol{F}_{L,mid}
    $$

    也就是说，合并时应当是右儿子的矩阵乘左儿子的矩阵。原因是题目要求先经过左半区间的函数，再经过右半区间的函数。

    若支持修改某一个 $f_i$，只需要在线段树上单点修改对应叶子，然后沿途重新合并即可。

??? abstract "复杂度分析"

    由于矩阵大小固定为 $2\times2$，一次矩阵乘法可以视为 $\mathcal{O}(1)$。

    建树复杂度为 $\mathcal{O}(n)$，单次询问复杂度为 $\mathcal{O}(\log n)$，单点修改复杂度为 $\mathcal{O}(\log n)$，空间复杂度为 $\mathcal{O}(n)$。

## 结语

表示矩阵的意义在于，把抽象的线性映射转化成可以直接计算的矩阵乘法。

在算法题中，如果一个递推或变换能够写成线性映射，或者能通过增加维度改写成线性映射，那么就可以尝试用矩阵乘积维护复合关系。在线段树上维护矩阵乘积之后，就可以同时处理区间查询与单点修改。
