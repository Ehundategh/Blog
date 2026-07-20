# 线段树合并

在树形数据结构或分治算法中，我们常常需要在树的每个节点维护一个桶，例如每种数值的出现次数。如果为树中的每个节点都建立一棵完整的线段树，空间复杂度为 $\mathcal{O}(n^2)$，这显然不能承受。

为了优化空间，可以采用 **动态开点线段树**。对于每个节点，只在有值的位置开辟线段树节点；若一棵动态开点线段树中插入了 $k$ 个位置，它占用的节点数为 $\mathcal{O}(k\log W)$。当我们需要自底向上统计子树的信息和时，就需要将子节点的动态开点线段树合并到父节点中，这一过程被称为 **线段树合并**。

## 算法流程

考虑合并两棵动态开点线段树 $\boldsymbol{X}$ 与 $\boldsymbol{Y}$ 的过程。我们从它们各自的根节点开始，同步向下递归进行合并：

- 若当前递归到的节点中，有一个为空，即 $x=0$ 或 $y=0$，则直接返回另一个节点。这对应了直接继承整棵子树的信息，单次操作复杂度为 $\mathcal{O}(1)$。
- 若两棵树的当前节点都不为空，且已经到达叶子节点，即 $l=r$，则将两者的权值合并，将结果累加到其中一个节点上，并返回该节点。
- 若不是上述两种情况，则递归合并左右子树，并在合并完成后调用 $\operatorname{Update}(u)$ 重新上传、维护当前节点的信息，最后返回合并后的节点。

## 复杂度证明

线段树合并的复杂度可以从 **节点数量消减** 的角度证明。

每次两个不为空的节点发生实质重合并进行合并时，由于我们将两个节点的信息合并为一个，因此整棵动态开点线段树的总节点数一定会减少 $1$。

初始时，所有动态开点的线段树中，节点总数不超过 $\mathcal{O}((n+m)\log n)$。在整个树上回溯合并的过程中，因为实质的合并操作一定会导致节点数减少，所以实质合并，即两个非空节点的重合，次数上限就是初始的节点总数。

综合上述，线段树合并的总时间复杂度与空间复杂度均为 $\mathcal{O}((n+m)\log n)$。这里的 $n+m$ 表示最初插入到所有动态开点线段树中的修改总量，实际例题中通常写成 $m\log W$ 的形式。

## 核心代码

根据上述流程，我们可以给出 C++ 核心实现。我们定义节点结构体，向上合并使用 $\operatorname{Update}$，单点修改使用 $\operatorname{Give}$。

```cpp
struct node{
    int LSon,RSon;
    long long Val;
}Node[MAXN * 80];

int TotalNodes;

void Update(int Now){
    Node[Now].Val=Node[Node[Now].LSon].Val+Node[Node[Now].RSon].Val;
}

void Give(int &Now,int l,int r,int Pos,long long Val){
    if(!Now) Now=++TotalNodes;
    if(l==r){
        Node[Now].Val+=Val;
        return;
    }
    int Mid=(l+r)>>1;
    if(Pos<=Mid) Give(Node[Now].LSon,l,Mid,Pos,Val);
    else Give(Node[Now].RSon,Mid+1,r,Pos,Val);
    Update(Now);
}

int Merge(int x,int y,int l,int r){
    if(!x||!y) return x|y;
    if(l==r){
        Node[x].Val+=Node[y].Val;
        return x;
    }
    int Mid=(l+r)>>1;
    Node[x].LSon=Merge(Node[x].LSon,Node[y].LSon,l,Mid);
    Node[x].RSon=Merge(Node[x].RSon,Node[y].RSon,Mid+1,r);
    Update(x);
    return x;
}
```

## 例题：雨天的尾巴

[洛谷 P4556 雨天的尾巴](https://www.luogu.com.cn/problem/P4556) 是线段树合并的模板题。

???+ note "题目描述"

    给定一棵包含 $n$ 个节点的树，给出 $m$ 次操作。

    每次操作给出 $u,v,w$，表示在节点 $u$ 到 $v$ 的最短路径上的每一个节点投放一个 $w$ 类型的物品。

    要求在所有操作结束后，输出每个节点上数量最多的物品是哪一种。若有多种物品数量相同且最多，输出编号最小的物品；若该节点没有物品，输出 $0$。

??? tip "Hint"

    如果对每次路径上的节点直接暴力累加修改，单次操作的复杂度为 $\mathcal{O}(n)$，总复杂度高达 $\mathcal{O}(nm)$，显然会超时。

    考虑将路径修改转化为单点修改，也就是 **树上差分**。我们该如何通过差分表示路径 $u\to v$ 的修改，并在最后通过一次统计合并出每个点的桶信息？

??? success "解法"

    对树上的路径修改采用 **树上差分** 方案。

    对于每次操作 $u,v,w$，设 $g=\operatorname{LCA}(u,v)$，而 $p=\operatorname{fa}(g)$。

    我们在节点 $u$ 和 $v$ 的动态开点线段树中将 $w$ 类型物品的数量加 $1$，在 $g$ 和 $p$ 的动态开点线段树中将 $w$ 类型物品的数量减 $1$。

    显然，任意节点 $x$ 最终所拥有的每种物品的真实数量，就是以 $x$ 为根的子树中所有节点差分桶的叠加之和。

    因此，我们可以在对整棵树进行深搜回溯时，将子节点的线段树依次合并到当前父节点的线段树中。在合并完成后，当前节点线段树的根节点记录的 $\operatorname{MaxId}$ 即为子树内出现次数最多且编号最小的物品编号。

    ```cpp
    #include <cstdio>
    #include <cstring>
    #include <algorithm>
    using namespace std;

    const int MAXN=100010;

    struct edge{
        int St,Ed,Next;
    }Edge[MAXN<<1];

    int Head[MAXN],Total;

    void Edge_Add(int St,int Ed){
        Edge[++Total]={St,Ed,Head[St]};
        Head[St]=Total;
    }

    int Up[MAXN][20],Deep[MAXN];

    void DFS1(int Now,int Fa){
        Deep[Now]=Deep[Fa]+1;
        Up[Now][0]=Fa;
        for(int i=1;i<20;i++){
            Up[Now][i]=Up[Up[Now][i-1]][i-1];
        }
        for(int i=Head[Now];i;i=Edge[i].Next){
            int To=Edge[i].Ed;
            if(To!=Fa) DFS1(To,Now);
        }
    }

    int LCA(int x,int y){
        if(Deep[x]<Deep[y]) swap(x,y);
        for(int i=19;i>=0;i--){
            if(Deep[Up[x][i]]>=Deep[y]) x=Up[x][i];
        }
        if(x==y) return x;
        for(int i=19;i>=0;i--){
            if(Up[x][i]!=Up[y][i]){
                x=Up[x][i];
                y=Up[y][i];
            }
        }
        return Up[x][0];
    }

    struct node{
        int LSon,RSon;
        int MaxVal,MaxId;
    }Node[MAXN*80];

    int Root[MAXN],TotalNodes;

    void Update(int Now){
        int L=Node[Now].LSon,R=Node[Now].RSon;
        if(Node[L].MaxVal>=Node[R].MaxVal){
            Node[Now].MaxVal=Node[L].MaxVal;
            Node[Now].MaxId=Node[L].MaxId;
        }else{
            Node[Now].MaxVal=Node[R].MaxVal;
            Node[Now].MaxId=Node[R].MaxId;
        }
    }

    void Give(int &Now,int l,int r,int Pos,int Val){
        if(!Now) Now=++TotalNodes;
        if(l==r){
            Node[Now].MaxVal+=Val;
            Node[Now].MaxId=Node[Now].MaxVal>0?Pos:0;
            return;
        }
        int Mid=(l+r)>>1;
        if(Pos<=Mid) Give(Node[Now].LSon,l,Mid,Pos,Val);
        else Give(Node[Now].RSon,Mid+1,r,Pos,Val);
        Update(Now);
    }

    int Merge(int x,int y,int l,int r){
        if(!x||!y) return x|y;
        if(l==r){
            Node[x].MaxVal+=Node[y].MaxVal;
            Node[x].MaxId=Node[x].MaxVal>0?l:0;
            return x;
        }
        int Mid=(l+r)>>1;
        Node[x].LSon=Merge(Node[x].LSon,Node[y].LSon,l,Mid);
        Node[x].RSon=Merge(Node[x].RSon,Node[y].RSon,Mid+1,r);
        Update(x);
        return x;
    }

    int Ans[MAXN];

    void DFS2(int Now,int Fa){
        for(int i=Head[Now];i;i=Edge[i].Next){
            int To=Edge[i].Ed;
            if(To!=Fa){
                DFS2(To,Now);
                Root[Now]=Merge(Root[Now],Root[To],1,100000);
            }
        }
        Ans[Now]=Node[Root[Now]].MaxId;
    }

    int main(){
        int n,m;
        if(scanf("%d%d",&n,&m)!=2) return 0;
        for(int i=1;i<n;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            Edge_Add(u,v);
            Edge_Add(v,u);
        }
        DFS1(1,0);
        for(int i=1;i<=m;i++){
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            int g=LCA(u,v);
            Give(Root[u],1,100000,w,1);
            Give(Root[v],1,100000,w,1);
            Give(Root[g],1,100000,w,-1);
            Give(Root[Up[g][0]],1,100000,w,-1);
        }
        DFS2(1,0);
        for(int i=1;i<=n;i++){
            printf("%d\n",Ans[i]);
        }
        return 0;
    }
    ```

??? abstract "复杂度分析"

    树上差分单次修改的时间复杂度为 $\mathcal{O}(\log W)$，其开销在 $\operatorname{Give}$ 上。$m$ 次操作总开销为 $\mathcal{O}(m\log W)$。

    回溯 DFS 时合并线段树的总次数为 $n-1$ 次，实质合并的重合节点总数不超过 $\mathcal{O}(m\log W)$。

    综上，整体的时间复杂度为 $\mathcal{O}((n+m)\log W)$，其中 $W$ 为物品最大种类数，在洛谷模板题中 $W\le 10^5$。

    动态开点线段树共新增节点不超过 $\mathcal{O}(m\log W)$ 个，邻接表、深度数组与倍增数组占用 $\mathcal{O}(n\log n)$ 空间。总空间复杂度为 $\mathcal{O}(n\log n+m\log W)$。

## 更多应用例题

- [GSOI 2026 商路照影](../../solution/jiuguang-summer/day2/trade.md)：GSOI 2026 第二试「商路照影」详细题解，展示了如何在二叉树回溯合并过程中利用独立性完成乘法原理计数。
