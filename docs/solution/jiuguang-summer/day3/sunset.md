# 浮光掠影

## 题意简述

给定一个长度为 $n$ 的序列 $w$，支持两种操作：

- `M p c`：将 $w_p$ 修改为 $c$；
- `Q l r`：询问区间 $[l,r]$ 内非空连续子段和的最大值。

## 部分分

当 $n,m\leq 2000$ 时，修改时直接改变原数组，询问时在区间内跑一遍最大子段和即可，时间复杂度为 $\mathcal{O}(nm)$。

若序列在所有时刻均非负，那么区间最大子段和就是区间和。用树状数组维护单点赋值带来的差值，并查询区间和即可，时间复杂度为 $\mathcal{O}((n+m)\log n)$。

若负数位置很少，也可以维护负数位置，并在查询时枚举可能被负数切开的连续段。但这一做法本质上仍然是在利用最大子段和只需要维护少量断点的性质。

## 正解

考虑线段树维护区间信息。对于一个区间，需要维护：

- 区间总和；
- 最大前缀和；
- 最大后缀和；
- 最大子段和。

两个相邻区间合并时，跨过中点的最大子段和等于左区间最大后缀和加右区间最大前缀和，其余部分从左右儿子中取最大即可。

这份 Std 使用了等价的矩阵写法。对每个位置构造一个 max-plus 矩阵，表示经过这个元素时，状态之间的转移贡献。区间的信息就是这些矩阵按位置顺序相乘后的结果。线段树的节点维护对应区间的矩阵，单点修改时重构叶子矩阵，查询时按从左到右的顺序合并矩阵。

矩阵大小是常数，因此每次修改和查询都只会经过线段树上的 $\mathcal{O}(\log n)$ 个节点。总时间复杂度为 $\mathcal{O}((n+m)\log n)$，空间复杂度为 $\mathcal{O}(n)$。所有信息均需使用 `long long`。

## 参考代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LSon Node[Now].LeftS
#define RSon Node[Now].RightS
#define MAXN 200010
const long long INF=1ll<<60;
using namespace std;
int Line[MAXN],n,q;
class matrix{
    long long Num[4][4];
public:
    void Init(long long a){for(int i=1;i<=3;i++) for(int j=1;j<=3;j++) Num[i][j]=a;}
    matrix(){Init(-INF);}
    matrix(long long a){Init(a);}
    matrix operator*(const matrix &t) const{
        matrix ans;
        for(int i=1;i<=3;i++){
            for(int j=1;j<=3;j++){
                for(int k=1;k<=3;k++){
                    ans.Num[i][j]=max(ans.Num[i][j],Num[i][k]+t.Num[k][j]);
                }
            }
        }
        return ans;
    }
    void Modify(int a){
        Num[1][1]=Num[1][3]=Num[2][1]=Num[2][3]=a;
        Num[2][2]=Num[3][3]=0;
    }
    long long Back() const{return max(Num[2][1],Num[2][3]);}
};
class Segment_Tree{
    int cnt=0;
    struct node{
        matrix Value;
        int LeftS,RightS;
        int Left,Right;
    }Node[MAXN<<2];
public:
    int Build(int L,int R){
        int Now=++cnt;
        Node[Now].Left=L;Node[Now].Right=R;
        if(L==R){Node[Now].Value.Modify(Line[L]);return Now;}
        int Mid=(L+R)>>1;
        LSon=Build(L,Mid);
        RSon=Build(Mid+1,R);
        Node[Now].Value=Node[LSon].Value*Node[RSon].Value;
        return Now;
    }
    void Modify(int Now,int Pos,int Value){
        if(Node[Now].Left==Node[Now].Right){Node[Now].Value.Modify(Value);return;}
        else{
            if(Pos<=Node[LSon].Right) Modify(LSon,Pos,Value);
            else Modify(RSon,Pos,Value);
            Node[Now].Value=Node[LSon].Value*Node[RSon].Value;
        }
    }
    matrix Query(int Now,int Left,int Right){
        if( Node[Now].Left>=Left && Right>=Node[Now].Right )return Node[Now].Value;
        else{
            if(Node[LSon].Right>=Left&&Node[RSon].Left<=Right) return Query(LSon,Left,Right)*Query(RSon,Left,Right);
            else if(Node[LSon].Right>=Left) return Query(LSon,Left,Right);
            else return Query(RSon,Left,Right);
        }
    }
}T;
int main(){
    freopen("sunset.in","r",stdin);
    freopen("sunset.out","w",stdout);
    char Option[4];
    int In1,In2;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",&Line[i]);
    }
    T.Build(1,n);
    while(q-->0){
        scanf("%s%d%d",Option+1,&In1,&In2);
        if(Option[1]=='Q') printf("%lld\n",T.Query(1,In1,In2).Back());
        else T.Modify(1,In1,In2);
    }
    return 0;
}
```
