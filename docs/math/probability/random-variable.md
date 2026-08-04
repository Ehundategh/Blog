# 随机变量、期望与方差

## 随机变量

连续抛三次硬币时，一共有八种完整结果。如果只关心正面出现次数，那么正正反、正反正、反正正都可以映射到数值 $2$。随机变量正是从样本点到数值的函数。

???+ definition "随机变量"

    对于样本空间 $\Omega$ 中的每个样本点 $\omega$，都有唯一实数 $X(\omega)$ 与之对应，称 $X$ 为随机变量。若 $X$ 的全部可能取值有限或可以一一列举，就称 $X$ 为离散型随机变量。

???+ definition "分布列"

    设离散型随机变量 $X$ 的可能取值为 $x_1,x_2,\ldots,x_n$。若

    $$
    P(X=x_i)=p_i,
    \qquad i=1,2,\ldots,n,
    $$

    就称这些 $p_i$ 构成 $X$ 的概率分布列。

分布列满足 $p_i\geq0$ 且 $\sum_i p_i=1$。

## 数学期望

???+ definition "数学期望"

    设离散型随机变量 $X$ 的分布列为 $P(X=x_i)=p_i$，则

    $$
    E(X)=\sum_{i=1}^{n}x_ip_i
    $$

    称为 $X$ 的数学期望，简称期望。

期望是按照概率加权得到的平均值，它不一定是随机变量能够取得的值。例如均匀骰子的点数期望为

$$
E(X)=\dfrac{1+2+3+4+5+6}{6}=\dfrac72.
$$

???+ theorem "期望的仿射性质"

    对常数 $a,b$，有

    $$
    E(aX+b)=aE(X)+b.
    $$

??? proof "证明"

    若 $X$ 取值为 $x_i$，则 $aX+b$ 对应取值为 $ax_i+b$。于是

    $$
    \begin{aligned}
    E(aX+b)
    &=\sum_i(ax_i+b)P(X=x_i)\\
    &=aE(X)+b\sum_iP(X=x_i)\\
    &=aE(X)+b.
    \end{aligned}
    $$

???+ theorem "期望的线性性"

    若随机变量 $X,Y$ 的期望存在，则

    $$
    E(X+Y)=E(X)+E(Y).
    $$

    这里不要求 $X,Y$ 相互独立。

??? proof "证明"

    按照二者的联合取值求和，

    $$
    \begin{aligned}
    E(X+Y)
    &=\sum_x\sum_y(x+y)P(X=x,Y=y)\\
    &=\sum_xx\sum_yP(X=x,Y=y)
    +\sum_yy\sum_xP(X=x,Y=y)\\
    &=E(X)+E(Y).
    \end{aligned}
    $$

## 指示变量

???+ definition "指示变量"

    事件 $A$ 的指示变量定义为

    $$
    I_A=
    \begin{cases}
    1,&A\text{ 发生},\\
    0,&A\text{ 不发生}.
    \end{cases}
    $$

它的期望为

$$
E(I_A)=P(A).
$$

因此，“某件事发生了多少次”可以写成若干个指示变量之和，再使用期望线性性。

???+ note "例题：随机排列的不动点"

    从 $1,2,\ldots,n$ 的全部排列中等概率选择一个。若数字 $i$ 仍位于第 $i$ 个位置，就称 $i$ 是不动点。求不动点个数的期望。

??? tip "Hint"

    对每个位置定义一个指示变量，表示该位置是否为不动点。

??? success "解法"

    令 $I_i$ 表示位置 $i$ 是否为不动点，令 $X$ 表示不动点总数，则

    $$
    X=\sum_{i=1}^{n}I_i.
    $$

    数字 $i$ 等可能地出现在 $n$ 个位置之一，所以 $P(I_i=1)=\dfrac1n$。由期望线性性，

    $$
    E(X)=\sum_{i=1}^{n}E(I_i)
    =\sum_{i=1}^{n}\dfrac1n=1.
    $$

    各位置成为不动点的事件并不独立，但期望线性性不要求独立。

## 方差与协方差

???+ definition "方差"

    设离散型随机变量 $X$ 的分布列为 $P(X=x_i)=p_i$，定义

    $$
    D(X)=\sum_{i=1}^{n}\bigl(x_i-E(X)\bigr)^2p_i.
    $$

方差描述随机变量在期望附近的波动程度。

???+ theorem "方差的计算公式"

    $$
    D(X)=E(X^2)-\bigl(E(X)\bigr)^2.
    $$

??? proof "证明"

    记 $\mu=E(X)$，展开定义：

    $$
    \begin{aligned}
    D(X)
    &=\sum_{i=1}^{n}(x_i-\mu)^2p_i\\
    &=\sum_{i=1}^{n}x_i^2p_i
    -2\mu\sum_{i=1}^{n}x_ip_i
    +\mu^2\sum_{i=1}^{n}p_i\\
    &=E(X^2)-2\mu E(X)+\mu^2\\
    &=E(X^2)-\mu^2.
    \end{aligned}
    $$

???+ definition "协方差"

    随机变量 $X,Y$ 的协方差定义为

    $$
    \operatorname{Cov}(X,Y)
    =E\bigl((X-E(X))(Y-E(Y))\bigr).
    $$

展开可得

$$
\operatorname{Cov}(X,Y)=E(XY)-E(X)E(Y).
$$

???+ theorem "和的方差"

    $$
    D(X+Y)=D(X)+D(Y)+2\operatorname{Cov}(X,Y).
    $$

    特别地，若 $X,Y$ 独立，则

    $$
    D(X+Y)=D(X)+D(Y).
    $$

??? proof "证明"

    令 $\mu=E(X),\nu=E(Y)$，直接展开：

    $$
    \begin{aligned}
    D(X+Y)
    &=E\left(((X-\mu)+(Y-\nu))^2\right)\\
    &=D(X)+D(Y)+2\operatorname{Cov}(X,Y).
    \end{aligned}
    $$

    若 $X,Y$ 独立，则联合概率可以分解，从而 $E(XY)=E(X)E(Y)$，协方差为 $0$。

## 期望递推

面对随机过程，可以从下一步转移列方程。若状态 $i$ 经过一步后以概率 $p_{ij}$ 到达状态 $j$，每步代价为 $1$，令 $E_i$ 表示从状态 $i$ 到结束还需的期望步数，则

$$
E_i=1+\sum_jp_{ij}E_j.
$$

如果其中包含 $j=i$，右侧会出现 $p_{ii}E_i$。这就是自环项，需要移到左侧后再求解。

## 例题：灯潮往复

???+ note "题目描述"

    有 $n$ 盏灯，第 $i$ 盏灯的初始状态为 $a_i\in\{0,1\}$，亮起时贡献 $w_i$。有 $m$ 个按钮，第 $j$ 个按钮翻转区间 $[l_j,r_j]$ 内全部灯。独立进行 $k$ 轮，每轮等概率选择一个按钮。求最终总亮度的期望。

??? tip "Hint"

    分别计算每盏灯最终亮起的概率。单盏灯的状态只有亮、灭两种，其概率满足一阶递推。

??? success "解法一：化为等比递推"

    定义指示变量 $X_i$ 表示第 $i$ 盏灯最终是否亮起。若最终总亮度为 $L$，则

    $$
    E(L)=\sum_{i=1}^{n}w_iP(X_i=1).
    $$

    记覆盖第 $i$ 盏灯的按钮数为 $c_i$，一轮中它被翻转的概率为

    $$
    q_i=\dfrac{c_i}{m}.
    $$

    令 $p_{i,t}$ 表示经过 $t$ 轮后第 $i$ 盏灯亮起的概率。下一轮亮起有两种互斥情况：原来亮且没有被翻转，或者原来灭且被翻转。因此

    $$
    p_{i,t+1}=p_{i,t}(1-q_i)+(1-p_{i,t})q_i.
    $$

    整理为

    $$
    p_{i,t+1}-\dfrac12
    =(1-2q_i)\left(p_{i,t}-\dfrac12\right).
    $$

    连续递推 $k$ 次，得到

    $$
    p_{i,k}=\dfrac12+\left(a_i-\dfrac12\right)(1-2q_i)^k.
    $$

    用区间差分求出全部 $c_i$，快速幂计算 $(1-2q_i)^k$，再累加 $w_ip_{i,k}$。

??? success "解法二：矩阵快速幂加速递推"

    不化出闭式，也可以直接对亮、灭两种状态的概率进行递推。令

    $$
    \boldsymbol{F}_{i,t}
    =
    \begin{bmatrix}
    P(X_{i,t}=0)\\
    P(X_{i,t}=1)
    \end{bmatrix},
    $$

    其中 $X_{i,t}$ 表示经过 $t$ 轮后第 $i$ 盏灯的状态。若本轮没有翻转，状态不变；若本轮翻转，亮、灭两种状态交换。因此转移矩阵为

    $$
    \boldsymbol{M}_i
    =
    \begin{bmatrix}
    1-q_i&q_i\\
    q_i&1-q_i
    \end{bmatrix},
    $$

    并且

    $$
    \boldsymbol{F}_{i,t+1}
    =\boldsymbol{M}_i\boldsymbol{F}_{i,t}.
    $$

    初始状态为

    $$
    \boldsymbol{F}_{i,0}
    =
    \begin{bmatrix}
    1-a_i\\
    a_i
    \end{bmatrix}.
    $$

    由于每一轮的转移矩阵完全相同，连续转移 $k$ 轮后有

    $$
    \boldsymbol{F}_{i,k}
    =\boldsymbol{M}_i^k\boldsymbol{F}_{i,0}.
    $$

    矩阵从状态向量左侧作用，所以快速幂求出的 $\boldsymbol{M}_i^k$ 也应左乘初始向量。结果向量的第二个分量就是 $p_{i,k}$。最后由期望的线性性得到

    $$
    E(L)=\sum_{i=1}^{n}w_i\left(\boldsymbol{M}_i^k\boldsymbol{F}_{i,0}\right)_2.
    $$

    两种方法使用的转移完全相同。第一种方法将二阶线性变换化为一个等比数列；第二种方法则保留两个状态，直接计算转移矩阵的 $k$ 次幂。

??? abstract "复杂度分析"

    区间差分复杂度为 $\mathcal{O}(m+n)$。对每盏灯使用标量快速幂或二阶矩阵快速幂，时间复杂度均为 $\mathcal{O}(m+n\log k)$，空间复杂度为 $\mathcal{O}(n)$。
