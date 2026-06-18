# Treap

Treap 同时维护两种关系：

1. 节点的 `Value` 满足二叉搜索树性质；
2. 节点的 `Priority` 满足堆性质。

我们给每个新节点随机一个优先级，并规定父亲的优先级小于儿子的优先级。权值决定中序遍历，优先级决定树形。

查找、排名、第 $k$ 小、前驱与后继与[二叉搜索树](binary-search-tree.md)完全相同。本节只讨论如何利用随机优先级维持树形。

## 插入

先按照普通二叉搜索树插入节点。递归返回时，如果某个儿子的优先级小于当前节点，就通过旋转把这个儿子提上来。

- 左儿子优先级更小：对左儿子执行右旋 `Zig`；
- 右儿子优先级更小：对右儿子执行左旋 `Zag`。

旋转不会改变中序遍历，所以二叉搜索树性质仍然成立；把较小优先级旋转到上方后，堆性质也得到恢复。

## 删除

若待删除节点的 `Count` 大于 $1$，直接减一。

否则，若它至多有一个儿子，直接用这个儿子替换当前节点。若左右儿子均存在，则比较两边优先级，把优先级较小的儿子旋转到上方，再继续递归删除原节点。

可以发现，删除过程始终保持二叉搜索树与堆的两种性质。

## 期望复杂度

若各节点优先级互不相同，那么对于一组确定的权值与优先级，满足两种性质的 Treap 形态唯一。它等价于按照优先级从小到大插入权值所得到的二叉搜索树。

由于优先级随机，任意节点成为一段权值区间根节点的概率相同。固定一个节点 $x$，与它相距 $k$ 个位置的节点成为其祖先的概率不超过 $\dfrac{1}{k+1}$。因此 $x$ 的期望深度满足：

$$
\mathbf{E}[\operatorname{Depth}(x)]
\le
2\sum_{k=1}^{n}\dfrac{1}{k}
=
\mathcal{O}(\log n)
$$

所以插入、删除与查询的期望时间复杂度均为 $\mathcal{O}(\log n)$。这里保证的是期望复杂度，而不是任意随机结果下的最坏复杂度。

## 模板

[P3369【模板】普通平衡树](https://www.luogu.com.cn/problem/P3369) 同样可以作为 Treap 的模板题。

???+ note "题目描述"

    维护一个可重集合，支持插入、删除、查询权值排名、查询第 $k$ 小、查询前驱与查询后继。

??? tip "Hint"

    用 `Value` 维护二叉搜索树性质，用随机的 `Priority` 维护小根堆性质。冲突时通过旋转恢复堆性质。

??? success "解法"

    插入和删除写成返回子树根编号的递归函数。每次递归结束后执行 `Update`，即可维护子树大小。其余查询直接使用二叉搜索树的做法。

    ```cpp
    #include <cstdio>
    #define MAXN 100010
    using namespace std;
    struct node{
        int LeftSon,RightSon;
        int Value,Count,Size;
        unsigned Priority;
    }Node[MAXN];
    int Root=0,cnt=0,n,Option,In;
    unsigned Seed=712367821;
    unsigned Rand(){
        Seed^=Seed<<13;
        Seed^=Seed>>17;
        Seed^=Seed<<5;
        return Seed;
    }
    void Update(int Now){
        Node[Now].Size=Node[Node[Now].LeftSon].Size+Node[Node[Now].RightSon].Size+Node[Now].Count;
    }
    int New(int Value){
        Node[++cnt]={0,0,Value,1,1,Rand()};
        return cnt;
    }
    int Zig(int Now){
        int Son=Node[Now].LeftSon;
        Node[Now].LeftSon=Node[Son].RightSon;
        Node[Son].RightSon=Now;
        Update(Now);Update(Son);
        return Son;
    }
    int Zag(int Now){
        int Son=Node[Now].RightSon;
        Node[Now].RightSon=Node[Son].LeftSon;
        Node[Son].LeftSon=Now;
        Update(Now);Update(Son);
        return Son;
    }
    int Insert(int Now,int Value){
        if(!Now) return New(Value);
        if(Value==Node[Now].Value) Node[Now].Count++;
        else if(Value<Node[Now].Value){
            Node[Now].LeftSon=Insert(Node[Now].LeftSon,Value);
            if(Node[Node[Now].LeftSon].Priority<Node[Now].Priority) Now=Zig(Now);
        }
        else{
            Node[Now].RightSon=Insert(Node[Now].RightSon,Value);
            if(Node[Node[Now].RightSon].Priority<Node[Now].Priority) Now=Zag(Now);
        }
        Update(Now);
        return Now;
    }
    int Delete(int Now,int Value){
        if(!Now) return 0;
        if(Value<Node[Now].Value) Node[Now].LeftSon=Delete(Node[Now].LeftSon,Value);
        else if(Value>Node[Now].Value) Node[Now].RightSon=Delete(Node[Now].RightSon,Value);
        else if(Node[Now].Count>1) Node[Now].Count--;
        else if(!Node[Now].LeftSon||!Node[Now].RightSon){
            return Node[Now].LeftSon?Node[Now].LeftSon:Node[Now].RightSon;
        }
        else if(Node[Node[Now].LeftSon].Priority<Node[Node[Now].RightSon].Priority){
            Now=Zig(Now);
            Node[Now].RightSon=Delete(Node[Now].RightSon,Value);
        }
        else{
            Now=Zag(Now);
            Node[Now].LeftSon=Delete(Node[Now].LeftSon,Value);
        }
        Update(Now);
        return Now;
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
            if(Option==1) Root=Insert(Root,In);
            else if(Option==2) Root=Delete(Root,In);
            else if(Option==3) printf("%d\n",Get_Rank(In));
            else if(Option==4) printf("%d\n",Get_Num(In));
            else if(Option==5) printf("%d\n",Get_Pre(In));
            else printf("%d\n",Get_Next(In));
        }
        return 0;
    }
    ```

??? abstract "复杂度分析"

    单次操作的期望时间复杂度为 $\mathcal{O}(\log n)$，空间复杂度为 $\mathcal{O}(n)$。
