# 星脉聚流光

## 题意简述

对于每个满足 $1\leq x\leq n$、$1\leq y\leq m$ 的整点 $(x,y)$，连接 $(0,0)$ 与 $(x,y)$。若线段内部经过 $k$ 个其他整点，则产生 $2k+1$ 的损失。求全部点的损失之和。

## Hint

??? tip "提示"
    线段 $(0,0)$ 到 $(x,y)$ 的内部整点数量为 $\gcd(x,y)-1$，因此单点贡献为 $2\gcd(x,y)-1$。问题转化为矩形中的最大公约数之和。

## 数据点 $1\sim 6$

从 $(0,0)$ 到 $(x,y)$ 的线段内部共有 $\gcd(x,y)-1$ 个整点，所以该点的传输损失为

$$
2(\gcd(x,y)-1)+1=2\gcd(x,y)-1.
$$

若 $\min(n,m)=1$，每个点的最大公约数均为 $1$，答案为 $\max(n,m)$。

若 $\min(n,m)=2$，记 $s=\max(n,m)$。第一行贡献为 $s$，第二行在另一个坐标为偶数时额外贡献 $2$，所以答案为

$$
2s+2\left\lfloor\dfrac{s}{2}\right\rfloor.
$$

## 数据点 $7\sim 12$

直接枚举全部 $n\times m$ 个点，使用辗转相除法计算 $\gcd(x,y)$，再累加 $2\gcd(x,y)-1$。

时间复杂度为 $\mathcal{O}(nm\log\min(n,m))$，空间复杂度为 $\mathcal{O}(1)$。这一做法的瓶颈是逐点处理，而最大公约数相同的点对可以放在一起统计。

## 数据点 $13\sim 19$

这一档满足 $n=m$。设

$$
\Phi(s)=\sum_{i=1}^{s}\varphi(i).
$$

在 $[1,s]^2$ 中，最大公约数为 $1$ 的有序点对数量为 $2\Phi(s)-1$。其中，对每个 $2\leq y\leq s$，满足 $1\leq x<y$ 且 $\gcd(x,y)=1$ 的 $x$ 有 $\varphi(y)$ 个；交换两个坐标得到另一半，最后补上点 $(1,1)$。

枚举最大公约数 $d$。将两个坐标同时除以 $d$ 后，最大公约数恰为 $d$ 的点对数量为

$$
2\Phi\left(\left\lfloor\dfrac{n}{d}\right\rfloor\right)-1.
$$

线性筛预处理 Euler 函数及其前缀和，再枚举 $d$ 计算贡献即可。

## 正解一：倍数容斥

令 $r=\min(n,m)$，定义 $f_d$ 为满足

$$
1\leq x\leq n,\qquad 1\leq y\leq m,\qquad \gcd(x,y)=d
$$

的有序点对数量。

两个坐标都能被 $d$ 整除的点对共有

$$
\left\lfloor\dfrac{n}{d}\right\rfloor
\left\lfloor\dfrac{m}{d}\right\rfloor
$$

个，其中还包含最大公约数为 $2d,3d,\ldots$ 的点对。因此从大到小枚举 $d$，有

$$
f_d=\left\lfloor\dfrac{n}{d}\right\rfloor
\left\lfloor\dfrac{m}{d}\right\rfloor
-\sum_{\substack{k\geq 2\\kd\leq r}}f_{kd}.
$$

枚举顺序保证右侧状态均已求出。每个点对按照其最大公约数恰好归入一个 $f_d$，所以递推不会遗漏，也不会重复。

记全部最大公约数之和为 $S$，则

$$
S=\sum_{d=1}^{r}d f_d.
$$

原问题的答案为

$$
2S-nm.
$$

内层枚举总次数为 $\sum_{d=1}^{r}\lfloor r/d\rfloor$。时间复杂度为 $\mathcal{O}(r\log r)$，空间复杂度为 $\mathcal{O}(r)$。

## 正解二：Möbius 反演

定义 $F(d)$ 为满足 $d\mid x$ 且 $d\mid y$ 的有序点对数量，定义 $f(d)$ 为最大公约数恰为 $d$ 的有序点对数量。于是

$$
F(d)=\left\lfloor\dfrac{n}{d}\right\rfloor
\left\lfloor\dfrac{m}{d}\right\rfloor
=\sum_{d\mid k}f(k).
$$

对倍数关系作 Möbius 反演，得到

$$
f(d)=\sum_{t=1}^{\lfloor r/d\rfloor}\mu(t)F(dt).
$$

交换求和顺序，并令 $k=dt$，有

$$
\begin{aligned}
S
&=\sum_{d=1}^{r}d f(d)\\
&=\sum_{k=1}^{r}F(k)\sum_{t\mid k}\mu(t)\dfrac{k}{t}.
\end{aligned}
$$

根据恒等式

$$
\varphi(k)=\sum_{t\mid k}\mu(t)\dfrac{k}{t},
$$

最终得到

$$
S=\sum_{k=1}^{r}\varphi(k)
\left\lfloor\dfrac{n}{k}\right\rfloor
\left\lfloor\dfrac{m}{k}\right\rfloor.
$$

线性筛预处理 Euler 函数后枚举 $k$，再输出 $2S-nm$。时间复杂度与空间复杂度均为 $\mathcal{O}(r)$。

## 参考代码

正式 STD 使用正解一。

[energy.cpp](/Blog/assets/solution/jiuguang-summer/day9/std/energy.cpp)
