# 线段树基础

线段树用于维护区间信息。它的核心并不是“树”这个形态，而是把一个大区间不断拆成左右两个子区间，使每个区间的信息都可以由两个子区间的信息合并得到。

设一个节点维护区间 $[l,r]$。若 $l=r$，它就是一个叶子；否则令：

$$
mid=\left\lfloor\dfrac{l+r}{2}\right\rfloor
$$

则左儿子维护 $[l,mid]$，右儿子维护 $[mid+1,r]$。

如果一个信息可以写成：

$$
\operatorname{Info}([l,r])
=
\operatorname{Merge}\left(\operatorname{Info}([l,mid]),\operatorname{Info}([mid+1,r])\right)
$$

那么就可以尝试使用线段树维护。

## 基本维护

先考虑最简单的区间和。每个节点维护三个东西：

- 当前节点对应的区间 $[l,r]$。
- 左右儿子的编号。
- 当前区间的和。

于是建树时，叶子直接读取原数组，非叶子递归建立左右儿子，再把两边的和加起来。

```cpp
#include <cstdio>
#define LSon Node[Now].LeftSon
#define RSon Node[Now].RightSon
#define MAXN 100010
using namespace std;
struct node{
    int l,r,LeftSon,RightSon;
    long long Val;
}Node[MAXN<<2];
long long Line[MAXN];
int cnt=0,n,m;
void Push_Up(int Now){
    Node[Now].Val=Node[LSon].Val+Node[RSon].Val;
}
int Build(int l,int r){
    int Now=++cnt;
    Node[Now].l=l;Node[Now].r=r;
    if(l==r){Node[Now].Val=Line[l];return Now;}
    int Mid=(l+r)>>1;
    LSon=Build(l,Mid);
    RSon=Build(Mid+1,r);
    Push_Up(Now);
    return Now;
}
```

这里数组通常开到 $4n$。这并不是说线段树真的有 $4n$ 个有用节点，而是堆式或递归式存储时可以用这个大小避免边界讨论。

## 区间查询

查询区间 $[L,R]$ 时，我们递归访问线段树上的节点。

- 如果当前节点区间完全包含在 $[L,R]$ 中，直接返回该节点的信息。
- 如果当前节点区间和 $[L,R]$ 没有交集，返回空信息。
- 否则继续递归左右儿子，再合并答案。

```cpp
long long Query(int Now,int l,int r){
    if(Node[Now].l>=l&&Node[Now].r<=r) return Node[Now].Val;
    else if(Node[Now].l>r||Node[Now].r<l) return 0;
    long long Ret=0;
    Ret+=Query(LSon,l,r);
    Ret+=Query(RSon,l,r);
    return Ret;
}
```

可以发现，一次区间查询会把询问区间拆成若干个线段树节点。每层至多访问常数个“边界节点”，所以复杂度为 $\mathcal{O}(\log n)$。

## 单点修改

单点修改比较直接。沿着根到对应叶子的路径递归下去，修改叶子后再一路向上重新合并。

```cpp
void Modify(int Now,int Pos,long long Val){
    if(Node[Now].l==Node[Now].r){
        Node[Now].Val=Val;
        return;
    }
    int Mid=(Node[Now].l+Node[Now].r)>>1;
    if(Pos<=Mid) Modify(LSon,Pos,Val);
    else Modify(RSon,Pos,Val);
    Push_Up(Now);
}
```

由于每一层只会进入一个儿子，所以单点修改的复杂度也是 $\mathcal{O}(\log n)$。

## 懒标记

如果要做区间修改，例如把 $[L,R]$ 中所有数加上 $x$，显然不能把所有叶子都改一遍。

考虑一个节点 $u$ 维护的区间 $[l,r]$。如果 $[l,r]$ 完全被修改区间包含，那么这一整段的和会增加：

$$
(r-l+1)x
$$

此时我们可以先只修改当前节点的信息，并记录一个标记：

$$
\operatorname{Tag}(u)\leftarrow \operatorname{Tag}(u)+x
$$

这个标记的含义是：这个节点的子区间还没有真正收到这次修改，之后如果要访问它的儿子，再把标记下放。

```cpp
void Add_Tag(int Now,long long Val){
    Node[Now].Val+=(Node[Now].r-Node[Now].l+1)*Val;
    Node[Now].Tag+=Val;
}
void Push_Down(int Now){
    if(Node[Now].Tag==0) return;
    Add_Tag(LSon,Node[Now].Tag);
    Add_Tag(RSon,Node[Now].Tag);
    Node[Now].Tag=0;
}
void Modify(int Now,int l,int r,long long Val){
    if(Node[Now].l>=l&&Node[Now].r<=r){
        Add_Tag(Now,Val);
        return;
    }
    else if(Node[Now].l>r||Node[Now].r<l) return;
    Push_Down(Now);
    Modify(LSon,l,r,Val);
    Modify(RSon,l,r,Val);
    Push_Up(Now);
}
long long Query(int Now,int l,int r){
    if(Node[Now].l>=l&&Node[Now].r<=r) return Node[Now].Val;
    else if(Node[Now].l>r||Node[Now].r<l) return 0;
    Push_Down(Now);
    return Query(LSon,l,r)+Query(RSon,l,r);
}
```

完整结构中需要在 `node` 里加入 `long long Tag;`。如果是区间赋值，则标记需要额外记录“是否存在赋值标记”，否则无法区分“赋值为 $0$”和“没有标记”。

## 标记复合

懒标记本质上是在维护区间修改之间的复合关系。

对于区间加，两个标记 $a,b$ 的复合仍然是加：

$$
x\mapsto x+a,\quad x\mapsto x+b
$$

连续作用后就是：

$$
x\mapsto x+a+b
$$

所以标记可以直接相加。

但如果同时有区间乘和区间加，标记就应该看成一次函数：

$$
x\mapsto ax+b
$$

两次标记复合时要注意顺序：

$$
(a_2x+b_2)\circ(a_1x+b_1)=a_2a_1x+a_2b_1+b_2
$$

这个视角会在[双半群模型](double-semigroup.md)中继续展开。

## 动态开点

如果值域很大，例如要维护 $[1,10^9]$ 上的点，但实际只会修改很少的位置，那么直接建完整线段树不合适。

动态开点的想法是：最开始只建立根节点，只有在递归进入某个子区间时才创建对应儿子。

```cpp
int NewNode(int l,int r){
    int Now=++cnt;
    Node[Now].l=l;Node[Now].r=r;
    Node[Now].LeftSon=Node[Now].RightSon=0;
    Node[Now].Val=0;
    return Now;
}
void Check(int Now){
    int Mid=(Node[Now].l+Node[Now].r)>>1;
    if(!LSon) LSon=NewNode(Node[Now].l,Mid);
    if(!RSon) RSon=NewNode(Mid+1,Node[Now].r);
}
void Modify(int Now,int Pos,long long Val){
    if(Node[Now].l==Node[Now].r){
        Node[Now].Val+=Val;
        return;
    }
    Check(Now);
    int Mid=(Node[Now].l+Node[Now].r)>>1;
    if(Pos<=Mid) Modify(LSon,Pos,Val);
    else Modify(RSon,Pos,Val);
    Push_Up(Now);
}
```

动态开点不会改变单次操作的 $\mathcal{O}(\log V)$ 复杂度，其中 $V$ 是值域大小。但它让空间复杂度和实际访问过的节点数相关，在权值线段树、可持久化线段树中比较常见。

## 常见维护对象

线段树并不只维护区间和。只要左右区间可以合并，就可以放进线段树里。

常见的维护对象包括：

- 区间和、区间最大值、区间最小值。
- 区间最大子段和，需要维护前缀最大和、后缀最大和、总和、答案。
- 区间矩阵乘积，需要注意乘法顺序。
- 区间函数复合，可以用矩阵或标记复合描述。
- 扫描线中的覆盖次数和覆盖长度。

因此写线段树时，应该先想清楚两件事：

1. 每个节点维护什么信息。
2. 左右儿子的信息如何合并。

如果还存在区间修改，则继续考虑：

1. 一个标记如何作用到节点信息上。
2. 两个标记如何复合。

这四件事确定后，线段树的代码通常只是把这些关系递归地写出来。
