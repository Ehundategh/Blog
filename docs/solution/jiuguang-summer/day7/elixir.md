# 藿香正气液

## 题意简述

求满足 $1\le x<y\le n$ 且 $\gcd(x,y)=y-x$ 的整数对数量。

## Hint

令 $d=y-x$。条件变为 $\gcd(x,x+d)=d$，也就是 $d\mid x$。

??? note "提示"
    由于 $\gcd(x,x+d)=\gcd(x,d)$，要让它等于 $d$，等价于 $d\mid x$。

## 解法

令 $x=ad$，则 $y=(a+1)d$。只需要满足 $(a+1)d\le n$，即

$$
a\le \left\lfloor\dfrac{n}{d}\right\rfloor-1.
$$

于是固定 $d$ 的贡献为 $\left\lfloor\dfrac{n}{d}\right\rfloor-1$，并且 $d\le \left\lfloor\dfrac{n}{2}\right\rfloor$。答案为

$$
\sum_{d=1}^{\lfloor n/2\rfloor}\left(\left\lfloor\dfrac{n}{d}\right\rfloor-1\right).
$$

使用整除分块计算即可。

## 复杂度

整除分块的时间复杂度为 $\mathcal{O}(\sqrt n)$，空间复杂度为 $\mathcal{O}(1)$。

## 参考代码

[elixir.cpp](/Blog/assets/solution/jiuguang-summer/day7/std/elixir.cpp)
