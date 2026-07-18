# 我流奥义

## 题意简述

平面上有若干灌木丛，烟雾从原点向所有方向扩散到半径 $r$。同一条从原点出发的射线上只会标记最近的灌木丛；若原点本身有灌木丛，则只标记原点。求被标记的数量。

## 部分分

对于任意两个非零点，若叉积为 $0$ 且点积为正，则它们在同一条有向射线上。直接两两比较可以完成去重，但复杂度为 $\mathcal{O}(n^2)$。

## 正解

只保留距离不超过 $r$ 的点。若出现原点，答案立即为 $1$。否则把每个点 $(x,y)$ 除以 $\gcd(|x|,|y|)$，得到这条有向射线的最简整数表示。对所有最简整数对排序后统计不同对数，即为被烟雾第一次碰到的方向数量。

## 复杂度

每个点做一次标准化，排序复杂度为 $\mathcal{O}(n\log n)$。距离平方需要使用 `long long`。

## 参考代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n,In1,In2,r,T;
struct point{
    int x,y;
}Point[1000010];

bool cmp(point a,point b){
    if(a.x==b.x) return a.y<b.y;
    return a.x<b.x;
}

void Solve(){
    int Count=0;bool Tag=1;
    scanf("%d%d",&n,&r);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&In1,&In2);
        if(1ll*In1*In1+1ll*In2*In2>1ll*r*r){
            i--,n--;
            continue;
        }
        if(In1==0&&In2==0){Tag=0;i--,n--;continue;}
        int Gcd=__gcd(abs(In1),abs(In2));
        In1/=Gcd;In2/=Gcd;
        Point[i]={In1,In2};
    }
    if (!Tag) {puts("1");return;}
    sort(Point+1,Point+n+1,cmp);
    for(int i=1;i<=n;i++){
        if((Point[i].x!=Point[i-1].x||Point[i].y!=Point[i-1].y)||(i==1)) Count++;
    }
    printf("%d\n",Count);
    return;
}

int main() {
    freopen("smoke.in","r",stdin);
    freopen("smoke.out","w",stdout);
    scanf("%d",&T);
    while (T-->0) {Solve();}
    return 0;
}
```
