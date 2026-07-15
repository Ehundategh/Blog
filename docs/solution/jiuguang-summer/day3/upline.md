# 何以为我

## 题意简述

给定一个长度为 $n$ 的序列 $a_1,a_2,\cdots,a_n$，求满足 $i<j<k$ 且 $a_i<a_j<a_k$ 的三元组数量。

## 部分分

若 $n\leq 300$，直接枚举 $i,j,k$ 三重循环即可，时间复杂度为 $\mathcal{O}(n^3)$。

当 $n$ 增大以后，考虑一个合法三元组的中间位置 $j$。若我们知道左侧有多少个 $a_i<a_j$，右侧有多少个 $a_k>a_j$，那么以 $j$ 为中间项的贡献就是两者的乘积。

于是可以预处理：

- `SmallFront[j]`：在 $j$ 左侧且小于 $a_j$ 的元素个数；
- `SmallBack[j]`：在 $j$ 右侧且大于 $a_j$ 的元素个数。

若直接枚举顺序对，时间复杂度为 $\mathcal{O}(n^2)$。

## 正解

将顺序对计数交给树状数组维护。

从左到右扫描。扫描到 $i$ 时，树状数组中维护的是已经出现的数值出现次数，所以查询 `Line[i]-1` 的前缀和即可得到 `SmallFront[i]`。随后把 `Line[i]` 加入树状数组。

从右到左再扫描一次。扫描到 $i$ 时，树状数组中维护的是右侧已经出现的数值，查询总数减去不超过 `Line[i]` 的个数，即可得到 `SmallBack[i]`。

最后累加

$$
\sum_{i=1}^{n}\operatorname{SmallFront}(i)\operatorname{SmallBack}(i)
$$

即可。时间复杂度为 $\mathcal{O}(n\log V)$，其中 $V$ 为值域上界；空间复杂度为 $\mathcal{O}(n+V)$。答案需要使用 `long long`。

## 参考代码

```cpp
#include <cstdio>
#include <cstring>
#define MAXNUM 100010
#define MAXN 200010
using namespace std;
int Line[MAXN],SmallFront[MAXN],SmallBack[MAXN],n;
long long Ans=0;
struct SZSZ{
    int C[MAXNUM];
    int lowbit(int a){
        return a&(-a);
    }
    void Update(int x,int y){
        for(;x<MAXNUM;x+=lowbit(x)){
            C[x]+=y;
        }
        return;
    }
    void Init(){
        memset(C,0,sizeof(C));
    }
    int Query(int x){
        int ans=0;
        for(;x;x-=lowbit(x)){
            ans+=C[x];
        }
        return ans;
    }
}S1,S2;
int main(){
    freopen("upline.in","r",stdin);
    freopen("upline.out","w",stdout);
    memset(SmallFront,0,sizeof(SmallFront));
    memset(SmallBack,0,sizeof(SmallBack));
    scanf("%d",&n);
    S1.Init();
    S2.Init();
    for(int i=1;i<=n;i++){
        scanf("%d",&Line[i]);
        SmallFront[i]=S1.Query(Line[i]-1);
        S1.Update(Line[i],1);
    }
    for(int i=n;i>=1;i--){
        SmallBack[i]=S2.Query(MAXNUM)-S2.Query(Line[i]);
        S2.Update(Line[i],1);
    }
    for(int i=1;i<=n;i++){
        Ans+=1ll*SmallFront[i]*SmallBack[i];
    }
    printf("%lld",Ans);
    return 0;
}
```
