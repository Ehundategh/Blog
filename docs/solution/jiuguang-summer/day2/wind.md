# 逐风

## 题目简述

给定周期为 $n$ 的风向序列。每天白天可以自行移动不超过 $k$ 的曼哈顿距离，傍晚会被当天的风推动。对于每组数据，要求最早在某天傍晚恰好到达目标点。

## 数据点 $1\sim 8$

这部分保证答案存在且不超过 $10^5$。

考虑枚举经过的天数 $t$。设前 $t$ 天的风一共使船只移动到 $(W_x(t),W_y(t))$，那么白天需要补充的位移为

$$
(x-W_x(t),y-W_y(t)).
$$

经过 $t$ 天，白天最多可以移动 $t\times k$ 的曼哈顿距离。因此，$t$ 天能够到达终点，当且仅当

$$
\lvert x-W_x(t)\rvert+\lvert y-W_y(t)\rvert\leq t\times k.
$$

从 $t=0$ 开始依次枚举，并直接模拟每天的风即可。由于答案不超过 $10^5$，时间复杂度为 $\mathcal{O}(n+\operatorname{Ans})$。

## 数据点 $9\sim 12$

这部分满足特殊性质，即每天风的曼哈顿距离都不超过 $k$。

沿用上一档部分分的判定条件。假设经过 $t$ 天可以到达终点，那么

$$
\lvert x-W_x(t)\rvert+\lvert y-W_y(t)\rvert\leq t\times k.
$$

从第 $t$ 天到第 $t+1$ 天，风带来的新增位移的曼哈顿距离不超过 $k$。根据三角不等式，有

$$
\begin{aligned}
&\lvert x-W_x(t+1)\rvert+\lvert y-W_y(t+1)\rvert\\
\leq{}&\lvert x-W_x(t)\rvert+\lvert y-W_y(t)\rvert+k\\
\leq{}&(t+1)k.
\end{aligned}
$$

所以，如果 $t$ 天可行，那么 $t+1$ 天也可行，判定具有单调性。预处理一个周期内的风位移前缀和后，可以二分最早的可行天数。

## 正解

一般情况下，单日风的位移可能超过 $k$，上一档部分分中的单调性不再成立，不能直接二分答案。

设一个完整周期的风位移为 $(S_x,S_y)$，前 $t$ 天的风位移为 $(P_x(t),P_y(t))$，其中 $1\leq t\leq n$。考虑答案除以 $n$ 后的余数对应 $t$，并设在这之前已经经过了 $q$ 个完整周期，那么经过的总天数为

$$
qn+t,
$$

风带来的总位移为

$$
(qS_x+P_x(t),qS_y+P_y(t)).
$$

令

$$
a=x-P_x(t),\qquad b=y-P_y(t),
$$

那么需要满足

$$
\lvert a-qS_x\rvert+\lvert b-qS_y\rvert\leq(qn+t)k.
$$

利用

$$
\lvert X\rvert+\lvert Y\rvert
=\max(X+Y,-X+Y,X-Y,-X-Y),
$$

可以将绝对值限制拆成下面四个关于 $q$ 的一次不等式：

$$
\begin{cases}
(nk+S_x+S_y)q\geq a+b-tk,\\
(nk-S_x+S_y)q\geq-a+b-tk,\\
(nk+S_x-S_y)q\geq a-b-tk,\\
(nk-S_x-S_y)q\geq-a-b-tk.
\end{cases}
$$

对于一个形如 $Aq\geq B$ 的不等式，并限制 $q$ 为非负整数：

- 若 $A>0$，可以得到 $q$ 的下界；
- 若 $A=0$，只需要判断该不等式是否恒成立；
- 若 $A<0$，可以得到 $q$ 的上界。

将四个不等式得到的上下界取交，若交集非空，取其中最小的 $q$，即可得到当前 $t$ 对应的最早时间。枚举 $1\leq t\leq n$，取所有合法时间的最小值即为答案。

特别地，$t=n$ 可以表示经过整数个完整周期的情况；而时间为 $0$ 的情况需要单独判断目标点是否为原点。

每个 $t$ 只需要处理四个一次不等式，因此每组数据的时间复杂度为 $\mathcal{O}(n)$，总时间复杂度为 $\mathcal{O}(\sum n)$。

## 参考代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const long long INF=1e18;
int T;
long long n,k,x,y,X[100010],Y[100010];
long long PreX,PreY,Ans=0,NowX,NowY;
void Deal(long long a,long long b,long long &Max,long long &Min){
    if (a==0&&b>0) {Max=0,Min=INF;}
    if (a>0&&b>0) {
        Min=max(Min,(a+b-1)/a);
    }
    if (a<0) {
        if (b>0) {Max=0,Min=INF;}
        else if (b==0) {Max=min(Max,0ll);Min=max(Min,0ll);}
        else Max=min(Max,b/a);
    }
    return;
}
long long Get(long long a,long long b,long long t) {
    long long Max=INF,Min=0;
    Deal(n*k+PreX+PreY,a+b-t*k,Max,Min);
    Deal(n*k-PreX+PreY,-a+b-t*k,Max,Min);
    Deal(n*k+PreX-PreY,a-b-t*k,Max,Min);
    Deal(n*k-PreX-PreY,-a-b-t*k,Max,Min);
    if (Max>=Min) return Min*n+t;
    else return INF;
}
void Solve() {
    PreX=PreY=NowX=NowY=0;Ans=INF;
    scanf("%lld%lld%lld%lld",&n,&k,&x,&y);
    for (int i=1;i<=n;i++) {
        scanf("%lld%lld",&X[i],&Y[i]);
        PreX+=1ll*X[i];
        PreY+=1ll*Y[i];
    }
    if (x==0&&y==0) {puts("0");return;}
    for (int i=1;i<=n;i++) {
        NowX+=1ll*X[i];
        NowY+=1ll*Y[i];
        Ans=min(Get(x-NowX,y-NowY,i),Ans);
    }
    if (Ans==INF) puts("-1");
    else printf("%lld\n",Ans);
    return;
}

int main() {
    freopen("wind.in","r",stdin);
    freopen("wind.out","w",stdout);
    scanf("%d",&T);
    while (T-->0) Solve();
    return 0;
}
```
