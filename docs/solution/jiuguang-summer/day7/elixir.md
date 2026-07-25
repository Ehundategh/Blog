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

## 推导

数据点较小时可以直接枚举 $(x,y)$ 并判断条件。令 $d=y-x$ 后，

$$
\gcd(x,y)=\gcd(x,x+d)=\gcd(x,d).
$$

所以条件等价于 $d\mid x$。写作 $x=td$ 后，$y=(t+1)d$，每个满足 $(t+1)d\le n$ 的正整数对 $(t,d)$ 都对应唯一合法数对，反之亦然；求和没有重复也没有遗漏。

## 复杂度

令 $q=\left\lfloor n/d\right\rfloor$，同一个 $q$ 对应的 $d$ 是一段连续区间，因此可以整除分块。时间复杂度为 $\mathcal{O}(\sqrt n)$，空间复杂度为 $\mathcal{O}(1)$；计数与乘法使用 `long long`。

## 参考代码

[elixir.cpp](/Blog/assets/solution/jiuguang-summer/day7/std/elixir.cpp)
