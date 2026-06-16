# 矩阵与线性方程组

## 矩阵

???+ note "定义"

    一个 $n\times m$ 的矩阵 $\boldsymbol{A}$ 由 $n$ 行 $m$ 列共 $n\times m$ 个元素构成，记作：

    $$
    \boldsymbol{A}=
    \begin{pmatrix}
    a_{11}&a_{12}&\cdots&a_{1m}\\
    a_{21}&a_{22}&\cdots&a_{2m}\\
    \vdots&\vdots&\ddots&\vdots\\
    a_{n1}&a_{n2}&\cdots&a_{nm}
    \end{pmatrix}
    $$

    可简记作 $\boldsymbol{A}=(a_{ij})$。若 $n=m$，则称该矩阵为 $n$ 阶方阵。

??? note "矩阵运算"

    给定 $n\times m$ 矩阵 $\boldsymbol{A}=(a_{ij})$ 和 $\boldsymbol{B}=(b_{ij})$，以及 $m\times l$ 矩阵 $\boldsymbol{C}=(c_{ij})$。

    矩阵加法定义为：

    $$
    \boldsymbol{A}+\boldsymbol{B}=(a_{ij}+b_{ij})
    $$

    矩阵数乘定义为：

    $$
    k\boldsymbol{A}=(ka_{ij})
    $$

    矩阵乘法要求左侧矩阵列数等于右侧矩阵行数。令 $\boldsymbol{D}=\boldsymbol{A}\boldsymbol{C}=(d_{ij})$，则：

    $$
    d_{ij}=\sum_{k=1}^{m}a_{ik}c_{kj}
    $$

??? note "行向量、列向量与转置"

    对矩阵 $\boldsymbol{A}=(a_{ij})_{n\times m}$，第 $i$ 个行向量为：

    $$
    \boldsymbol{\alpha}_i=(a_{i1},a_{i2},\ldots,a_{im})
    $$

    第 $j$ 个列向量为：

    $$
    \boldsymbol{\beta}_j^T=(a_{1j},a_{2j},\ldots,a_{nj})^T
    $$

    这里的 $T$ 表示转置，矩阵 $\boldsymbol{A}$ 的转置记作：

    $$
    \boldsymbol{A}^{T}=(a_{ji})_{m\times n}
    $$

## 向量组与秩

???+ note "线性相关与线性无关"

    对于向量组 $A=\{\boldsymbol{\alpha}_1,\boldsymbol{\alpha}_2,\ldots,\boldsymbol{\alpha}_n\}$，考虑方程：

    $$
    k_1\boldsymbol{\alpha}_1+k_2\boldsymbol{\alpha}_2+\cdots+k_n\boldsymbol{\alpha}_n=\boldsymbol{0}
    $$

    如果方程成立当且仅当 $k_1=k_2=\cdots=k_n=0$，则称向量组 $A$ 中所有向量线性无关，否则称其线性相关。

??? note "极大无关组与秩"

    对向量组 $A$ 选出一个子向量组 $A'$。在所有线性无关的子向量组中，向量数量最多的称为向量组 $A$ 的极大无关组。

    向量组 $A$ 的秩定义为其极大无关组的向量个数，记作 $\operatorname{rank}(A)$。

    对矩阵来说，行秩指矩阵所有行向量组成的向量组的秩，列秩同理。矩阵的行秩等于列秩，统称为矩阵的秩，记作 $\operatorname{r}(\boldsymbol{A})$。

## 初等变换

???+ note "定义"

    矩阵的初等变换分为三类：

    - 第一类：对换两行或两列。
    - 第二类：将某一行或某一列乘以一个非零常数。
    - 第三类：将某一行或某一列乘上一个数后加到另一行或另一列上。

    单位矩阵为：

    $$
    \boldsymbol{I}_n=
    \begin{pmatrix}
    1&0&\cdots&0\\
    0&1&\cdots&0\\
    \vdots&\vdots&\ddots&\vdots\\
    0&0&\cdots&1
    \end{pmatrix}
    $$

    对单位矩阵做一次初等变换得到的矩阵称为初等矩阵。每次初等行变换都等价于左乘一个初等矩阵，每次初等列变换都等价于右乘一个初等矩阵。

??? note "行列式"

    对 $n$ 阶方阵 $\boldsymbol{A}=(a_{ij})$，其行列式记作 $|\boldsymbol{A}|$ 或 $\det(\boldsymbol{A})$。

    取第一列展开，有：

    $$
    |\boldsymbol{A}|=
    a_{11}|\boldsymbol{A}_{11}|+
    a_{21}|\boldsymbol{A}_{21}|+\cdots+
    a_{n1}|\boldsymbol{A}_{n1}|
    $$

    其中 $|\boldsymbol{A}_{ij}|=(-1)^{i+j}|\boldsymbol{M}_{ij}|$ 为代数余子式，$|\boldsymbol{M}_{ij}|$ 为去掉第 $i$ 行第 $j$ 列后得到的余子式。

    对一阶方阵，其行列式的值就是唯一元素的值。行列式也可以按任意一行或任意一列展开。

??? note "初等变换对行列式的影响"

    对矩阵做第一类初等变换，行列式的值变为相反数。

    对矩阵做第二类初等变换，行列式的值也乘以对应常数。

    对矩阵做第三类初等变换，行列式的值不变。

??? note "逆阵"

    对于 $n$ 阶方阵 $\boldsymbol{A}$，若存在 $n$ 阶方阵 $\boldsymbol{B}$ 使得：

    $$
    \boldsymbol{A}\boldsymbol{B}
    =
    \boldsymbol{B}\boldsymbol{A}
    =
    \boldsymbol{I}_n
    $$

    则称 $\boldsymbol{B}$ 为 $\boldsymbol{A}$ 的逆阵，记作 $\boldsymbol{A}^{-1}=\boldsymbol{B}$。

    如果一个矩阵有逆阵，那么称其为非异阵，否则称为奇异阵。

??? note "对角阵与三角阵"

    对 $n$ 阶方阵 $\boldsymbol{A}=(a_{ij})$，若其满足 $a_{ij}=0(\forall i\ne j)$，则称其为对角阵，记作：

    $$
    \boldsymbol{A}=\operatorname{diag}\{a_{11},a_{22},\ldots,a_{nn}\}
    $$

    若满足 $a_{ij}=0(\forall i>j)$，则称其为上三角阵。下三角阵同理。

## 线性方程组

???+ note "定义"

    对于 $n$ 个变量的 $m$ 个方程：

    $$
    \left\{
    \begin{aligned}
    a_{11}x_1+a_{12}x_2+\cdots+a_{1n}x_n&=b_1\\
    a_{21}x_1+a_{22}x_2+\cdots+a_{2n}x_n&=b_2\\
    &\vdots\\
    a_{m1}x_1+a_{m2}x_2+\cdots+a_{mn}x_n&=b_m
    \end{aligned}
    \right.
    $$

    可以记为矩阵形式：

    $$
    \boldsymbol{A}\boldsymbol{x}=\boldsymbol{\beta}
    $$

    其中 $\boldsymbol{A}$ 称为系数矩阵，$(\boldsymbol{A}\mid\boldsymbol{\beta})$ 称为增广矩阵。

??? proof "初等行变换不改变解集"

    对 $\boldsymbol{A}\boldsymbol{x}=\boldsymbol{\beta}$ 做一次初等行变换，等价于左乘一个初等矩阵 $\boldsymbol{P}$，得到：

    $$
    \boldsymbol{P}\boldsymbol{A}\boldsymbol{x}
    =
    \boldsymbol{P}\boldsymbol{\beta}
    $$

    由于初等矩阵均为非异阵，$\boldsymbol{P}^{-1}$ 存在。若 $\boldsymbol{x}$ 是原方程的解，则其显然满足新方程；若 $\boldsymbol{x}$ 满足新方程，则左乘 $\boldsymbol{P}^{-1}$ 后又回到原方程。

    因此初等行变换不改变线性方程组的解集。

??? note "有解条件"

    方程组 $\boldsymbol{A}\boldsymbol{x}=\boldsymbol{\beta}$ 有解当且仅当：

    $$
    \operatorname{r}(\boldsymbol{A})
    =
    \operatorname{r}(\boldsymbol{A}\mid\boldsymbol{\beta})
    $$

    若秩不相等，那么化为阶梯形后会出现左侧全为 $0$、右侧非零的矛盾方程，即 $0=c(c\ne0)$。

## 高斯消元

???+ note "行阶梯形矩阵"

    一个矩阵若满足以下条件，则称为行阶梯形矩阵：

    - 所有全零行均位于矩阵底部。
    - 对每个非零行，其第一个非零元素称为主元。
    - 主元所在列从上到下严格右移。

    高斯消元的目标，就是把增广矩阵 $(\boldsymbol{A}\mid\boldsymbol{\beta})$ 化为行阶梯形矩阵。

??? success "前向消元"

    设当前已经处理到第 $r$ 行，接下来从第 $c$ 列开始寻找主元。

    首先在第 $r,r+1,\ldots,m$ 行中寻找一个第 $c$ 列非零的行。如果不存在这样的行，那么说明第 $c$ 列不能提供新的主元，直接考虑下一列。

    若找到了某一行 $p$，则交换第 $p$ 行与第 $r$ 行，使得 $a_{rc}\ne0$。接下来用第 $r$ 行消去其下方所有行的第 $c$ 列。对每个 $i>r$ 且 $a_{ic}\ne0$ 的行，做：

    $$
    R_i\leftarrow R_i-\dfrac{a_{ic}}{a_{rc}}R_r
    $$

    这样第 $i$ 行的第 $c$ 列就会变为 $0$。完成后，$(r,c)$ 位置就是一个主元位置，令 $r\leftarrow r+1$，继续处理下一列。

    这个过程结束后，矩阵已经被化为行阶梯形。

??? success "回代"

    行阶梯形矩阵的好处在于：靠下的主元依赖的未知数更少。

    若某一行化为：

    $$
    0x_1+0x_2+\cdots+0x_n=c
    $$

    且 $c\ne0$，则方程组无解。

    否则，从最后一个主元行开始向上回代。若第 $i$ 行主元在第 $p_i$ 列，则：

    $$
    x_{p_i}
    =
    \dfrac{
    b_i-\sum_{j>p_i}a_{ij}x_j
    }{a_{i,p_i}}
    $$

    没有主元的变量称为自由元。若主元个数小于变量个数，则自由元可以任意取值，方程组有无穷多解；若每个变量列都有主元，则方程组有唯一解。

??? abstract "复杂度分析"

    对 $n$ 个变量、$n$ 个方程的普通方阵情形，前向消元的主项复杂度为 $\mathcal{O}(n^3)$，回代复杂度为 $\mathcal{O}(n^2)$。

## Gauss-Jordan 消元

???+ note "行最简形矩阵"

    在行阶梯形的基础上，若还满足：

    - 每个主元均为 $1$。
    - 每个主元所在列除主元外全为 $0$。

    则称其为行最简形矩阵。

    Gauss-Jordan 消元的目标，就是把增广矩阵进一步化到行最简形。此时主元变量可以直接读出，不需要回代。

??? success "具体步骤"

    可以先完成一次高斯消元，得到所有主元位置。接下来从最后一个主元向前处理。

    若第 $i$ 个主元位于 $(i,p_i)$，首先把该行除以主元，使得：

    $$
    a_{i,p_i}=1
    $$

    然后对每个 $k<i$，用第 $i$ 行消去第 $k$ 行在第 $p_i$ 列上的值：

    $$
    R_k\leftarrow R_k-a_{k,p_i}R_i
    $$

    由于我们是从下往上做，这一步不会破坏已经处理好的右侧主元列。所有主元处理完之后，每个主元列都只剩一个 $1$，其余位置均为 $0$。

    这时若第 $p_i$ 列是主元列，则第 $p_i$ 个变量可以写成：

    $$
    x_{p_i}
    =
    b_i-\sum_{j\notin P}a_{ij}x_j
    $$

    其中 $P$ 是所有主元列集合，$j\notin P$ 的变量是自由元。

??? note "求逆矩阵"

    Gauss-Jordan 消元也可以用于求逆矩阵。把 $\boldsymbol{A}$ 与单位矩阵拼成：

    $$
    (\boldsymbol{A}\mid\boldsymbol{I}_n)
    $$

    对其做初等行变换。若左侧能够化为 $\boldsymbol{I}_n$，右侧就变成了 $\boldsymbol{A}^{-1}$：

    $$
    (\boldsymbol{A}\mid\boldsymbol{I}_n)
    \sim
    (\boldsymbol{I}_n\mid\boldsymbol{A}^{-1})
    $$

    这是因为整个过程等价于左乘某个非异矩阵 $\boldsymbol{P}$，若 $\boldsymbol{P}\boldsymbol{A}=\boldsymbol{I}_n$，则 $\boldsymbol{P}=\boldsymbol{A}^{-1}$。

??? abstract "复杂度分析"

    Gauss-Jordan 消元同样是 $\mathcal{O}(n^3)$。常数通常大于只做前向消元与回代的高斯消元，但它可以直接得到行最简形，在求逆矩阵或处理自由元表达式时更方便。
