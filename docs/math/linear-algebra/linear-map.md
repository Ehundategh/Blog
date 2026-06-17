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

??? proof "证明"

    若 $\{\boldsymbol{e}_1,\boldsymbol{e}_2,\ldots,\boldsymbol{e}_n\}$ 是一组基，那么它本身就是极大无关组，所以显然线性无关。

    接下来说明任意 $\boldsymbol{\alpha}\in V$ 都能被这组基线性表示。若不能表示，那么把 $\boldsymbol{\alpha}$ 加入这组向量后，仍然线性无关，否则 $\boldsymbol{\alpha}$ 就可以由原向量组表示。这与极大无关组矛盾。

    反过来，若一个 $n$ 个向量的向量组线性无关，由于 $\operatorname{dim}V=n$，它已经达到无关组大小的上界，所以是极大无关组，也就是一组基。

    最后说明表示唯一。若：

    $$
    \boldsymbol{\alpha}
    =
    \sum_{i=1}^{n}k_i\boldsymbol{e}_i
    =
    \sum_{i=1}^{n}l_i\boldsymbol{e}_i
    $$

    两式相减，有：

    $$
    \sum_{i=1}^{n}(k_i-l_i)\boldsymbol{e}_i=\boldsymbol{0}
    $$

    由于这组基线性无关，只能 $k_i-l_i=0$，即 $k_i=l_i$。

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

??? proof "证明"

    第一个式子本质上来自复合的结合律。$\boldsymbol{\varphi}^n$ 表示连续复合 $n$ 次 $\boldsymbol{\varphi}$，$\boldsymbol{\varphi}^m$ 表示连续复合 $m$ 次 $\boldsymbol{\varphi}$，两者再复合就是连续复合 $n+m$ 次，因此：

    $$
    \boldsymbol{\varphi}^n\circ\boldsymbol{\varphi}^m
    =
    \boldsymbol{\varphi}^{n+m}
    $$

    对逆映射，由定义可知 $\boldsymbol{\varphi}^{-1}$ 是能够撤销 $\boldsymbol{\varphi}$ 的映射。因此先做 $\boldsymbol{\varphi}$ 再做 $\boldsymbol{\varphi}^{-1}$，或者先做 $\boldsymbol{\varphi}^{-1}$ 再做 $\boldsymbol{\varphi}$，都会回到原向量，即恒等映射。

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
    &=m_{11}\boldsymbol{e}_1+m_{21}\boldsymbol{e}_2+\cdots+m_{n1}\boldsymbol{e}_n\\
    \boldsymbol{\varphi}(\boldsymbol{e}_2)
    &=m_{12}\boldsymbol{e}_1+m_{22}\boldsymbol{e}_2+\cdots+m_{n2}\boldsymbol{e}_n\\
    &\vdots\\
    \boldsymbol{\varphi}(\boldsymbol{e}_n)
    &=m_{1n}\boldsymbol{e}_1+m_{2n}\boldsymbol{e}_2+\cdots+m_{nn}\boldsymbol{e}_n
    \end{aligned}
    \right.
    $$

    则称：

    $$
    \boldsymbol{M}=(m_{ij})
    $$

    为 $\boldsymbol{\varphi}$ 在这组基下的表示矩阵。

    也就是说，表示矩阵的第 $j$ 列，就是 $\boldsymbol{\varphi}(\boldsymbol{e}_j)$ 在这组基下的坐标向量。这样写的原因是坐标向量默认写成列向量。

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

??? proof "证明"

    设：

    $$
    \boldsymbol{\alpha}
    =
    \sum_{i=1}^{n}x_i\boldsymbol{e}_i
    $$

    根据线性映射的定义，有：

    $$
    \boldsymbol{\varphi}(\boldsymbol{\alpha})
    =
    \sum_{i=1}^{n}x_i\boldsymbol{\varphi}(\boldsymbol{e}_i)
    $$

    而每个 $\boldsymbol{\varphi}(\boldsymbol{e}_i)$ 已经在定义表示矩阵时写成了基的线性组合。把这些式子代入并合并同类项，得到的每个坐标正是矩阵 $\boldsymbol{M}$ 与坐标向量 $\boldsymbol{x}$ 相乘的结果，所以：

    $$
    \boldsymbol{y}=\boldsymbol{M}\boldsymbol{x}
    $$

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

??? proof "证明"

    先考虑两个映射。设 $\boldsymbol{\varphi}_1,\boldsymbol{\varphi}_2$ 的表示矩阵分别为 $\boldsymbol{M}_1,\boldsymbol{M}_2$。

    若 $\boldsymbol{\alpha}$ 的坐标向量为 $\boldsymbol{x}$，则 $\boldsymbol{\varphi}_1(\boldsymbol{\alpha})$ 的坐标向量为：

    $$
    \boldsymbol{M}_1\boldsymbol{x}
    $$

    再作用 $\boldsymbol{\varphi}_2$ 后，坐标向量变为：

    $$
    \boldsymbol{M}_2(\boldsymbol{M}_1\boldsymbol{x})
    =
    \boldsymbol{M}_2\boldsymbol{M}_1\boldsymbol{x}
    $$

    于是 $\boldsymbol{\varphi}_2\boldsymbol{\varphi}_1$ 的表示矩阵就是 $\boldsymbol{M}_2\boldsymbol{M}_1$。多个映射时重复使用这个结论即可。

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

??? success "表示矩阵方式"

    为了把一次函数中的平移项也写进线性映射，我们不直接在一维空间中维护 $x$，而是把状态扩成二维向量：

    $$
    \begin{pmatrix}
    x\\1
    \end{pmatrix}
    $$

    设线性空间为 $\mathbb{K}^2$，取标准基：

    $$
    \boldsymbol{e}_1=
    \begin{pmatrix}
    1\\0
    \end{pmatrix},
    \quad
    \boldsymbol{e}_2=
    \begin{pmatrix}
    0\\1
    \end{pmatrix}
    $$

    对一次函数 $f_i(x)=k_ix+b_i$，定义线性映射 $\boldsymbol{\Phi}_i$：

    $$
    \boldsymbol{\Phi}_i
    \begin{pmatrix}
    u\\v
    \end{pmatrix}
    =
    \begin{pmatrix}
    k_iu+b_iv\\
    v
    \end{pmatrix}
    $$

    那么：

    $$
    \boldsymbol{\Phi}_i(\boldsymbol{e}_1)=
    \begin{pmatrix}
    k_i\\0
    \end{pmatrix},
    \quad
    \boldsymbol{\Phi}_i(\boldsymbol{e}_2)=
    \begin{pmatrix}
    b_i\\1
    \end{pmatrix}
    $$

    因此 $\boldsymbol{\Phi}_i$ 在标准基下的表示矩阵为：

    $$
    \boldsymbol{F}_i=
    \begin{pmatrix}
    k_i&b_i\\
    0&1
    \end{pmatrix}
    $$

    于是：

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

    这就是一次函数 $f_i$ 对状态的作用。

??? warning "一个容易混淆的写法"

    如果考虑多项式空间 $V=\operatorname{span}\{1,x\}$，并定义：

    $$
    \boldsymbol{\psi}_i(1)=1,\quad
    \boldsymbol{\psi}_i(x)=k_ix+b_i
    $$

    那么它的表示矩阵是：

    $$
    \begin{pmatrix}
    1&b_i\\
    0&k_i
    \end{pmatrix}
    $$

    但这个映射对多项式 $p(x)$ 的作用是：

    $$
    p(x)\mapsto p(k_ix+b_i)
    $$

    也就是右复合 $p\circ f_i$。

    题目中“$x$ 按顺序经过 $f_l,\ldots,f_r$”对应的是：

    $$
    f_r\circ f_{r-1}\circ\cdots\circ f_l
    $$

    这是不断左复合。因此这个多项式空间上的写法不能直接拿来当成题目的维护矩阵，除非额外把复合方向重新调整清楚。

??? success "两种视角的相同点"

    现在可以看出，真正用于本题的表示矩阵就是齐次状态上的表示矩阵：

    $$
    \boldsymbol{F}_i=
    \begin{pmatrix}
    k_i&b_i\\
    0&1
    \end{pmatrix}
    $$

    它和一般表示矩阵理论的关系是：我们选定了 $\mathbb{K}^2$ 的标准基，并把一次函数作用在扩展状态 $(x,1)^T$ 上。

    它和“多项式空间 $\{1,x\}$”那种写法的相同点是：都把一次函数相关的操作转化成了矩阵乘法。

    不同点是：齐次状态矩阵维护的是数值状态的左复合转移，正好对应题目顺序；多项式空间中令 $x\mapsto kx+b$ 的表示矩阵维护的是右复合。

??? success "线段树维护"

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

## 例子：斐波那契数列

???+ note "题目描述"

    定义斐波那契数列：

    $$
    F_0=0,\quad F_1=1
    $$

    $$
    F_n=F_{n-1}+F_{n-2}
    $$

    多次询问 $F_n$。

??? tip "Hint"

    递推中每一项只依赖前两项。考虑把相邻两项一起作为状态。

??? success "解法"

    定义状态向量：

    $$
    \boldsymbol{s}_n=
    \begin{pmatrix}
    F_n\\
    F_{n-1}
    \end{pmatrix}
    $$

    根据递推式，有：

    $$
    \begin{pmatrix}
    F_{n+1}\\
    F_n
    \end{pmatrix}
    =
    \begin{pmatrix}
    1&1\\
    1&0
    \end{pmatrix}
    \begin{pmatrix}
    F_n\\
    F_{n-1}
    \end{pmatrix}
    $$

    记：

    $$
    \boldsymbol{T}=
    \begin{pmatrix}
    1&1\\
    1&0
    \end{pmatrix}
    $$

    则：

    $$
    \boldsymbol{s}_n=\boldsymbol{T}^{n-1}\boldsymbol{s}_1
    $$

    其中：

    $$
    \boldsymbol{s}_1=
    \begin{pmatrix}
    1\\0
    \end{pmatrix}
    $$

    所以只需要快速求出 $\boldsymbol{T}^{n-1}$，再取结果向量第一维即可。

??? note "与函数复合的关系"

    斐波那契数列中，每一步都在做同一个线性映射：

    $$
    \boldsymbol{s}\mapsto\boldsymbol{T}\boldsymbol{s}
    $$

    因此求 $F_n$ 本质上就是维护：

    $$
    \underbrace{\boldsymbol{T}\boldsymbol{T}\cdots\boldsymbol{T}}_{n-1\text{ 次}}
    $$

    这和一次函数复合中维护：

    $$
    \boldsymbol{F}_r\boldsymbol{F}_{r-1}\cdots\boldsymbol{F}_l
    $$

    是同一种事情。

    不同点在于，斐波那契的每一步转移矩阵相同，所以通常用矩阵快速幂；一次函数复合中每个位置的矩阵可能不同，所以更自然地用线段树维护区间矩阵积。

??? success "线段树维护的扩展"

    如果每个位置的递推转移不同，例如：

    $$
    a_{i+1}=p_ia_i+q_ia_{i-1}
    $$

    那么可以令：

    $$
    \boldsymbol{T}_i=
    \begin{pmatrix}
    p_i&q_i\\
    1&0
    \end{pmatrix}
    $$

    此时：

    $$
    \begin{pmatrix}
    a_{i+1}\\
    a_i
    \end{pmatrix}
    =
    \boldsymbol{T}_i
    \begin{pmatrix}
    a_i\\
    a_{i-1}
    \end{pmatrix}
    $$

    若要查询从第 $l$ 项状态转移到第 $r$ 项状态，需要维护的矩阵为：

    $$
    \boldsymbol{T}_{r-1}\boldsymbol{T}_{r-2}\cdots\boldsymbol{T}_l
    $$

    在线段树上，叶子 $i$ 存 $\boldsymbol{T}_i$，父亲合并仍然是右儿子矩阵乘左儿子矩阵。这样就可以支持单点修改某个递推系数，并在 $\mathcal{O}(\log n)$ 的时间查询一段递推的结果。

??? abstract "复杂度分析"

    对普通斐波那契数列，矩阵快速幂时间复杂度为 $\mathcal{O}(\log n)$。

    对每个位置转移不同的扩展形式，线段树建树复杂度为 $\mathcal{O}(n)$，单次查询和单点修改复杂度均为 $\mathcal{O}(\log n)$。

## 结语

表示矩阵的意义在于，把抽象的线性映射转化成可以直接计算的矩阵乘法。

在算法题中，如果一个递推或变换能够写成线性映射，或者能通过增加维度改写成线性映射，那么就可以尝试用矩阵乘积维护复合关系。在线段树上维护矩阵乘积之后，就可以同时处理区间查询与单点修改。
