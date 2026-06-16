# 线性空间与线性映射

## 线性空间

???+ note "定义"

    线性空间是依赖数域 $\mathbb{K}$ 定义的集合 $V$。集合中的元素对加法、数乘封闭，并且满足加法与数乘的通常运算法则。

    对 OI 中常见的应用来说，可以先把线性空间理解为：其中的对象可以相加，也可以乘上一个数，并且这些操作不会跑出原集合。

??? note "例子"

    $\mathbb{R}^n$ 是 $\mathbb{R}$ 上的线性空间。两个向量相加仍然是 $\mathbb{R}^n$ 中的向量，一个向量乘上实数后仍然是 $\mathbb{R}^n$ 中的向量。

    多项式集合在次数不超过某个上界时，也可以看成线性空间。例如次数不超过 $n$ 的多项式集合，对加法和数乘封闭。

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

??? note "映射之间的运算"

    我们通常研究 $V\to V$ 的线性映射。对于定义在 $V$ 上的两个线性映射 $\boldsymbol{\varphi},\boldsymbol{\psi}$，可以定义复合：

    $$
    \boldsymbol{\varphi}\boldsymbol{\psi}(\boldsymbol{\alpha})
    =
    \boldsymbol{\varphi}(\boldsymbol{\psi}(\boldsymbol{\alpha}))
    $$

    映射复合通常不可交换。

    也可以定义加法和数乘：

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

    因此：

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

    此时 $\boldsymbol{\varphi}$ 称为可逆映射。可逆映射必然是双射，也称为自同构。

??? note "幂与复合"

    对定义在线性空间 $V$ 上的线性映射 $\boldsymbol{\varphi}$，有：

    $$
    \boldsymbol{\varphi}^{n}\circ\boldsymbol{\varphi}^{m}
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

    一次函数直接看并不是线性映射，因为 $f_i(0)=b_i$ 不一定等于 $0$。但是可以把 $x$ 放到齐次坐标中：

    $$
    \begin{pmatrix}
    x\\1
    \end{pmatrix}
    $$

??? success "解法"

    对一次函数 $f_i(x)=k_ix+b_i$，构造矩阵：

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

    因此一次函数复合可以转化为矩阵乘法：

    $$
    f_r f_{r-1}\cdots f_l(x)
    \Longleftrightarrow
    \boldsymbol{F}_r\boldsymbol{F}_{r-1}\cdots\boldsymbol{F}_l
    \begin{pmatrix}
    x\\1
    \end{pmatrix}
    $$

    由于矩阵乘法满足结合律，所以可以用线段树维护区间矩阵乘积。查询区间 $[l,r]$ 时取出矩阵积，再作用到 $\begin{pmatrix}x\\1\end{pmatrix}$ 上即可。

??? abstract "复杂度分析"

    若矩阵大小固定为 $2\times2$，线段树单次合并可以视为 $\mathcal{O}(1)$。

    建树复杂度为 $\mathcal{O}(n)$，单次询问复杂度为 $\mathcal{O}(\log n)$，空间复杂度为 $\mathcal{O}(n)$。
