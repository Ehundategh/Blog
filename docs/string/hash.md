# 字符串 Hash

字符串 Hash 的目标是把一个字符串映射成一个数，使得两个字符串相等时，它们的 Hash 值一定相等；两个字符串不相等时，它们的 Hash 值尽可能不同。

在算法题中，它通常用于快速判断两个子串是否相同。我们不把它当成严格的判等证明，而是把它当成一种很方便的随机化判等工具。

## 定义

设字符串为：

$$
s=s_1s_2\cdots s_n
$$

取一个进制 $B$ 和模数 $P$，把字符映射成整数 $\operatorname{val}(s_i)$。定义：

$$
\operatorname{Hash}(s)
=
\sum_{i=1}^{n}\operatorname{val}(s_i)B^{n-i}\pmod P
$$

也可以递推地写成：

$$
H_i=(H_{i-1}B+\operatorname{val}(s_i))\bmod P
$$

其中 $H_i=\operatorname{Hash}(s_1s_2\cdots s_i)$。

这样做的好处是，若我们预处理所有前缀 Hash 和 $B$ 的幂，就可以在 $\mathcal{O}(1)$ 的时间求出任意子串的 Hash。

## 子串 Hash

设 $H_i$ 表示前 $i$ 个字符的 Hash，且 $H_0=0$。那么子串 $s_l\cdots s_r$ 的 Hash 为：

$$
\operatorname{Hash}(s[l,r])
=
H_r-H_{l-1}B^{r-l+1}
\pmod P
$$

实现时要注意减法可能得到负数，所以通常再加一次 $P$。

```cpp
#include <cstdio>
#include <cstring>
#define MAXN 1000010
using namespace std;
const long long Mod=1000000007;
const long long Base=131;
char S[MAXN];
long long H[MAXN],Pow[MAXN];
void Build(){
    int Len=strlen(S+1);
    Pow[0]=1;
    for(int i=1;i<=Len;i++){
        Pow[i]=Pow[i-1]*Base%Mod;
        H[i]=(H[i-1]*Base+S[i])%Mod;
    }
}
long long GetHash(int l,int r){
    return (H[r]-H[l-1]*Pow[r-l+1]%Mod+Mod)%Mod;
}
```

之后判断两个等长子串是否相同，只需要比较它们的 Hash 值。

```cpp
bool Same(int l1,int r1,int l2,int r2){
    return GetHash(l1,r1)==GetHash(l2,r2);
}
```

## 最长公共前缀

Hash 经常和二分放在一起使用。

例如要比较两个后缀 $s_l,s_r$ 的最长公共前缀长度。我们可以二分长度 $Len$，判断：

$$
\operatorname{Hash}(s[l,l+Len-1])
=
\operatorname{Hash}(s[r,r+Len-1])
$$

如果相同，说明答案至少为 $Len$；否则答案小于 $Len$。因此一次最长公共前缀查询可以在 $\mathcal{O}(\log n)$ 的时间完成。

这一点在很多题中很有用。比如两个字符串逐字符比较会很慢，但“前 $Len$ 位是否相同”这个问题可以通过 Hash 快速回答，于是最长公共前缀就变成了二分。

??? success "拼接字符串后二分 LCP"

    如果有一个主串 $T$，以及若干个字符串 $S_i$，每次询问要比较跳过前 $Pre$ 个字符后的最长公共前缀，那么可以把所有字符串拼接到一个大串中。

    设 $T$ 放在大串开头，$S_i$ 在大串中的起始位置为 $\operatorname{Mark}(i)$。那么比较 $T$ 和 $S_i$ 跳过前 $Pre$ 个字符后的前 $Len$ 位是否相同，只需要判断：

    $$
    \operatorname{Hash}(S[1+Pre,Pre+Len])
    =
    \operatorname{Hash}(S[\operatorname{Mark}(i)+Pre,\operatorname{Mark}(i)+Pre+Len-1])
    $$

    可以发现，$Len$ 具有单调性。若长度为 $Len$ 的前缀相同，那么更短的前缀一定相同；若长度为 $Len$ 的前缀不同，那么更长的前缀一定不同。于是直接二分 $Len$。

    下面是一个双 Hash 的写法。这里两个模数分别维护一遍前缀 Hash，判断相等时同时比较两者。

    ```cpp
    #include <cstdio>
    #include <cstring>
    #include <algorithm>
    #define MAXN 110
    #define MAXL 200010
    const int Mod1=1e9+7;
    const int Mod2=1e9+9;
    const int p=20070903;
    using namespace std;
    int n,Length[MAXN],StLen,cns,q,Mark[MAXN],a;
    char S[MAXL],In[MAXL];
    class BKDRHash{
    private:
        int Mod,Hash[MAXL<<1],P[MAXL<<1];
        inline int Mul(int a,int b){return 1ll*a*b%Mod;}
        inline int Del(int a,int b){return (a-=b)<0?a+Mod:a;}
    public:
        void Init(int a){
            Mod=a;
            P[0]=1;
            for(int i=1;i<=cns;i++){
                Hash[i]=Mul(Hash[i-1],p);
                P[i]=Mul(P[i-1],p);
                Hash[i]=(Hash[i]+S[i])%Mod;
            }
        }
        int Query(int Left,int Right){
            return Del(Hash[Right],Mul(Hash[Left-1],P[Right-Left+1]));
        }
    }Hash1,Hash2;
    bool Judge(int L1,int R1,int L2,int R2){
        return Hash1.Query(L1,R1)==Hash1.Query(L2,R2)
            && Hash2.Query(L1,R1)==Hash2.Query(L2,R2);
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
    ```

    这段代码中，`Query(Left,Right)` 对应的就是 $\operatorname{Hash}(S[Left,Right])$。由于所有字符串被拼接在同一个数组 `S` 中，所以 `Judge` 只需要接收两段区间端点即可。

    对于每次询问，枚举每一个 $S_i$，调用 `Get_LCP(i,Pre)` 求出对应的最长公共前缀长度，再取最大值即可。若题目要求编号最小，则只在严格变大时更新答案。

    预处理复杂度为 $\mathcal{O}(\sum |S_i|+|T|)$，每次比较一个字符串需要 $\mathcal{O}(\log |S_i|)$，因此若每次询问枚举全部字符串，总复杂度为：

    $$
    \mathcal{O}\left(qn\log L+\sum |S_i|+|T|\right)
    $$

## 字符串匹配

给定模式串 $T$ 和文本串 $S$，如果只要求完全匹配，可以先算出：

$$
\operatorname{Hash}(T)
$$

然后枚举 $S$ 中所有长度为 $|T|$ 的子串，比较它们的 Hash 即可。

这种做法的复杂度为：

$$
\mathcal{O}(|S|+|T|)
$$

其中预处理 $S$ 的前缀 Hash 需要 $\mathcal{O}(|S|)$，枚举所有起点也只需要线性时间。

## 回文判断

如果要判断一个子串是否为回文，可以对原串和反串分别做 Hash。

设原串为 $S$，反串为 $R$。对于 $S[l,r]$，它在反串中的对应位置是：

$$
R[n-r+1,n-l+1]
$$

于是只需要判断：

$$
\operatorname{Hash}_S(l,r)
=
\operatorname{Hash}_R(n-r+1,n-l+1)
$$

这样就可以 $\mathcal{O}(1)$ 判断一个子串是否为回文。

进一步地，若要找最长回文子串，可以枚举中心并二分半径；也可以在一些题里用 Hash 作为判定条件配合其他单调性。

## 不同子串计数

考虑统计一个字符串中有多少个不同子串。

一个直接的做法是枚举长度 $Len$，再枚举所有长度为 $Len$ 的子串，把它们的 Hash 值放入集合中。对于固定长度，集合大小就是不同子串个数。

于是答案为：

$$
\sum_{Len=1}^{n}
\left|\left\{
\operatorname{Hash}(s[i,i+Len-1])
\mid
1\le i\le n-Len+1
\right\}\right|
$$

这个做法复杂度为 $\mathcal{O}(n^2\log n)$，不一定是最优做法，但作为 Hash 的应用非常直观。

如果题目规模更大，通常会考虑后缀数组、后缀自动机等更稳定的数据结构。

## 关于冲突

Hash 存在冲突。也就是说，可能出现 $S\ne T$，但：

$$
\operatorname{Hash}(S)=\operatorname{Hash}(T)
$$

因此在正式比赛中，一般会使用双 Hash 或更换模数、进制来降低出错概率。

所谓卡 Hash，主要就是构造不同字符串让它们的 Hash 值相同。实际写题时不需要把构造方法研究得太深，但应该知道：单模数 Hash 并不是严格判等。如果题目明确需要确定性做法，或者数据很容易针对 Hash，就要考虑 KMP、后缀数组、后缀自动机等算法。

## 常见应用

Hash 常见于下面几类题：

- 判断两个子串是否相同。
- 配合二分求最长公共前缀。
- 字符串匹配。
- 回文判定。
- 统计不同子串数量。
- 比较拼接、循环同构、前后缀关系。

它的优点是实现短、适配性强；缺点是存在冲突。因此使用时要先判断题目是否允许这种风险，再决定是否使用双 Hash 或确定性算法。
