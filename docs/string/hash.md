# 字符串 Hash

字符串 Hash 用于把字符串映射到一个整数，从而快速判断两个字符串是否相同。

在算法题中，我们一般不把 Hash 当成严格证明，而是把它当成一个很方便的判等工具。常见做法是选取一个进制 $p$ 和模数 $\operatorname{Mod}$，并预处理前缀 Hash。

## 定义

设字符串为：

$$
s=s_1s_2\cdots s_n
$$

把每个字符映射为一个整数 $\operatorname{Val}(s_i)$。定义前缀 Hash 函数：

$$
\operatorname{PreHash}(i)
=
\left(\operatorname{PreHash}(i-1)p+\operatorname{Val}(s_i)\right)\bmod \operatorname{Mod}
$$

其中：

$$
\operatorname{PreHash}(0)=0
$$

于是整个字符串的 Hash 可以写成：

$$
\operatorname{Hash}(s)=\operatorname{PreHash}(n)
$$

这里的 $p$ 一般取一个素数，例如 $131,13331,20070903$ 等；$\operatorname{Mod}$ 也通常取一个大素数。

## 子串 Hash

对于子串 $s_l\cdots s_r$，它的 Hash 为：

$$
\operatorname{Hash}(s[l,r])
=
\operatorname{PreHash}(r)
-
\operatorname{PreHash}(l-1)p^{r-l+1}
\pmod{\operatorname{Mod}}
$$

实现时减法可能变成负数，所以需要补一次 $\operatorname{Mod}$。

```cpp
#include <cstdio>
#include <cstring>
#define MAXN 1000010
using namespace std;
const int Mod=1000000007;
const int p=131;
char S[MAXN];
int PreHash[MAXN],Pow[MAXN];
inline int Mul(int a,int b){return 1ll*a*b%Mod;}
inline int Del(int a,int b){return (a-=b)<0?a+Mod:a;}
void Build(){
    int Len=strlen(S+1);
    Pow[0]=1;
    for(int i=1;i<=Len;i++){
        Pow[i]=Mul(Pow[i-1],p);
        PreHash[i]=Mul(PreHash[i-1],p);
        PreHash[i]=(PreHash[i]+S[i])%Mod;
    }
}
int Query(int l,int r){
    return Del(PreHash[r],Mul(PreHash[l-1],Pow[r-l+1]));
}
```

如果两个子串长度相同，那么可以直接比较它们的 Hash 值。

```cpp
bool Same(int l1,int r1,int l2,int r2){
    return Query(l1,r1)==Query(l2,r2);
}
```

这就是字符串 Hash 最基本的用法。

## 双 Hash

单 Hash 可能发生冲突，所以在需要更稳妥的时候，我们通常维护两套 Hash。

设两个模数分别为 $\operatorname{Mod}_1,\operatorname{Mod}_2$，得到两个 Hash 函数：

$$
\operatorname{Hash}_1(s),\quad \operatorname{Hash}_2(s)
$$

判断两个字符串相同时，需要同时满足：

$$
\operatorname{Hash}_1(S)=\operatorname{Hash}_1(T)
$$

和：

$$
\operatorname{Hash}_2(S)=\operatorname{Hash}_2(T)
$$

代码上可以直接写成一个类，然后开两个对象。

```cpp
class BKDRHash{
private:
    int Mod,PreHash[MAXL],Pow[MAXL];
    inline int Mul(int a,int b){return 1ll*a*b%Mod;}
    inline int Del(int a,int b){return (a-=b)<0?a+Mod:a;}
public:
    void Init(int NowMod,char S[],int Len){
        Mod=NowMod;
        Pow[0]=1;
        for(int i=1;i<=Len;i++){
            Pow[i]=Mul(Pow[i-1],p);
            PreHash[i]=Mul(PreHash[i-1],p);
            PreHash[i]=(PreHash[i]+S[i])%Mod;
        }
    }
    int Query(int l,int r){
        return Del(PreHash[r],Mul(PreHash[l-1],Pow[r-l+1]));
    }
};
```

这样只需要再写一个 `Judge`，同时比较两套 Hash 即可。

```cpp
bool Judge(int l1,int r1,int l2,int r2){
    return Hash1.Query(l1,r1)==Hash1.Query(l2,r2)
        && Hash2.Query(l1,r1)==Hash2.Query(l2,r2);
}
```

## 应用一：统计不同字符串

[P3370 【模板】字符串哈希](https://www.luogu.com.cn/problem/P3370) 是最直接的 Hash 模板题。

???+ note "题目描述"

    给定 $n$ 个字符串，要求统计其中本质不同的字符串数量。

??? tip "Hint"

    如果两个字符串相同，那么它们的 $\operatorname{Hash}$ 值相同。因此可以把每个字符串的 Hash 值求出来，再排序去重。

??? success "解法"

    对每个字符串 $S_i$ 求：

    $$
    \operatorname{Hash}(S_i)
    $$

    然后把所有 Hash 值排序。排序后，相同的字符串会被放在一起，只需要统计相邻不同的段数即可。

    若担心冲突，可以把双 Hash 的两个值放进结构体中比较。

    ```cpp
    #include <cstdio>
    #include <cstring>
    #include <algorithm>
    #define MAXN 10010
    #define MAXL 1510
    using namespace std;
    const int Mod1=1000000007;
    const int Mod2=1000000009;
    const int p=13331;
    struct data{
        int x,y;
    }A[MAXN];
    bool operator<(data a,data b){
        if(a.x!=b.x) return a.x<b.x;
        return a.y<b.y;
    }
    bool operator==(data a,data b){
        return a.x==b.x&&a.y==b.y;
    }
    char S[MAXL];
    int n;
    int Calc(int Mod){
        int Ret=0,Len=strlen(S+1);
        for(int i=1;i<=Len;i++){
            Ret=(1ll*Ret*p+S[i])%Mod;
        }
        return Ret;
    }
    int main(){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%s",S+1);
            A[i]={Calc(Mod1),Calc(Mod2)};
        }
        sort(A+1,A+n+1);
        int Ans=0;
        for(int i=1;i<=n;i++){
            if(i==1||!(A[i]==A[i-1])) Ans++;
        }
        printf("%d",Ans);
        return 0;
    }
    ```

??? abstract "复杂度分析"

    设字符串总长度为 $L$。求 Hash 的复杂度为 $\mathcal{O}(L)$，排序复杂度为 $\mathcal{O}(n\log n)$。

## 应用二：二分最长公共前缀

Hash 经常和二分一起出现。

若要比较两个后缀 $s_l,s_r$ 的最长公共前缀，可以二分答案 $Len$，判断：

$$
\operatorname{Hash}(s[l,l+Len-1])
=
\operatorname{Hash}(s[r,r+Len-1])
$$

若相同，说明答案至少为 $Len$；否则答案小于 $Len$。

??? success "拼接字符串后的写法"

    如果有一个主串 $T$，以及若干个字符串 $S_i$，每次询问给出 $Pre$，要求比较跳过前 $Pre$ 个字符后的最长公共前缀，那么可以把所有字符串拼接到同一个大串中。

    设 $T$ 放在开头，$S_i$ 的起始位置为 $\operatorname{Mark}(i)$。那么比较 $T$ 与 $S_i$ 的前 $Len$ 位是否相同，只需要判断：

    $$
    \operatorname{Hash}(S[1+Pre,Pre+Len])
    =
    \operatorname{Hash}(S[\operatorname{Mark}(i)+Pre,\operatorname{Mark}(i)+Pre+Len-1])
    $$

    这就是之前代码中的 `Judge`。

    ```cpp
    int Get_LCP(int x,int Pre){
        int l=0,r=min(StLen-Pre,Length[x]-Pre);
        while(l<r){
            int Mid=(l+r)>>1;
            if(Mid==l) Mid++;
            if(Judge(1+Pre,1+Mid+Pre-1,Mark[x]+Pre,Mark[x]+Mid+Pre-1)) l=Mid;
            else r=Mid-1;
        }
        return l;
    }
    ```

    这里的 `Mark[x]` 表示第 $x$ 个字符串在拼接大串中的开头位置。由于所有字符串都在同一个数组中，所以判断两个子串是否相同只需要给出两段区间端点。

    每次询问枚举所有字符串，用 `Get_LCP` 得到对应的匹配长度，取最大值即可。

## 应用三：最长重复子串

[P2852 [USACO06DEC] Milk Patterns G](https://www.luogu.com.cn/problem/P2852) 可以用 Hash 配合二分处理。

???+ note "题目描述"

    给定一个长度为 $n$ 的序列，要求找出最长的子串长度，使得这个子串至少出现 $k$ 次。

??? tip "Hint"

    二分长度 $Len$。如果存在某个长度为 $Len$ 的子串出现至少 $k$ 次，那么答案至少为 $Len$。

??? success "解法"

    对序列同样可以做 Hash，只需要把每个数当作一个字符值即可。

    对于固定的 $Len$，枚举所有区间：

    $$
    [i,i+Len-1]
    $$

    求出它们的 Hash，排序后统计相同 Hash 连续出现的最大次数。若最大次数不小于 $k$，说明当前 $Len$ 可行。

    ```cpp
    bool Check(int Len){
        int Tot=0;
        for(int i=1;i+Len-1<=n;i++){
            A[++Tot]=Query(i,i+Len-1);
        }
        sort(A+1,A+Tot+1);
        int Cnt=1;
        for(int i=2;i<=Tot;i++){
            if(A[i]==A[i-1]) Cnt++;
            else Cnt=1;
            if(Cnt>=k) return true;
        }
        return k<=1;
    }
    ```

    外层再二分 $Len$ 即可。

??? abstract "复杂度分析"

    每次 `Check` 需要排序，复杂度为 $\mathcal{O}(n\log n)$；二分长度后总复杂度为 $\mathcal{O}(n\log^2 n)$。

## 应用四：字符串匹配

给定模式串 $T$ 和文本串 $S$，可以先算出：

$$
\operatorname{Hash}(T)
$$

然后枚举 $S$ 中所有长度为 $|T|$ 的子串，比较它们的 Hash。

```cpp
for(int i=1;i+LenT-1<=LenS;i++){
    if(Query(i,i+LenT-1)==HashT){
        printf("%d\n",i);
    }
}
```

这种做法的复杂度为 $\mathcal{O}(|S|+|T|)$。

## 应用五：回文判断

如果要判断一个子串是否为回文，可以对原串和反串分别预处理 Hash。

设原串为 $S$，反串为 $R$。对于 $S[l,r]$，它在反串中的对应区间为：

$$
R[n-r+1,n-l+1]
$$

于是判断：

$$
\operatorname{Hash}_S(l,r)
=
\operatorname{Hash}_R(n-r+1,n-l+1)
$$

即可得到该子串是否为回文。

若要找最长回文子串，可以枚举中心并二分半径，用 Hash 判断当前半径是否合法。

## 应用六：不同子串计数

如果只用 Hash，可以枚举所有长度 $Len$，把长度为 $Len$ 的所有子串 Hash 放入数组中排序去重。

答案为：

$$
\sum_{Len=1}^{n}
\left|\left\{
\operatorname{Hash}(s[i,i+Len-1])
\mid
1\le i\le n-Len+1
\right\}\right|
$$

这个做法比较直观，复杂度为 $\mathcal{O}(n^2\log n)$。若题目规模更大，通常使用[后缀数组](suffix-array.md)或后缀自动机。

## 关于冲突

Hash 存在冲突。也就是说，可能出现 $S\ne T$，但：

$$
\operatorname{Hash}(S)=\operatorname{Hash}(T)
$$

卡 Hash 的本质就是构造不同字符串使它们的 Hash 相同。这里不深入讨论构造方法，只需要知道：如果题目要求确定性正确，或者数据显然可能针对 Hash，就应该考虑 KMP、后缀数组、后缀自动机等确定性算法。

实际使用中，双 Hash 可以显著降低冲突概率。
