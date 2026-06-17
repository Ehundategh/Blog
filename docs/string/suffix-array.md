# 后缀数组

后缀数组用于把一个字符串的所有后缀按字典序排序。它常用于处理最长公共前缀、不同子串计数、重复子串等问题。

## 定义

设字符串为：

$$
s=s_1s_2\cdots s_n
$$

第 $i$ 个后缀为：

$$
s_i s_{i+1}\cdots s_n
$$

定义 $\operatorname{Sa}_i$ 表示字典序排名为 $i$ 的后缀起始位置，定义 $\operatorname{Rank}_i$ 表示起始位置为 $i$ 的后缀的排名。

也就是说：

$$
\operatorname{Rank}_{\operatorname{Sa}_i}=i
$$

## 倍增思路

一个直接做法是把所有后缀拿出来排序，但比较两个后缀最坏需要 $\mathcal{O}(n)$，总复杂度会比较高。

考虑倍增。我们先按长度为 $1$ 的前缀排序，也就是按单个字符排序。然后若已经知道所有后缀长度为 $k$ 的前缀排名，就可以用二元组：

$$
\left(\operatorname{Rank}_i,\operatorname{Rank}_{i+k}\right)
$$

表示从位置 $i$ 开始长度为 $2k$ 的前缀排名。

于是每一轮把 $k$ 翻倍：

$$
1,2,4,8,\ldots
$$

直到 $k\ge n$，所有后缀的顺序就确定了。

如果每一轮直接 `sort` 二元组，复杂度是 $\mathcal{O}(n\log^2 n)$。进一步注意到二元组的两个关键字都是排名，可以使用计数排序优化到每轮 $\mathcal{O}(n)$，总复杂度为 $\mathcal{O}(n\log n)$。

## $\mathcal{O}(n\log n)$ 求后缀数组

下面给出计数排序优化后的写法。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 1000010
using namespace std;
char S[MAXN];
int n,m,Sa[MAXN],Rank[MAXN],Second[MAXN],Temp[MAXN],Cnt[MAXN];
void Sort(){
    for(int i=0;i<=m;i++) Cnt[i]=0;
    for(int i=1;i<=n;i++) Cnt[Rank[i]]++;
    for(int i=1;i<=m;i++) Cnt[i]+=Cnt[i-1];
    for(int i=n;i>=1;i--) Sa[Cnt[Rank[Second[i]]]--]=Second[i];
}
void Get_SA(){
    m=127;
    for(int i=1;i<=n;i++){
        Rank[i]=S[i];
        Second[i]=i;
    }
    Sort();
    for(int k=1,p=0;p<n;k<<=1,m=p){
        p=0;
        for(int i=n-k+1;i<=n;i++) Second[++p]=i;
        for(int i=1;i<=n;i++){
            if(Sa[i]>k) Second[++p]=Sa[i]-k;
        }
        Sort();
        Temp[Sa[1]]=p=1;
        for(int i=2;i<=n;i++){
            int x=Sa[i],y=Sa[i-1];
            int X1=Rank[x],Y1=Rank[y];
            int X2=x+k<=n?Rank[x+k]:0;
            int Y2=y+k<=n?Rank[y+k]:0;
            if(X1==Y1&&X2==Y2) Temp[x]=p;
            else Temp[x]=++p;
        }
        for(int i=1;i<=n;i++) Rank[i]=Temp[i];
    }
}
int main(){
    scanf("%s",S+1);
    n=strlen(S+1);
    Get_SA();
    for(int i=1;i<=n;i++) printf("%d ",Sa[i]);
    return 0;
}
```

这段代码中，`Second` 表示这一轮排序中的第二关键字已经排好后的下标顺序。由于第一关键字是 `Rank`，再对 `Second` 按 `Rank` 做一次计数排序，就得到了二元组排序结果。

[P3809 【模板】后缀排序](https://www.luogu.com.cn/problem/P3809) 可以直接使用这份代码。

## 高度数组

定义：

$$
\operatorname{LCP}(i,j)
$$

表示起始位置为 $i,j$ 的两个后缀的最长公共前缀长度。

高度数组定义为：

$$
\operatorname{Height}_i
=
\operatorname{LCP}(\operatorname{Sa}_i,\operatorname{Sa}_{i-1})
$$

并令：

$$
\operatorname{Height}_1=0
$$

也就是说，$\operatorname{Height}_i$ 表示排名相邻的两个后缀的最长公共前缀。

### 求解

有一个重要性质：

$$
\operatorname{Height}_{\operatorname{Rank}_i}
\ge
\operatorname{Height}_{\operatorname{Rank}_{i-1}}-1
$$

考虑从 $i-1$ 开始的后缀和它排名前一个的后缀。若它们有长度为 $k$ 的公共前缀，那么删去第一个字符后，从 $i$ 开始的后缀至少还能保留长度 $k-1$ 的公共前缀。虽然它排名前一个的后缀可能变化，但最优的相邻比较不会更差到低于这个下界。

因此在求 $\operatorname{Height}_{\operatorname{Rank}_i}$ 时，可以从上一次的长度减一开始继续拓展。

```cpp
int Height[MAXN];
void Get_Height(){
    for(int i=1,k=0;i<=n;i++){
        if(Rank[i]==1) continue;
        if(k) k--;
        int j=Sa[Rank[i]-1];
        while(i+k<=n&&j+k<=n&&S[i+k]==S[j+k]) k++;
        Height[Rank[i]]=k;
    }
}
```

每次 $k$ 最多增加 $n$ 次，也最多减少 $n$ 次，所以总复杂度为 $\mathcal{O}(n)$。

## 应用一：字符加密

[P4051 [JSOI2007] 字符加密](https://www.luogu.com.cn/problem/P4051) 是后缀数组的一个经典应用。

???+ note "题目描述"

    给定一个字符串，考虑它的所有循环同构串，按字典序排序后输出每个循环同构串的最后一个字符。

??? tip "Hint"

    把原串复制一遍，循环同构串就可以看作新串中的一个长度为 $n$ 的子串。

??? success "解法"

    设原串为 $S$，构造：

    $$
    T=S+S
    $$

    对 $T$ 求后缀数组。按照后缀排名从小到大遍历 $\operatorname{Sa}_i$，若 $\operatorname{Sa}_i\le n$，则它对应一个循环同构串。

    对于起点为 $x$ 的循环同构串，其最后一个字符位置为：

    $$
    x+n-1
    $$

    因此输出 $T[x+n-1]$ 即可。

??? abstract "复杂度分析"

    构造长度为 $2n$ 的字符串并求后缀数组，时间复杂度为 $\mathcal{O}(n\log n)$。

## 应用二：不同子串数量

[SP32951 ADASTRNG - Ada and Substring](https://www.luogu.com.cn/problem/SP32951) 可以用高度数组解决。

???+ note "题目描述"

    给定一个字符串，求不同子串的数量。

??? tip "Hint"

    每个后缀能贡献若干个以它为开头的子串，但和前一个后缀的公共前缀部分已经出现过。

??? success "解法"

    对于起点为 $\operatorname{Sa}_i$ 的后缀，它一共能产生：

    $$
    n-\operatorname{Sa}_i+1
    $$

    个前缀子串。

    其中前 $\operatorname{Height}_i$ 个已经在排名前一个后缀中出现过，所以新增贡献为：

    $$
    n-\operatorname{Sa}_i+1-\operatorname{Height}_i
    $$

    因此答案为：

    $$
    \sum_{i=1}^{n}
    \left(n-\operatorname{Sa}_i+1-\operatorname{Height}_i\right)
    $$

??? abstract "复杂度分析"

    求后缀数组和高度数组后线性统计，时间复杂度为 $\mathcal{O}(n\log n)$。

## 应用三：最长重复子串

[UVA1223 Editor](https://www.luogu.com.cn/problem/UVA1223) 可以用高度数组处理。

???+ note "题目描述"

    给定字符串，求最长的重复子串长度。

??? tip "Hint"

    如果两个后缀有公共前缀，那么这个公共前缀就是一个重复出现的子串。

??? success "解法"

    任意两个后缀的最长公共前缀，会出现在它们排名区间上的 $\operatorname{Height}$ 最小值中。对于只要求最长重复子串的情况，只需要取相邻后缀的最大公共前缀即可：

    $$
    \max_{2\le i\le n}\operatorname{Height}_i
    $$

    若要求某个子串至少出现 $k$ 次，则可以在 $\operatorname{Height}$ 上看连续 $k-1$ 个位置的最小值，并取最大值。

??? abstract "复杂度分析"

    求出后缀数组和高度数组后，扫描一遍即可，时间复杂度为 $\mathcal{O}(n\log n)$。

## 小结

后缀数组的核心是把后缀排序。排序后，许多字符串问题都会变成相邻后缀之间的最长公共前缀问题。

通常需要记住三个数组：

- $\operatorname{Sa}_i$：排名为 $i$ 的后缀起点。
- $\operatorname{Rank}_i$：起点为 $i$ 的后缀排名。
- $\operatorname{Height}_i$：$\operatorname{Sa}_i$ 与 $\operatorname{Sa}_{i-1}$ 的最长公共前缀。

有了这三个数组，就可以处理不同子串数量、最长重复子串、循环同构排序以及更多区间 $\operatorname{LCP}$ 问题。
