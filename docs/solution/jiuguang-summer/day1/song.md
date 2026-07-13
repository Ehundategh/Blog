# 流光之歌

## 题目简述

给定歌魔声音 $T$，以及 $n$ 个成员声音 $S_i$。每次询问给出一个不可用前缀长度 $l$，比较时需要忽略每段声音的前 $l$ 个字符，要求找出与歌魔声音最长公共前缀最大的成员编号，若有多个则输出编号最小者。

## 第一档部分分

首先可以设计一个简单暴力。

对于每个询问，直接把 $T$ 和每个 $S_i$ 的前 $l$ 个字符忽略，然后逐字符比较最长公共前缀。得到所有 $S_i$ 的相似程度后，取最大值，若相同则取编号最小的一个。

时间复杂度为：

$$
\mathcal{O}\left(q\times \left(\sum |S|+|T|\right)\right)
$$

可以通过较小的数据。

## 第二档部分分

考虑 $n=2$ 的情况。这个时候本质上只需要比较很少的字符串，但如果每次仍然逐字符比较，在长字符串上仍然会慢。

一般遇到字符串匹配问题，我们可以考虑 $\texttt{Hash}$。最长公共前缀具有单调性：若长度为 $x$ 的前缀相同，则所有更短的前缀也相同；若长度为 $x$ 的前缀不同，则所有更长的前缀也不同。

![忽略不可用前缀后，比较剩余后缀的最长公共前缀](/Blog/assets/solution/jiuguang-summer/day1/solution_lcp.svg)

于是对于每一对字符串，我们可以二分最长公共前缀长度，并用字符串哈希在 $\mathcal{O}(1)$ 时间内判断某个长度是否相同。

整体时间复杂度为：

$$
\mathcal{O}\left(\sum |S|+|T|+q\log \min(|S|,|T|)\right)
$$

这里的思想可以直接推广到正解。

## 正解一：直接 DP

本题还有一种更直接的写法。

对于一个固定的成员 $S_i$，令

$$
f_j=\operatorname{LCP}(T[j\ldots],S_i[j\ldots]).
$$

若 $T_j=S_{i,j}$，则

$$
f_j=f_{j+1}+1.
$$

否则 $f_j=0$。因此对于每个成员串，都可以从后往前扫一遍，直接得到它在所有不可用前缀长度下的匹配长度。

询问给出 $l$ 时，实际比较的是 $T[l+1\ldots]$ 与 $S_i[l+1\ldots]$。也就是说，当我们在处理位置 $j$ 时，它对应的不可用前缀长度就是 $j-1$。于是可以在预处理每个成员串时，顺手更新每个 $l$ 的最优成员编号。

按照成员编号从小到大处理，并且只在匹配长度严格更大时更新答案，就可以自然保证平局时取编号较小者。

时间复杂度为

$$
\mathcal{O}\left(\sum_i \min(|T|,|S_i|)+q\right),
$$

空间复杂度为 $\mathcal{O}(|T|)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 12
#define MAXL 2000010
using namespace std;
int n,q,StLen,Len,BestLen[MAXL],BestId[MAXL],a;
char T[MAXL],S[MAXL];
int main(){
    scanf("%s",T+1);
    StLen=strlen(T+1);
    scanf("%d%d",&n,&q);
    for(int i=0;i<=StLen;i++) BestId[i]=1;
    for(int i=1;i<=n;i++){
        scanf("%s",S+1);
        Len=strlen(S+1);
        int Lim=min(StLen,Len),Now=0;
        for(int j=Lim;j>=1;j--){
            if(T[j]==S[j]) Now++;
            else Now=0;
            if(Now>BestLen[j-1]){
                BestLen[j-1]=Now;
                BestId[j-1]=i;
            }
        }
    }
    while(q-->0){
        scanf("%d",&a);
        printf("%d\n",BestId[a]);
    }
    return 0;
}
```

## 正解二：Hash

本题中 $n$ 很小，最大只有 $10$，而总字符串长度和询问数较大。

我们可以预处理 $T$ 和所有 $S_i$ 的哈希。对于每个询问 $l$，枚举每一个 $S_i$，用二分加哈希求出忽略前 $l$ 个字符后的最长公共前缀长度。

设当前成员的匹配长度为 $Len_i$。我们取 $Len_i$ 最大的成员；如果有多个成员匹配长度相同，就取编号最小的成员。

由于每次询问只枚举 $n$ 个字符串，而 $n\leq 10$，所以可以通过所有数据。

时间复杂度为：

$$
\mathcal{O}\left(\sum |S|+|T|+qn\log \min(|S_i|,|T|)\right)
$$

## 正解三：后缀数组

也可以使用后缀数组完成本题。

首先把所有字符串拼接成一个长字符串，并在不同字符串之间加入互不相同或不会出现在原串中的分隔符。对这个长字符串求后缀数组和高度数组，再用 $\texttt{ST}$ 表维护区间高度数组最小值。

对于两个后缀，它们的最长公共前缀可以转化为后缀数组排名区间上的高度数组最小值。于是每次询问时，歌魔声音去掉前 $l$ 个字符后对应一个后缀，每个成员声音去掉前 $l$ 个字符后也对应一个后缀，二者的 $\texttt{LCP}$ 可以用一次区间最小值查询得到。

这样每次询问仍然枚举成员并取最大相似程度，时间复杂度为：

$$
\mathcal{O}\left((\sum |S|+|T|)\log(\sum |S|+|T|)+qn\right)
$$

实现上哈希做法更短，后缀数组做法可以避免哈希冲突，两种做法都可以通过本题。

## 参考代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 12
#define MAXL 2000010
const int Mod1=1e9+7;
const int Mod2=1e9+9;
const int Inv1=489437524;
const int Inv2=793611037;
const int p=20070903;
using namespace std;
int n,Length[MAXN],StLen,cns,q,Mark[MAXN],a;
char S[MAXL],In[MAXL];
class BKDRHash{
private:
    int Mod,Inv,Hash[MAXL<<1],P[MAXL<<1];
    inline int Calc(int a,int b){return (a+=b)<Mod?a:a-Mod;}
    inline int Mul(int a,int b){return 1ll*a*b%Mod;}
    inline int Del(int a,int b){return (a-=b)<0?a+Mod:a;}
public:
    void Init(int a,int b){
        Mod=a;Inv=b;
        P[0]=1;
        for(int i=1;i<=cns;i++){
            Hash[i]=Mul(Hash[i-1],p);
            P[i]=Mul(P[i-1],p);
            Hash[i]+=S[i];
        }
    }
    int Query(int Left,int Right){
        return Del(Hash[Right],Mul(Hash[Left-1],P[Right-Left+1]));
    }
}Hash1,Hash2;
bool Judge(int L1,int R1,int L2,int R2){
    int V11,V12,V21,V22;
    V11=Hash1.Query(L1,R1);
    V12=Hash2.Query(L1,R1);
    V21=Hash1.Query(L2,R2);
    V22=Hash2.Query(L2,R2);
    return (V11==V21&&V22==V12);
}
int Get_LCP(int x,int Pre){
    int L=0,R=min(StLen-Pre,Length[x]-Pre);
    while(L<R){
        int Mid=(L+R)>>1;
        if(Mid==L) Mid++;
        if(Judge(1+Pre,1+Mid+Pre-1,Mark[x]+Pre,Mark[x]+Mid+Pre-1)) L=Mid;
        else R=Mid-1;
    }
    return L;
}
int main(){
    scanf("%s",S+1);
    cns=strlen(S+1); StLen=cns;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%s",In+1);
        Length[i]=strlen(In+1);
        Mark[i]=cns+1;
        for(int j=1;j<=Length[i];j++){
            S[++cns]=In[j];
        }
    }
    Hash1.Init(Mod1,Inv1);
    Hash2.Init(Mod2,Inv2);
    while(q-->0){
        scanf("%d",&a);
        int Ans=1,MaxLen=0;
        for(int i=1;i<=n;i++){
            int NowLen=Get_LCP(i,a);
            if(NowLen>MaxLen){
                MaxLen=NowLen;
                Ans=i;
            }
        }
        printf("%d\n",Ans);
    }
    return 0;
}
```
