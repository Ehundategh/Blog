# 引力之阱

## 题目简述

给出 $n+1$ 个 $n$ 维点及其到某个未知点的距离平方，求这个未知点的坐标。

## $32$ 分

这部分 $n\leq3$，且保证答案坐标均为整数，满足 $-30\leq x_i\leq30$。

根据题目描述，对于每个探测器 $i$，合法的答案都需要满足

$$
\sum_{j=1}^{n}(x_j-a_{i,j})^2=d_i.
$$

因此，可以直接枚举每一维坐标 $x_i$，再检查枚举出的点是否满足全部 $n+1$ 个等式。枚举的状态数不超过 $61^3$，可以通过这部分数据。

## $64$ 分

这部分满足特殊性质。设第 $i+1$ 个探测器的第 $i$ 维坐标为 $c_i$。

由于第 $1$ 个探测器位于原点，有

$$
d_1=\sum_{j=1}^{n}x_j^2.
$$

第 $i+1$ 个探测器只有第 $i$ 维坐标不为 $0$，因此

$$
d_{i+1}=(x_i-c_i)^2+\sum_{j\ne i}x_j^2.
$$

将两个式子相减，可以得到

$$
d_{i+1}-d_1=c_i^2-2c_ix_i,
$$

于是

$$
x_i=\dfrac{d_1+c_i^2-d_{i+1}}{2c_i}.
$$

对每一维分别计算即可。更重要的是，这部分启发我们：将两个距离平方的等式相减，可以消去所有未知数的平方项。

## 正解

回到第一档部分分中的等式。对于任意 $2\leq i\leq n+1$，将第 $i$ 个探测器对应的等式减去第 $1$ 个探测器对应的等式：

$$
\sum_{j=1}^{n}(x_j-a_{i,j})^2-
\sum_{j=1}^{n}(x_j-a_{1,j})^2=d_i-d_1.
$$

展开后所有 $x_j^2$ 都会被消去。整理得到

$$
2\sum_{j=1}^{n}(a_{i,j}-a_{1,j})x_j
=d_1-d_i+\sum_{j=1}^{n}(a_{i,j}^2-a_{1,j}^2).
$$

对于每个 $2\leq i\leq n+1$ 建立一个方程，就得到了一个包含 $n$ 个未知数和 $n$ 个方程的线性方程组，使用高斯消元求解即可。

题目保证答案唯一，因此高斯消元过程中一定能够找到非零主元。输出时保留三位小数即可。

为了避免浮点误差导致输出 `-0.000`，若某一维答案的绝对值小于 $0.0005$，应当先将其输出为 $0.000$。

## 复杂度

建立方程组的时间复杂度为 $\mathcal{O}(n^2)$，高斯消元的时间复杂度为 $\mathcal{O}(n^3)$，空间复杂度为 $\mathcal{O}(n^2)$。

## 参考代码

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
double A[18];
double Num[18][18],In1;

int main(){
    freopen("escape.in","r",stdin);
    freopen("escape.out","w",stdout);
    memset(Num,0,sizeof(Num));
    scanf("%d",&n);
    for (int i=1;i<=n+1;i++) {
        scanf("%lf",&A[i]);
    }
    for (int i=1;i<=n;i++) {
        for (int j=1;j<=n;j++) {
            scanf("%lf",&In1);
            Num[i][j]=-2*In1+2*A[j];
            Num[i][n+1]-=In1*In1-A[j]*A[j];
        }
        scanf("%lf",&In1);
        Num[i][n+1]+=In1-A[n+1];
    }
    for(int i=1;i<=n;i++){
        if(fabs(Num[i][i])<1e-8){
            for(int j=i+1;j<=n;j++){
                if(fabs(Num[j][i])>1e-8){
                    for(int k=1;k<=n+1;k++) swap(Num[j][k],Num[i][k]);
                    break;
                }
            }
        }
        double Temp=Num[i][i];
        for(int j=i;j<=n+1;j++) Num[i][j]/=Temp;
        for(int j=1;j<=n;j++){
            if(j==i) continue;
            double Times=Num[j][i]/Num[i][i];
            for(int k=1;k<=n+1;k++){
                Num[j][k]-=Num[i][k]*Times;
            }
        }
    }
    for (int i=1;i<=n;i++) {
        if (fabs(Num[i][n+1])<0.0005) printf("0.000 ");
        else printf("%.3lf ",Num[i][n+1]);
    }
    return 0;
}
```
