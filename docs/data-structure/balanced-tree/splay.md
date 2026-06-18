# Splay

Splay 也称伸展树，是一种自调整二叉搜索树。它不显式维护树高，而是在每次访问节点 $x$ 后执行 `Splay(x)`，将 $x$ 旋转到根。单次操作可能达到 $\mathcal{O}(n)$，但连续操作的均摊复杂度为 $\mathcal{O}(\log n)$。

Splay 中的节点定义、查找、排名、前驱与后继均建立在[二叉搜索树](binary-search-tree.md)上。本节只讨论 Splay 特有的伸展操作；左右旋的连边方式也在二叉搜索树一节中给出。

## 伸展操作

假设当前需要把节点 $x$ 旋转到根，令其父亲为 $y$，祖父为 $z$。

若 $y$ 已经是根，只需旋转一次 $x$，这一步称为 `Zig`。

若 $x$ 仍有祖父，则需要根据 $x,y,z$ 的位置分情况讨论。

### 一字旋

若 $x$ 与 $y$ 的儿子属性相同，即二者同时为左儿子或同时为右儿子，则先旋转 $y$，再旋转 $x$。

例如 $x$ 与 $y$ 均为左儿子时：

$$
z\longleftarrow y\longleftarrow x
\quad\Longrightarrow\quad
x\longrightarrow y\longrightarrow z
$$

这里不能连续对 $x$ 做两次单旋。先旋转 $y$ 可以同时压低原路径上的 $y,z$，这正是均摊复杂度分析中需要的结构变化。

### 之字旋

若 $x$ 与 $y$ 的儿子属性不同，则连续旋转两次 $x$。

例如 $y$ 是 $z$ 的左儿子，而 $x$ 是 $y$ 的右儿子：

$$
z\longleftarrow y\longrightarrow x
\quad\Longrightarrow\quad
y\longleftarrow x\longrightarrow z
$$

两种双旋都保持中序遍历不变，因此旋转后仍然是一棵二叉搜索树。

```cpp
bool Get(int Now){
    return Now==Node[Node[Now].Father].LeftSon;
}

void Rotate(int Now){
    int Father=Node[Now].Father;
    int Grand=Node[Father].Father;
    if(Get(Now)){
        Node[Father].LeftSon=Node[Now].RightSon;
        if(Node[Now].RightSon) Node[Node[Now].RightSon].Father=Father;
        Node[Now].RightSon=Father;
    }
    else{
        Node[Father].RightSon=Node[Now].LeftSon;
        if(Node[Now].LeftSon) Node[Node[Now].LeftSon].Father=Father;
        Node[Now].LeftSon=Father;
    }
    Node[Father].Father=Now;
    Node[Now].Father=Grand;
    if(!Grand) Root=Now;
    else if(Node[Grand].LeftSon==Father) Node[Grand].LeftSon=Now;
    else Node[Grand].RightSon=Now;
    Update(Father);Update(Now);
}

void Splay(int Now){
    while(Now!=Root){
        int Father=Node[Now].Father;
        int Grand=Node[Father].Father;
        if(Grand){
            if(Get(Now)==Get(Father)) Rotate(Father);
            else Rotate(Now);
        }
        Rotate(Now);
    }
}
```

## 操作方式

Splay 的二叉搜索树操作本身没有改变，区别只在于每次访问后要把对应节点伸展到根。

- `Insert(Value)`：按二叉搜索树方式插入，再将新节点或已有节点伸展到根。
- `Get_Rank(Value)`：查找权值时，将找到的节点伸展到根。
- `Get_Num(Rank)`：找到第 `Rank` 小对应的节点后，将其伸展到根。
- `Get_Pre(Value)`、`Get_Next(Value)`：找到前驱或后继后，将其伸展到根。
- `Delete(Value)`：先将待删除节点伸展到根，再合并左右子树。

删除时，若根的左右子树均非空，则先令左子树成为整棵树，再把左子树中的最大节点伸展到根。此时新根没有右儿子，可以直接把原来的右子树接上。

## 势能分析

接下来说明为什么必须使用双旋，以及为什么 Splay 的均摊复杂度为 $\mathcal{O}(\log n)$。

定义节点 $u$ 的秩为：

$$
r(u)=\log_2\operatorname{Size}(u)
$$

定义整棵树的势能为：

$$
\Phi(T)=\sum_{u\in T}r(u)
$$

一次旋转的实际代价记作 $1$。对于一次伸展操作，均摊代价为实际旋转次数加上势能变化。

考虑一次双旋。旋转前后只有 $x,y,z$ 的子树大小可能改变。分别讨论一字旋与之字旋，并利用 $\log$ 函数的凹性，可以得到：

$$
2+\Delta\Phi
\le
3\bigl(r'(x)-r(x)\bigr)
$$

其中 $r'(x)$ 表示双旋后 $x$ 的秩。以一字旋为例，旋转后 $x$ 包含原来以 $z$ 为根的整棵子树，因此 $r'(x)=r(z)$；而旋转后的 $y,z$ 分别只包含这棵树的两个真子部分。两个子部分的大小之和不超过 $\operatorname{Size}'(x)$，将其代入对数的凹性即可吸收双旋的实际代价 $2$。之字旋的两侧子树互不相交，同样得到上述不等式。

最后可能剩下一次单旋，其均摊代价至多为：

$$
1+3\bigl(r'(x)-r(x)\bigr)
$$

把整次 `Splay(x)` 中的各组旋转相加，中间的秩变化会依次抵消，得到：

$$
\widehat{c}
\le
1+3\bigl(r(\operatorname{Root})-r(x)\bigr)
\le
1+3\log_2 n
$$

因此一次访问的均摊复杂度为 $\mathcal{O}(\log n)$。若只做单旋，上面的秩差无法稳定吸收路径上每一步的代价，也就不能得到这一界。

## 模板

[P3369【模板】普通平衡树](https://www.luogu.com.cn/problem/P3369) 可以直接检验各项基本操作。

???+ note "题目描述"

    维护一个可重集合，支持插入、删除、查询权值排名、查询第 $k$ 小、查询前驱与查询后继。

??? tip "Hint"

    所有查询方式均与普通二叉搜索树相同。需要补充的只有一点：每次找到目标节点后，将其伸展到根。

??? success "解法"

    使用 `Count` 记录相同权值的出现次数，使用 `Size` 维护子树大小。插入、排名、第 $k$ 小、前驱与后继在完成访问后调用 `Splay`；删除先把目标节点伸展到根，再按左右子树是否为空分类处理。

??? abstract "复杂度分析"

    每次操作的均摊时间复杂度为 $\mathcal{O}(\log n)$，空间复杂度为 $\mathcal{O}(n)$。

## 与 LCT 的关系

Splay 还可以维护一条会动态改变的首选路径。Link-Cut Tree 正是把每条实链组织成一棵 Splay，并通过伸展与翻转标记维护动态森林。本节只讨论按权值组织的平衡树；LCT 中 Splay 的中序顺序表示路径顺序，而不是权值顺序。
