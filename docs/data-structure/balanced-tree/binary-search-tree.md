# 二叉搜索树

二叉搜索树，简称 BST。对于树中任意节点 $u$，其左子树中所有节点的权值均小于 $operatorname{Value}(u)$，右子树中所有节点的权值均大于 $operatorname{Value}(u)$。

当相同权值可能出现多次时，我们不必建立多个节点，只需要令 $operatorname{Count}(u)$ 表示权值 $operatorname{Value}(u)$ 的出现次数。再令：

$$
\operatorname{Size}(u)
=
\operatorname{Size}(\operatorname{LeftSon}(u))
+
\operatorname{Size}(\operatorname{RightSon}(u))
+
\operatorname{Count}(u)
$$

即可处理排名与第 $k$ 小。

## 节点定义

```cpp
struct node{
    int LeftSon,RightSon,Father;
    int Value,Count,Size;
}Node[MAXN];

void Update(int Now){
    Node[Now].Size=Node[Node[Now].LeftSon].Size
                  +Node[Node[Now].RightSon].Size
                  +Node[Now].Count;
}
```

$0$ 号节点表示空节点，并约定 $operatorname{Size}(0)=0$。`Father` 对普通二叉搜索树并不是必需的，但它可以让旋转和向上更新写得更直接。

## 查找与插入

从根节点开始比较待查权值 $x$ 与当前节点权值：

- 若 $x$ 更小，则进入左子树；
- 若 $x$ 更大，则进入右子树；
- 若二者相等，则查找结束。

插入同理。若遇到相同权值，只增加当前节点的 `Count`；若走到空节点，则在对应位置建立新节点。

普通二叉搜索树一次操作的复杂度为 $mathcal{O}(h)$，其中 $h$ 是当前树高。若插入序列有序，则 $h$ 可能达到 $n$。

## 排名与第 k 小

查询权值 $x$ 的排名时，从根节点开始：

- 若 $x<\operatorname{Value}(u)$，答案一定在左子树；
- 否则，左子树中的所有数都小于等于当前搜索边界，应将 $operatorname{Size}(\operatorname{LeftSon}(u))$ 加入答案；
- 若 $x=\operatorname{Value}(u)$，此时即可返回；否则再加入 $operatorname{Count}(u)$ 并进入右子树。

查询第 $k$ 小时反过来判断。令 $s=\operatorname{Size}(\operatorname{LeftSon}(u))$：

- 若 $k\le s$，进入左子树；
- 若 $s<k\le s+\operatorname{Count}(u)$，答案就是当前节点；
- 否则令 $k\leftarrow k-s-\operatorname{Count}(u)$，进入右子树。

## 前驱与后继

权值 $x$ 的前驱是严格小于 $x$ 的最大权值。查找时，若当前节点权值小于 $x$，它可以作为候选答案，并继续进入右子树；否则进入左子树。

后继同理：若当前节点权值大于 $x$，记录候选答案并进入左子树；否则进入右子树。

## 删除

先找到待删除节点 $u$。

1. 若 $operatorname{Count}(u)>1$，只需将其减一。
2. 若 $u$ 至多有一个非空儿子，直接用这个儿子替换 $u$。
3. 若 $u$ 同时有两个儿子，在右子树中找到权值最小的节点 $v$。将 $v$ 的权值与出现次数移到 $u$，再删除 $v$。由于 $v$ 没有左儿子，问题就转化成了上一种情况。

## 左旋与右旋

旋转只改变局部父子关系，不改变中序遍历，因此旋转后的树仍然是二叉搜索树。

考虑节点 $x$ 与父亲 $y$。若 $x$ 是 $y$ 的左儿子，将 $x$ 提到 $y$ 的位置就是右旋，也称 `Zig`；若 $x$ 是 $y$ 的右儿子，则对应左旋，也称 `Zag`。

右旋时，$x$ 的右子树需要接到 $y$ 的左侧；左旋完全对称。连接完成后，先更新原父亲，再更新新父亲。

```cpp
void Zig(int Now){
    int Father=Node[Now].Father,Grand=Node[Father].Father;
    Node[Father].LeftSon=Node[Now].RightSon;
    if(Node[Now].RightSon) Node[Node[Now].RightSon].Father=Father;
    Node[Now].RightSon=Father;
    Node[Father].Father=Now;
    Node[Now].Father=Grand;
    if(!Grand) Root=Now;
    else if(Node[Grand].LeftSon==Father) Node[Grand].LeftSon=Now;
    else Node[Grand].RightSon=Now;
    Update(Father);Update(Now);
}

void Zag(int Now){
    int Father=Node[Now].Father,Grand=Node[Father].Father;
    Node[Father].RightSon=Node[Now].LeftSon;
    if(Node[Now].LeftSon) Node[Node[Now].LeftSon].Father=Father;
    Node[Now].LeftSon=Father;
    Node[Father].Father=Now;
    Node[Now].Father=Grand;
    if(!Grand) Root=Now;
    else if(Node[Grand].LeftSon==Father) Node[Grand].LeftSon=Now;
    else Node[Grand].RightSon=Now;
    Update(Father);Update(Now);
}
```

旋转本身只修改常数条边，时间复杂度为 $mathcal{O}(1)$。Splay 与 Treap 都会利用旋转调整树形，但调整条件并不相同。

## 普通二叉搜索树代码

下面的代码维护一个可重集合，并支持插入、删除、排名、第 $k$ 小、前驱与后继。它没有平衡保证，因此单次操作的最坏复杂度为 $mathcal{O}(n)$。

```cpp
#include <cstdio>
#define MAXN 100010
using namespace std;
struct node{
    int LeftSon,RightSon,Father;
    int Value,Count,Size;
}Node[MAXN];
int Root=0,cnt=0,n,Option,In;
void Update(int Now){
    Node[Now].Size=Node[Node[Now].LeftSon].Size+Node[Node[Now].RightSon].Size+Node[Now].Count;
}
void Maintain(int Now){
    while(Now){Update(Now);Now=Node[Now].Father;}
}
int New(int Value,int Father){
    Node[++cnt]={0,0,Father,Value,1,1};
    return cnt;
}
int Find(int Value){
    int Now=Root;
    while(Now&&Node[Now].Value!=Value){
        if(Value<Node[Now].Value) Now=Node[Now].LeftSon;
        else Now=Node[Now].RightSon;
    }
    return Now;
}
void Insert(int Value){
    if(!Root){Root=New(Value,0);return;}
    int Now=Root,Father=0;
    while(Now){
        Father=Now;
        if(Value==Node[Now].Value){Node[Now].Count++;Maintain(Now);return;}
        if(Value<Node[Now].Value) Now=Node[Now].LeftSon;
        else Now=Node[Now].RightSon;
    }
    Now=New(Value,Father);
    if(Value<Node[Father].Value) Node[Father].LeftSon=Now;
    else Node[Father].RightSon=Now;
    Maintain(Father);
}
void Delete(int Value){
    int Now=Find(Value);
    if(!Now) return;
    if(Node[Now].Count>1){Node[Now].Count--;Maintain(Now);return;}
    if(Node[Now].LeftSon&&Node[Now].RightSon){
        int Next=Node[Now].RightSon;
        while(Node[Next].LeftSon) Next=Node[Next].LeftSon;
        Node[Now].Value=Node[Next].Value;
        Node[Now].Count=Node[Next].Count;
        Now=Next;
    }
    int Son=Node[Now].LeftSon?Node[Now].LeftSon:Node[Now].RightSon;
    int Father=Node[Now].Father;
    if(Son) Node[Son].Father=Father;
    if(!Father) Root=Son;
    else if(Node[Father].LeftSon==Now) Node[Father].LeftSon=Son;
    else Node[Father].RightSon=Son;
    Maintain(Father);
}
int Get_Rank(int Value){
    int Now=Root,Ret=1;
    while(Now){
        if(Value<Node[Now].Value) Now=Node[Now].LeftSon;
        else{
            Ret+=Node[Node[Now].LeftSon].Size;
            if(Value==Node[Now].Value) return Ret;
            Ret+=Node[Now].Count;
            Now=Node[Now].RightSon;
        }
    }
    return Ret;
}
int Get_Num(int Rank){
    int Now=Root;
    while(Now){
        int LeftSize=Node[Node[Now].LeftSon].Size;
        if(Rank<=LeftSize) Now=Node[Now].LeftSon;
        else if(Rank<=LeftSize+Node[Now].Count) return Node[Now].Value;
        else{Rank-=LeftSize+Node[Now].Count;Now=Node[Now].RightSon;}
    }
    return 0;
}
int Get_Pre(int Value){
    int Now=Root,Ret=-(1<<30);
    while(Now){
        if(Node[Now].Value<Value){Ret=Node[Now].Value;Now=Node[Now].RightSon;}
        else Now=Node[Now].LeftSon;
    }
    return Ret;
}
int Get_Next(int Value){
    int Now=Root,Ret=1<<30;
    while(Now){
        if(Node[Now].Value>Value){Ret=Node[Now].Value;Now=Node[Now].LeftSon;}
        else Now=Node[Now].RightSon;
    }
    return Ret;
}
int main(){
    scanf("%d",&n);
    while(n-->0){
        scanf("%d%d",&Option,&In);
        if(Option==1) Insert(In);
        else if(Option==2) Delete(In);
        else if(Option==3) printf("%d\n",Get_Rank(In));
        else if(Option==4) printf("%d\n",Get_Num(In));
        else if(Option==5) printf("%d\n",Get_Pre(In));
        else printf("%d\n",Get_Next(In));
    }
    return 0;
}
```
