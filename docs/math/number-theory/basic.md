# 基础数论

这一节只讨论整数。也就是说，后面提到的数默认都在整数集 $\mathbb Z$ 中，除非单独说明。

基础数论中反复出现的线索可以概括为：带余除法给出同余，Euclid 算法给出最大公因数，Bézout 定理刻画逆元；再由质因数分解得到约数函数、Euler 函数，最后用简化剩余系推出 Euler 定理与 Fermat 小定理，并用 Dirichlet 卷积的语言引出 Möbius 函数与 Möbius 反演。

## 同余与最大公因数

### 整除与带余除法

给定 $a,b\in\mathbb Z$ 且 $b\ne 0$。若存在 $c\in\mathbb Z$ 使得 $a=bc$，则称 $b$ 整除 $a$，记作 $b\mid a$；否则记作 $b\nmid a$。

???+ theorem "带余除法定理"

    给定 $a\in\mathbb Z$ 与 $b\in\mathbb Z^+$，存在唯一的一对整数 $q,r$，使得

    $$
    a=bq+r,\qquad 0\le r<b.
    $$

??? proof "证明"

    取 $q=\left\lfloor\dfrac{a}{b}\right\rfloor$，$r=a-bq$。由下取整的定义立刻有 $0\le r<b$，所以存在性成立。

    若另有 $a=bq'+r'$，其中 $0\le r'<b$，则

    $$
    b(q-q')=r'-r.
    $$

    右侧绝对值小于 $b$，左侧又是 $b$ 的倍数，所以两边只能同时为 $0$。于是 $q=q'$，$r=r'$。

### 同余

给定正整数 $m$，如果 $m\mid(a-b)$，就称 $a,b$ 在模 $m$ 意义下同余，记作

$$
a\equiv b\pmod m.
$$

这等价于 $a,b$ 除以 $m$ 所得余数相同。

??? proof "同余与余数相同的等价性"

    分别写成 $a=mq_1+r_1,b=mq_2+r_2$，其中 $0\le r_1,r_2<m$。于是

    $$
    a-b=m(q_1-q_2)+(r_1-r_2).
    $$

    若 $r_1=r_2$，显然 $m\mid(a-b)$。反之，若 $m\mid(a-b)$，则 $m\mid(r_1-r_2)$，而 $\left|r_1-r_2\right|<m$，所以只能有 $r_1=r_2$。

???+ theorem "同余的基本性质"

    同余关系满足自反性、对称性与传递性。进一步地，若 $a\equiv b\pmod m$，$c\equiv d\pmod m$，则

    $$
    a\pm c\equiv b\pm d\pmod m,
    $$

    $$
    ac\equiv bd\pmod m,\qquad a^k\equiv b^k\pmod m\quad(k\in\mathbb Z^+).
    $$

??? proof "证明"

    显然 $m\mid(a-a)$，所以自反性成立。若 $m\mid(a-b)$，则 $m\mid(b-a)$，所以对称性成立。若 $m\mid(a-b)$ 且 $m\mid(b-c)$，则 $m\mid(a-c)$，所以传递性成立。

    由条件可写成 $a-b=mu,c-d=mv$。此时

    $$
    (a\pm c)-(b\pm d)=m(u\pm v),
    $$

    $$
    ac-bd=c(a-b)+b(c-d)=m(cu+bv),
    $$

    所以加、减、乘的结论成立。最后对 $k$ 使用归纳法：$k=1$ 时显然成立；若 $a^k\equiv b^k\pmod m$，再同时乘上 $a\equiv b\pmod m$，即可得到 $a^{k+1}\equiv b^{k+1}\pmod m$。

上述性质说明了同余运算的封闭性：把整数换成它除以 $m$ 的余数后，继续做加法、减法或乘法，所得结果与原式仍然同余。实际计算中，可以在每一步运算后立刻取模：

$$
(a+b)\bmod m=((a\bmod m)+(b\bmod m))\bmod m.
$$

乘法同理。这样既不改变最终余数，也能避免中间结果不必要地增长。

但是除法不能照搬这个结论。由 $ac\equiv bc\pmod m$ 一般不能直接约去 $c$；只有当 $c$ 在模 $m$ 意义下存在逆元时，才能把除以 $c$ 改写成乘上 $c$ 的逆元。

### 同余类与剩余系

给定模数 $m$，与整数 $a$ 同余的所有整数构成集合

$$
\overline a=\{a+km\mid k\in\mathbb Z\},
$$

称为 $a$ 模 $m$ 的同余类，也称剩余类。任意整数恰好属于 $\overline0,\overline1,\ldots,\overline{m-1}$ 中的一个。

??? proof "证明"

    由带余除法，每个整数 $a$ 都唯一写成 $a=mq+r$，其中 $0\le r<m$，于是 $a\in\overline r$。

    若 $a$ 同时属于 $\overline{r_1}$ 与 $\overline{r_2}$，则 $r_1\equiv r_2\pmod m$；由 $0\le r_1,r_2<m$ 得 $r_1=r_2$，故所属同余类唯一。

若 $m$ 个整数 $a_1,a_2,\ldots,a_m$ 满足 $\overline{a_1},\overline{a_2},\ldots,\overline{a_m}$ 恰好是模 $m$ 的全部同余类，就称它们组成模 $m$ 的一个完全剩余系。

???+ theorem "完全剩余系判别"

    $m$ 个整数构成模 $m$ 的完全剩余系，当且仅当它们两两不同余。

??? proof "证明"

    若它们构成完全剩余系，每个同余类只被代表一次，因此必然两两不同余。

    反之，模 $m$ 一共只有 $m$ 个同余类；$m$ 个两两不同余的整数分别落入不同的类，所以没有任何同余类能够遗漏，它们便构成完全剩余系。

在模 $m$ 的完全剩余系中，与 $m$ 互质的同余类共有若干个。每类任取一个代表所得的整数集合，称为模 $m$ 的一个简化剩余系；其中元素个数记为 $\varphi(m)$，称为 Euler 函数。

例如，模 $10$ 中与 $10$ 互质的同余类为 $\{\overline1,\overline3,\overline7,\overline9\}$，取代表元后，$\{1,3,7,9\}$ 构成一个简化剩余系，所以 $\varphi(10)=4$。注意我们只关心每个数所在的同余类，因此 $\{11,13,17,19\}$ 也是模 $10$ 的简化剩余系。

### 最大公因数

给定不全为 $0$ 的整数 $a,b$，同时整除 $a,b$ 的正整数称为它们的公因数，其中最大的一个称为最大公因数，记作 $\gcd(a,b)$。

???+ theorem "Euclid 算法"

    若 $a=bq+r$，则

    $$
    \gcd(a,b)=\gcd(b,r).
    $$

??? proof "证明"

    若 $d\mid a$ 且 $d\mid b$，则 $d\mid(a-bq)=r$，所以 $a,b$ 的每个公因数也是 $b,r$ 的公因数。

    反之，若 $d\mid b$ 且 $d\mid r$，则 $d\mid(bq+r)=a$。两组公因数完全相同，最大者自然相同。

重复应用 Euclid 算法，余数严格递减，最终必然得到

$$
\begin{aligned}
a&=bq_1+r_1,\\
b&=r_1q_2+r_2,\\
&\ \vdots\\
r_{k-2}&=r_{k-1}q_k+r_k,\\
r_{k-1}&=r_kq_{k+1}.
\end{aligned}
$$

由前一定理逐行替换可知 $\gcd(a,b)=r_k$。因此 Euclid 算法不仅会终止，而且最后一个非零余数就是最大公因数。

```cpp
int Gcd(int a,int b) {
    return b==0?a:Gcd(b,a%b);
}
```

### Bézout 定理

???+ theorem "Bézout 定理"

    若 $a,b$ 不全为 $0$，则存在整数 $x,y$，使得

    $$
    ax+by=\gcd(a,b).
    $$

??? proof "证明"

    考虑所有形如 $ax+by$ 的正整数，它们构成的集合非空，故存在最小值 $d=ax_0+by_0$。

    对 $a$ 除以 $d$，写成 $a=qd+r$，其中 $0\le r<d$。注意

    $$
    r=a-q(ax_0+by_0)=a(1-qx_0)+b(-qy_0).
    $$

    若 $r>0$，它也是形如 $ax+by$ 的正整数且小于 $d$，与 $d$ 的最小性矛盾，所以 $r=0$，即 $d\mid a$。同理 $d\mid b$。

    接着，$d$ 是 $a,b$ 的一个公因数。另一方面，任取公因数 $c$，由 $c\mid a,c\mid b$ 可知

    $$
    c\mid(ax_0+by_0)=d.
    $$

    因此所有公因数都整除 $d$，而 $d$ 本身又是正公因数，所以 $d=\gcd(a,b)$，定理得证。

扩展 Euclid 算法就是在求 $\gcd(a,b)$ 的同时求出一组 $x,y$。

```cpp
int ExGcd(int a,int b,int &x,int &y) {
    if (b==0) {
        x=1;y=0;
        return a;
    }
    int x1,y1,d=ExGcd(b,a%b,x1,y1);
    x=y1;
    y=x1-a/b*y1;
    return d;
}
```

这一过程也可以用矩阵来理解。令初始状态向量为

$$
\boldsymbol{s}_0=
\begin{pmatrix}
a\\
b
\end{pmatrix}.
$$

考虑某一轮辗转相除，若当前状态为

$$
\boldsymbol{s}=
\begin{pmatrix}
x\\
y
\end{pmatrix},
$$

且

$$
x=yq+r,\qquad q=\left\lfloor\dfrac{x}{y}\right\rfloor,
$$

那么下一轮状态应当变为 $(y,r)^T$。定义这一轮的变换矩阵

$$
\boldsymbol{P}_q=
\begin{pmatrix}
0&1\\
1&-q
\end{pmatrix}.
$$

则有

$$
\boldsymbol{P}_q\boldsymbol{s}
=
\begin{pmatrix}
y\\
x-qy
\end{pmatrix}
=
\begin{pmatrix}
y\\
r
\end{pmatrix}.
$$

也就是说，Euclid 算法中从 $(x,y)$ 变成 $(y,x\bmod y)$，等价于左乘一次 $\boldsymbol{P}_q$。

接下来考虑如何维护从初始状态到当前状态的变换矩阵。若当前已经有

$$
\boldsymbol{s}=\boldsymbol{T}\boldsymbol{s}_0,
$$

再做一次辗转相除，则

$$
\boldsymbol{s}'
=
\boldsymbol{P}_q\boldsymbol{s}
=
\boldsymbol{P}_q\boldsymbol{T}\boldsymbol{s}_0.
$$

所以维护矩阵时，新矩阵应当是 $\boldsymbol{P}_q\boldsymbol{T}$，也就是新变换左乘旧变换。连续做完辗转相除后，可以得到

$$
\begin{pmatrix}
\gcd(a,b)\\
0
\end{pmatrix}
=
\boldsymbol{T}
\begin{pmatrix}
a\\
b
\end{pmatrix},
$$

若

$$
\boldsymbol{T}=
\begin{pmatrix}
x_1&x_2\\
x_3&x_4
\end{pmatrix},
$$

则第一行给出

$$
ax_1+bx_2=\gcd(a,b).
$$

这正是扩展 Euclid 算法中要求的系数。因此我们也可以直接维护这个 $2\times2$ 变换矩阵。

```cpp
struct Matrix{
    long long Num[3][3];
    void Init(){
        for(int i=1;i<=2;i++) for(int j=1;j<=2;j++) Num[i][j]=0;
    }
};
Matrix operator*(Matrix a,Matrix b){
    Matrix Ret;Ret.Init();
    for(int i=1;i<=2;i++){
        for(int j=1;j<=2;j++){
            for(int k=1;k<=2;k++){
                Ret.Num[i][j]+=a.Num[i][k]*b.Num[k][j];
            }
        }
    }
    return Ret;
}
Matrix Unit(){
    Matrix Ret;Ret.Init();
    Ret.Num[1][1]=Ret.Num[2][2]=1;
    return Ret;
}
Matrix Make(int q){
    Matrix Ret;Ret.Init();
    Ret.Num[1][2]=1;
    Ret.Num[2][1]=1;
    Ret.Num[2][2]=-q;
    return Ret;
}
int ExGcd_Matrix(int a,int b,int &x,int &y) {
    Matrix Val=Unit();
    while (b) {
        int q=a/b;
        Matrix Now=Make(q);
        Val=Now*Val;
        int r=a-q*b;
        a=b;b=r;
    }
    x=Val.Num[1][1];y=Val.Num[1][2];
    return a;
}
```

这一写法和递归写法维护的是同一件事：递归写法在回溯时恢复系数，矩阵写法则把每一轮变换直接左乘到 $\boldsymbol{T}$ 上。最后 $\boldsymbol{T}$ 的第一行就是 $\gcd(a,b)$ 关于初始 $a,b$ 的线性表示。

### 模逆元

若存在整数 $x$ 满足 $ax\equiv1\pmod m$，则称 $x$ 是 $a$ 模 $m$ 意义下的逆元，记作 $a^{-1}$。此时，模意义下的除法可以改写为

$$
\dfrac{b}{a}\equiv b\cdot a^{-1}\pmod m.
$$

???+ theorem "逆元存在判别"

    $a$ 模 $m$ 的逆元存在，当且仅当 $\gcd(a,m)=1$。

??? proof "证明"

    若逆元 $x$ 存在，则 $ax\equiv1\pmod m$，所以存在整数 $k$ 使 $ax-mk=1$。任意 $a,m$ 的公因数都必须整除左侧，从而整除 $1$，故 $\gcd(a,m)=1$。

    反之，若 $\gcd(a,m)=1$，根据 Bézout 定理，存在整数 $x,y$ 使 $ax+my=1$。对等式两边模 $m$，得到 $ax\equiv1\pmod m$，因此 $x$ 就是 $a$ 的逆元。

???+ theorem "逆元唯一性"

    若逆元存在，则它在模 $m$ 意义下唯一。

??? proof "证明"

    若 $ax\equiv ay\equiv1\pmod m$，在两边同乘任意一个逆元 $a^{-1}$，便有 $x\equiv y\pmod m$。

???+ theorem "约去同因子"

    若 $ac\equiv bc\pmod m$ 且 $\gcd(c,m)=1$，则 $a\equiv b\pmod m$。

??? proof "证明"

    由 $\gcd(c,m)=1$，$c^{-1}$ 存在。在同余式两边同时乘 $c^{-1}$，得到 $a\equiv b\pmod m$。

因此，当题目要求对一个质数 $p$ 取模时，每个不被 $p$ 整除的数都有逆元，合法的除法都可以转成乘法。特别地，组合数等式中的分母若不含因子 $p$，就可以逐项乘逆元；若分母能被 $p$ 整除，则不能这样处理，需要另外分析。

```cpp
int Inv(int a,int Mod) {
    int x,y;
    ExGcd(a,Mod,x,y);
    x=(x%Mod+Mod)%Mod;
    return x;
}
```

若模数是质数 $p$，且 $p\nmid a$，后面的 Fermat 小定理还会给出另一种表示：

$$
a^{-1}\equiv a^{p-2}\pmod p.
$$

对应实现是快速幂。

```cpp
int Pow(int a,int b,int Mod) {
    int Ret=1;
    while (b) {
        if (b&1) Ret=1ll*Ret*a%Mod;
        a=1ll*a*a%Mod;
        b>>=1;
    }
    return Ret;
}
```

### 中国剩余定理

???+ theorem "中国剩余定理"

    设正整数 $m_1,m_2,\ldots,m_k$ 两两互质，则同余方程组

    $$
    \left\{
    \begin{aligned}
    x&\equiv a_1\pmod {m_1},\\
    x&\equiv a_2\pmod {m_2},\\
    &\ \vdots\\
    x&\equiv a_k\pmod {m_k}
    \end{aligned}
    \right.
    $$

    在模 $M=\prod_{i=1}^k m_i$ 意义下有且仅有一个解。

??? proof "证明"

    令 $M_i=\dfrac{M}{m_i}$。由于各模数两两互质，有 $\gcd(M_i,m_i)=1$，所以存在 $t_i$ 满足

    $$
    M_it_i\equiv1\pmod {m_i}.
    $$

    构造

    $$
    x=\sum_{i=1}^k a_iM_it_i.
    $$

    对任意固定的 $j$，当 $i\ne j$ 时有 $m_j\mid M_i$，对应项模 $m_j$ 为 $0$；而第 $j$ 项满足 $a_jM_jt_j\equiv a_j\pmod {m_j}$。所以 $x\equiv a_j\pmod {m_j}$，存在性成立。

    若 $x,y$ 都是方程组的解，则每个 $m_i$ 都整除 $x-y$。下面使用结论：若 $\gcd(r,s)=1$ 且 $r\mid n,s\mid n$，则 $rs\mid n$。

    事实上，写 $n=rq$，再由 Bézout 定理取 $ur+vs=1$，便有

    $$
    q=urq+vsq=un+vsq,
    $$

    故 $s\mid q$，从而 $rs\mid n$。对两两互质的 $m_i$ 反复使用这一结论，得到 $M\mid(x-y)$，即 $x\equiv y\pmod M$，唯一性成立。

## 数论函数

### 质数与唯一分解

大于 $1$ 的正整数 $p$，如果它的正因数只有 $1$ 和 $p$，就称 $p$ 为质数；大于 $1$ 且不是质数的正整数称为合数。

特别地，$1$ 既不是质数也不是合数。每个大于 $1$ 的合数 $n$ 都能写成 $n=ab$，其中 $1<a,b<n$，这是后面递归分解的基础。

???+ theorem "Euclid 引理"

    若 $p$ 是质数且 $p\mid ab$，则 $p\mid a$ 或 $p\mid b$。

??? proof "证明"

    若 $p\mid a$，结论已经成立。否则，因为 $p$ 的正因数只有 $1,p$，所以 $\gcd(p,a)=1$。

    根据 Bézout 定理，存在整数 $x,y$ 满足 $px+ay=1$。两边同乘 $b$，得到

    $$
    pbx+aby=b.
    $$

    $p$ 同时整除左侧的两项，因此 $p\mid b$。

???+ theorem "算术基本定理"

    每个大于 $1$ 的正整数都能够写成若干个质数的乘积；忽略质因数的排列顺序后，这种分解唯一。

??? proof "证明"

    先证明存在性。对 $n$ 使用强归纳法：$n=2$ 时结论成立。假设所有小于 $n$ 且大于 $1$ 的整数都能分解。若 $n$ 本身是质数，已经得到分解；否则 $n=ab$，其中 $1<a,b<n$，由归纳假设 $a,b$ 都能写成质数乘积，将两式相乘即得 $n$ 的质因数分解。

    再证明唯一性。假设

    $$
    n=p_1p_2\cdots p_r=q_1q_2\cdots q_s,
    $$

    其中所有 $p_i,q_j$ 都是质数。因为 $p_1\mid q_1q_2\cdots q_s$，反复使用 Euclid 引理，必有某个 $q_j$ 被 $p_1$ 整除。两个数均为质数，所以 $p_1=q_j$。约去这一公共质因数后，对剩余乘积重复上述过程，最终两侧的质因数逐一对应。因此两种分解只可能相差排列顺序。

根据算术基本定理，任意 $n>1$ 都能唯一写成标准形式

$$
n=p_1^{\alpha_1}p_2^{\alpha_2}\cdots p_k^{\alpha_k},
$$

其中 $p_1,p_2,\ldots,p_k$ 是两两不同的质数，$\alpha_i\in\mathbb Z^+$。这一表示把关于因数的问题转化为了对每个指数 $\alpha_i$ 的独立选择。

### 约数函数

???+ theorem "约数个数与约数和"

    若 $n=\prod_{i=1}^k p_i^{\alpha_i}$，则 $n$ 的正因数个数为

    $$
    \tau(n)=\prod_{i=1}^k(\alpha_i+1),
    $$

    全部正因数之和为

    $$
    \sigma(n)=\prod_{i=1}^k(1+p_i+p_i^2+\cdots+p_i^{\alpha_i}).
    $$

??? proof "证明"

    $n$ 的任意正因数 $d$ 都有且仅有一种表示

    $$
    d=p_1^{\beta_1}p_2^{\beta_2}\cdots p_k^{\beta_k},
    \qquad 0\le \beta_i\le \alpha_i.
    $$

    每个 $\beta_i$ 有 $\alpha_i+1$ 种选择，而且各指数相互独立，所以选择总数为 $\prod_{i=1}^k(\alpha_i+1)$。

    对所有选择对应的 $d$ 求和，利用乘法分配律，有

    $$
    \sum_{d\mid n}d
    =
    \prod_{i=1}^k\left(\sum_{j=0}^{\alpha_i}p_i^j\right),
    $$

    这正是所给的约数和公式。

### Euler 函数

Euler 函数 $\varphi(n)$ 表示 $1,2,\ldots,n$ 中与 $n$ 互质的整数个数。等价地，它也是模 $n$ 的简化剩余系所含元素个数。

???+ theorem "质数幂的 Euler 函数"

    若 $p$ 为质数且 $k\in\mathbb Z^+$，则

    $$
    \varphi(p^k)=p^k-p^{k-1}=p^k\left(1-\dfrac{1}{p}\right).
    $$

??? proof "证明"

    $1$ 到 $p^k$ 中，只有 $p,2p,\ldots,p^{k-1}p$ 与 $p^k$ 不互质，共 $p^{k-1}$ 个。从总数 $p^k$ 中减去它们即可。

???+ theorem "Euler 函数的积性"

    若 $\gcd(m,n)=1$，则

    $$
    \varphi(mn)=\varphi(m)\varphi(n).
    $$

??? proof "证明"

    由中国剩余定理，模 $mn$ 的每个同余类与一对模 $m$、模 $n$ 的同余类一一对应。

    一个整数与 $mn$ 互质，当且仅当它同时与 $m,n$ 互质。因此，模 $mn$ 中与 $mn$ 互质的同余类，恰好对应于“一个模 $m$ 的简化剩余类”和“一个模 $n$ 的简化剩余类”的任意组合，共有 $\varphi(m)\varphi(n)$ 个。

???+ theorem "Euler 函数公式"

    若 $n=\prod_{i=1}^k p_i^{\alpha_i}$，则

    $$
    \varphi(n)=n\prod_{p\mid n}\left(1-\dfrac{1}{p}\right).
    $$

??? proof "证明"

    不同质数的幂两两互质，连续使用积性及质数幂公式，得到

    $$
    \varphi(n)
    =
    \prod_{i=1}^k\varphi(p_i^{\alpha_i})
    =
    \prod_{i=1}^k p_i^{\alpha_i}\left(1-\dfrac{1}{p_i}\right)
    =
    n\prod_{i=1}^k\left(1-\dfrac{1}{p_i}\right).
    $$

???+ theorem "Euler 函数的约数和"

    对于任意正整数 $n$，有

    $$
    \sum_{d\mid n}\varphi(d)=n.
    $$

    用后面 Dirichlet 卷积的记号，这一式子也可以写成

    $$
    \varphi * \mathbf 1=\operatorname{Id}.
    $$

??? proof "证明"

    按照 $\gcd(k,n)$ 的值将 $1,2,\ldots,n$ 分类。对每个 $d\mid n$，满足 $\gcd(k,n)=\dfrac{n}{d}$ 的整数 $k$ 可写成 $k=\dfrac{n}{d} t$，条件等价于 $1\le t\le d$ 且 $\gcd(t,d)=1$，所以这一类恰有 $\varphi(d)$ 个。

    所有类别不重不漏地覆盖了 $n$ 个整数，因此各类大小之和为 $n$。

计算单个 $\varphi(n)$ 时，可以直接分解质因数。

```cpp
int Phi(int n) {
    int Ret=n;
    for (int i=2;i*i<=n;i++) {
        if (n%i==0) {
            Ret=Ret/i*(i-1);
            while (n%i==0) n/=i;
        }
    }
    if (n>1) Ret=Ret/n*(n-1);
    return Ret;
}
```

若要同时求出 $1\sim n$ 的质数、$\varphi$ 与 $\mu$，线性筛会更自然。

```cpp
void Init(int n) {
    Phi[1]=1;Mu[1]=1;
    for (int i=2;i<=n;i++) {
        if (!Mark[i]) {
            Prime[++cnt]=i;
            Phi[i]=i-1;
            Mu[i]=-1;
        }
        for (int j=1;j<=cnt&&i*Prime[j]<=n;j++) {
            int To=i*Prime[j];
            Mark[To]=true;
            if (i%Prime[j]==0) {
                Phi[To]=Phi[i]*Prime[j];
                Mu[To]=0;
                break;
            }
            Phi[To]=Phi[i]*(Prime[j]-1);
            Mu[To]=-Mu[i];
        }
    }
}
```

## 定理与反演

### Euler 定理与 Fermat 小定理

???+ theorem "简化剩余系的乘法重排"

    若 $\gcd(a,m)=1$，且 $r_1,r_2,\ldots,r_{\varphi(m)}$ 是模 $m$ 的一个简化剩余系，则

    $$
    ar_1,ar_2,\ldots,ar_{\varphi(m)}
    $$

    仍然是模 $m$ 的一个简化剩余系。

??? proof "证明"

    首先，任取 $i$，因为 $\gcd(a,m)=1$ 且 $\gcd(r_i,m)=1$，所以

    $$
    \gcd(ar_i,m)=1.
    $$

    也就是说，$ar_i$ 一定落在与 $m$ 互质的同余类中。

    接下来只需要证明这些同余类两两不同。若存在 $i\ne j$ 使得

    $$
    ar_i\equiv ar_j\pmod m,
    $$

    由于 $\gcd(a,m)=1$，根据前面的约去同因子结论，可以得到

    $$
    r_i\equiv r_j\pmod m,
    $$

    这与 $r_1,r_2,\ldots,r_{\varphi(m)}$ 是简化剩余系矛盾。

    因此 $ar_1,ar_2,\ldots,ar_{\varphi(m)}$ 恰好给出了所有与 $m$ 互质的同余类，也就是一个新的简化剩余系。

???+ theorem "Euler 定理"

    若 $\gcd(a,m)=1$，则

    $$
    a^{\varphi(m)}\equiv1\pmod m.
    $$

??? proof "证明"

    取模 $m$ 的一个简化剩余系 $r_1,r_2,\ldots,r_{\varphi(m)}$。由上一条结论，$ar_1,ar_2,\ldots,ar_{\varphi(m)}$ 仍是一个简化剩余系，因此两组元素的乘积同余：

    $$
    a^{\varphi(m)}
    \prod_{i=1}^{\varphi(m)}r_i
    \equiv
    \prod_{i=1}^{\varphi(m)}r_i
    \pmod m.
    $$

    每个 $r_i$ 都与 $m$ 互质，所以乘积也与 $m$ 互质，可以约去，得到结论。

???+ theorem "Fermat 小定理"

    若 $p$ 是质数，则对任意整数 $a$，有

    $$
    a^p\equiv a\pmod p.
    $$

    特别地，当 $p\nmid a$ 时，有 $a^{p-1}\equiv1\pmod p$。

??? proof "证明"

    若 $p\mid a$，则 $a^p\equiv a\equiv0\pmod p$。

    若 $p\nmid a$，则 $\gcd(a,p)=1$，又因为 $\varphi(p)=p-1$，由 Euler 定理有 $a^{p-1}\equiv1\pmod p$。两边同乘 $a$，得到 $a^p\equiv a\pmod p$。两种情况已经覆盖任意整数 $a$。

现在回到“对质数 $p$ 取模”的题目。若 $p\nmid a$，由 Fermat 小定理

$$
a^{p-1}\equiv1\pmod p,
$$

所以

$$
a^{-1}\equiv a^{p-2}\pmod p.
$$

因此，模质数意义下的合法除法可以写成乘 $a^{p-2}$。计算一个由加、减、乘、除组成的式子时，加减乘随时取模；只有除法需要先检查分母是否为 $0\pmod p$，再乘逆元。这个条件不能省略。

### Dirichlet 卷积

在数论函数中，经常会出现“对所有约数求和”的形式。为了把这类式子统一起来，我们定义 Dirichlet 卷积。

设 $f,g$ 是定义在正整数上的函数，定义

$$
(f*g)(n)=\sum_{d\mid n}f(d)g\left(\dfrac{n}{d}\right).
$$

这里的求和变量 $d$ 遍历 $n$ 的所有正因数。这个定义的意义在于，它把“拆成两个互补约数”的贡献统一写成一个运算。

常用的几个数论函数如下：

$$
\mathbf 1(n)=1,
$$

$$
\operatorname{Id}(n)=n,
$$

$$
\varepsilon(n)=
\begin{cases}
1,&n=1,\\
0,&n>1.
\end{cases}
$$

其中 $\mathbf 1$ 是常数函数，$\operatorname{Id}$ 是恒等函数，$\varepsilon$ 是 Dirichlet 卷积下的单位元。

???+ theorem "Dirichlet 卷积的基本性质"

    对任意数论函数 $f,g,h$，Dirichlet 卷积满足交换律和结合律：

    $$
    f*g=g*f,
    $$

    $$
    (f*g)*h=f*(g*h).
    $$

    并且有

    $$
    f*\varepsilon=f.
    $$

    同时，Dirichlet 卷积对函数加法满足分配律：

    $$
    f*(g+h)=f*g+f*h.
    $$

??? proof "证明"

    交换律直接来自互补约数的替换。具体地，

    $$
    (f*g)(n)=\sum_{d\mid n}f(d)g\left(\dfrac{n}{d}\right).
    $$

    令 $e=\dfrac{n}{d}$，当 $d$ 遍历 $n$ 的因数时，$e$ 也恰好遍历 $n$ 的因数，于是

    $$
    (f*g)(n)=\sum_{e\mid n}f\left(\dfrac{n}{e}\right)g(e)=(g*f)(n).
    $$

    接下来考虑结合律。展开左侧：

    $$
    \begin{aligned}
    ((f*g)*h)(n)
    &=
    \sum_{d\mid n}(f*g)(d)h\left(\dfrac{n}{d}\right)\\
    &=
    \sum_{d\mid n}\sum_{e\mid d}f(e)g\left(\dfrac{d}{e}\right)h\left(\dfrac{n}{d}\right).
    \end{aligned}
    $$

    这等价于把 $n$ 分解成三个正整数的乘积 $abc=n$，贡献为 $f(a)g(b)h(c)$。右侧 $(f*(g*h))(n)$ 展开后也是对所有 $abc=n$ 的三元分解求同样的贡献，因此二者相等。

    最后，

    $$
    (f*\varepsilon)(n)=\sum_{d\mid n}f(d)\varepsilon\left(\dfrac{n}{d}\right).
    $$

    只有 $\dfrac{n}{d}=1$，也就是 $d=n$ 时 $\varepsilon\left(\dfrac{n}{d}\right)=1$，其余项都为 $0$，所以 $(f*\varepsilon)(n)=f(n)$。

    分配律直接展开即可：

    $$
    \begin{aligned}
    (f*(g+h))(n)
    &=
    \sum_{d\mid n}f(d)(g+h)\left(\dfrac{n}{d}\right)\\
    &=
    \sum_{d\mid n}f(d)g\left(\dfrac{n}{d}\right)
    +
    \sum_{d\mid n}f(d)h\left(\dfrac{n}{d}\right)\\
    &=
    (f*g)(n)+(f*h)(n).
    \end{aligned}
    $$

???+ theorem "Dirichlet 逆"

    数论函数 $f$ 存在 Dirichlet 逆，当且仅当 $f(1)\ne0$。也就是说，此时存在唯一的数论函数 $g$，使得

    $$
    f*g=\varepsilon.
    $$

??? proof "证明"

    先看必要性。若 $f*g=\varepsilon$，代入 $n=1$，得到

    $$
    f(1)g(1)=1,
    $$

    所以 $f(1)\ne0$。

    反过来，若 $f(1)\ne0$，则先令

    $$
    g(1)=\dfrac{1}{f(1)}.
    $$

    对于 $n>1$，由 $(f*g)(n)=0$ 可得

    $$
    \sum_{d\mid n}f(d)g\left(\dfrac{n}{d}\right)=0.
    $$

    将 $d=n$ 的一项单独取出：

    $$
    f(n)g(1)+
    \sum_{\substack{d\mid n\\d<n}}f(d)g\left(\dfrac{n}{d}\right)=0.
    $$

    更方便地，也可以将含 $g(n)$ 的 $d=1$ 一项取出：

    $$
    f(1)g(n)+
    \sum_{\substack{d\mid n\\d>1}}f(d)g\left(\dfrac{n}{d}\right)=0.
    $$

    因此

    $$
    g(n)=
    -\dfrac{1}{f(1)}
    \sum_{\substack{d\mid n\\d>1}}f(d)g\left(\dfrac{n}{d}\right).
    $$

    右侧只会用到 $g(t)$ 且 $t<n$ 的值，因此可以递推确定 $g(n)$。存在性与唯一性同时得到。

???+ theorem "积性函数在卷积下封闭"

    若 $f,g$ 都是积性函数，则 $f*g$ 也是积性函数。

??? proof "证明"

    设 $\gcd(a,b)=1$。由于 $a,b$ 互质，$ab$ 的每个因数 $d$ 都能唯一写成 $d=d_1d_2$，其中 $d_1\mid a,d_2\mid b$。

    于是

    $$
    \begin{aligned}
    (f*g)(ab)
    &=
    \sum_{d\mid ab}f(d)g\left(\dfrac{ab}d\right)\\
    &=
    \sum_{d_1\mid a}\sum_{d_2\mid b}
    f(d_1d_2)
    g\left(\dfrac{a}{d_1}\cdot\dfrac{b}{d_2}\right).
    \end{aligned}
    $$

    因为 $f,g$ 都是积性函数，并且对应两部分互质，所以上式等于

    $$
    \sum_{d_1\mid a}\sum_{d_2\mid b}
    f(d_1)f(d_2)
    g\left(\dfrac{a}{d_1}\right)
    g\left(\dfrac{b}{d_2}\right).
    $$

    将两重和拆开，得到

    $$
    (f*g)(ab)=(f*g)(a)(f*g)(b).
    $$

前面 Euler 函数的约数和

$$
\sum_{d\mid n}\varphi(d)=n
$$

正是

$$
\varphi * \mathbf 1=\operatorname{Id}
$$

的逐点展开。接下来 Möbius 函数的基本求和则会给出

$$
\mu * \mathbf 1=\varepsilon.
$$

### Möbius 函数

Möbius 函数 $\mu(n)$ 定义为

$$
\mu(n)=
\begin{cases}
1, & n=1,\\
0, & n\ \text{含有平方质因子},\\
(-1)^k, & n\ \text{是}\ k\ \text{个不同质数的乘积}.
\end{cases}
$$

例如 $\mu(6)=1$，$\mu(12)=0$，$\mu(30)=-1$。

???+ theorem "Möbius 函数的基本求和"

    对任意正整数 $n$，有

    $$
    \sum_{d\mid n}\mu(d)=
    \begin{cases}
    1,&n=1,\\
    0,&n>1.
    \end{cases}
    $$

    用 Dirichlet 卷积记号，也就是

    $$
    \mu * \mathbf 1=\varepsilon.
    $$

??? proof "证明"

    $n=1$ 时只有因数 $1$，结论显然。

    设 $n>1$ 含有 $k$ 个不同质因数。只有不含平方质因子的 $d$ 对求和有贡献，而这样的 $d$ 等价于从这 $k$ 个质因数中选出一个子集。选出 $i$ 个时共有 $\binom ki$ 种，贡献为 $(-1)^i$，所以

    $$
    \sum_{d\mid n}\mu(d)
    =
    \sum_{i=0}^k\binom ki(-1)^i
    =
    (1-1)^k
    =
    0.
    $$

???+ theorem "Möbius 反演"

    若两个定义在正整数上的函数 $F,f$ 满足

    $$
    F(n)=\sum_{d\mid n}f(d),
    $$

    则

    $$
    f(n)=\sum_{d\mid n}\mu(d)F\left(\dfrac{n}{d}\right).
    $$

??? proof "证明"

    用 Dirichlet 卷积的语言，条件就是

    $$
    F=f*\mathbf 1.
    $$

    因为 $\mu * \mathbf 1=\varepsilon$，这说明 $\mu$ 是 $\mathbf 1$ 在 Dirichlet 卷积下的逆元。所以两边同时卷上 $\mu$，由交换律和结合律可得

    $$
    F*\mu
    =
    (f*\mathbf 1)*\mu
    =
    f*(\mathbf 1*\mu)
    =
    f*\varepsilon
    =
    f.
    $$

    将其展开，便得到

    $$
    f(n)=\sum_{d\mid n}\mu(d)F\left(\dfrac{n}{d}\right).
    $$

    下面也可以直接按求和式验证。

    把 $F$ 的定义代入右侧，并令 $e$ 表示 $f$ 中的求和变量：

    $$
    \begin{aligned}
    \sum_{d\mid n}\mu(d)F\left(\dfrac{n}{d}\right)
    &=
    \sum_{d\mid n}\mu(d)\sum_{e\mid n/d}f(e)\\
    &=
    \sum_{e\mid n}f(e)\sum_{d\mid n/e}\mu(d).
    \end{aligned}
    $$

    根据上一条定理，内层和只有在 $n/e=1$，即 $e=n$ 时为 $1$，其余时候均为 $0$。因此整个式子只剩下 $f(n)$，反演公式得证。

## 小结

这一部分的逻辑关系可以概括为：带余除法建立同余；Euclid 算法导出 Bézout 定理，进而刻画逆元；简化剩余系在互质乘法下重新排列，从而得到 Euler 定理与 Fermat 小定理；算术基本定理把整数拆成质数幂，进而得到约数函数、Euler 函数和 Möbius 函数；最后利用 $\sum_{d\mid n}\mu(d)$ 的消去性质完成 Möbius 反演。
