# 条件概率与 Bayes 公式

## 条件概率

袋中有 $2$ 个红球与 $3$ 个蓝球，不放回地连续抽取两个球。第一次抽到红球的概率为 $\dfrac25$；如果已经知道第一次抽到了红球，第二次抽到红球的概率就变成 $\dfrac14$。

概率发生变化，是因为已知信息排除了一部分原来可能的结果。

???+ definition "条件概率"

    设 $A,B$ 为两个事件，且 $P(B)>0$。在事件 $B$ 已经发生的条件下，事件 $A$ 发生的概率定义为

    $$
    P(A\mid B)=\dfrac{P(A\cap B)}{P(B)}.
    $$

已知 $B$ 发生后，样本空间被限制到集合 $B$；其中属于 $A$ 的部分正是 $A\cap B$。

???+ theorem "条件概率的乘法公式"

    若 $P(B)>0$，则

    $$
    P(A\cap B)=P(B)P(A\mid B).
    $$

    若 $P(A)>0$，同样有

    $$
    P(A\cap B)=P(A)P(B\mid A).
    $$

??? proof "证明"

    由条件概率的定义，

    $$
    P(A\mid B)=\dfrac{P(A\cap B)}{P(B)}.
    $$

    两边同乘 $P(B)$ 得到第一式。交换 $A,B$，并使用 $A\cap B=B\cap A$，得到第二式。

乘法公式适合计算一条过程路径的概率：先到达前一阶段，再在这个条件下到达下一阶段。

## 独立性

???+ definition "两个事件相互独立"

    若事件 $A,B$ 满足

    $$
    P(A\cap B)=P(A)P(B),
    $$

    就称 $A,B$ 相互独立。

当 $P(B)>0$ 时，独立性等价于 $P(A\mid B)=P(A)$。也就是说，知道 $B$ 已经发生以后，事件 $A$ 的概率没有变化。

互斥与独立描述的是两件不同的事情：

- 互斥表示 $A\cap B=\varnothing$，两个事件不能同时发生；
- 独立表示知道一个事件发生不会改变另一个事件的概率。

若 $P(A)>0,P(B)>0$ 且二者互斥，则

$$
P(A\cap B)=0<P(A)P(B),
$$

所以它们一定不独立。

???+ definition "多个事件相互独立"

    事件 $A_1,A_2,\ldots,A_n$ 相互独立，指对任意非空指标集合 $I\subseteq\{1,2,\ldots,n\}$，都有

    $$
    P\left(\bigcap_{i\in I}A_i\right)
    =\prod_{i\in I}P(A_i).
    $$

只检查任意两个事件得到的是两两独立。两两独立不能保证三个或更多事件相互独立，所以定义中要检查所有非空指标集合。

## 全概率公式

???+ definition "完备事件组"

    若事件 $B_1,B_2,\ldots,B_n$ 两两互斥，满足

    $$
    \mathop{\dot\bigcup}_{i=1}^{n}B_i=\Omega,
    $$

    并且每个 $P(B_i)>0$，就称它们构成样本空间的一个完备事件组。

???+ theorem "全概率公式"

    若 $B_1,B_2,\ldots,B_n$ 构成完备事件组，则对任意事件 $A$，

    $$
    P(A)=\sum_{i=1}^{n}P(B_i)P(A\mid B_i).
    $$

??? proof "证明"

    因为 $B_1,\ldots,B_n$ 覆盖整个样本空间，

    $$
    A=A\cap\Omega
    =\mathop{\dot\bigcup}_{i=1}^{n}(A\cap B_i).
    $$

    这些事件两两互斥，所以

    $$
    P(A)=\sum_{i=1}^{n}P(A\cap B_i).
    $$

    再代入乘法公式 $P(A\cap B_i)=P(B_i)P(A\mid B_i)$ 即得结论。

## Bayes 公式

???+ theorem "Bayes 公式"

    若 $B_1,\ldots,B_n$ 构成完备事件组，且 $P(A)>0$，则

    $$
    P(B_j\mid A)
    =\dfrac{P(B_j)P(A\mid B_j)}
    {\displaystyle\sum_{i=1}^{n}P(B_i)P(A\mid B_i)}.
    $$

??? proof "证明"

    根据条件概率与乘法公式，

    $$
    P(B_j\mid A)
    =\dfrac{P(A\cap B_j)}{P(A)}
    =\dfrac{P(B_j)P(A\mid B_j)}{P(A)}.
    $$

    再由全概率公式，

    $$
    P(A)=\sum_{i=1}^{n}P(B_i)P(A\mid B_i).
    $$

    把它代入分母即可。

$P(B_j)$ 是观察结果前来源为 $B_j$ 的先验概率，$P(B_j\mid A)$ 是观察到事件 $A$ 后得到的后验概率。

## 例题

???+ note "题目描述"

    设 $B_1,B_2$ 构成完备事件组，并且

    $$
    P(B_1)=\dfrac13,
    \qquad
    P(B_2)=\dfrac23,
    $$

    $$
    P(A\mid B_1)=\dfrac23,
    \qquad
    P(A\mid B_2)=\dfrac14.
    $$

    求 $P(A)$ 与 $P(B_1\mid A)$。

??? tip "Hint"

    先用全概率公式求 $P(A)$，再用 Bayes 公式反推来源。

??? success "解法"

    根据全概率公式，

    $$
    P(A)=\dfrac13\cdot\dfrac23
    +\dfrac23\cdot\dfrac14
    =\dfrac7{18}.
    $$

    因此

    $$
    P(B_1\mid A)
    =\dfrac{P(B_1)P(A\mid B_1)}{P(A)}
    =\dfrac{\dfrac29}{\dfrac7{18}}
    =\dfrac47.
    $$

    观察事件 $A$ 以前，$B_1$ 的概率为 $\dfrac13$；观察到 $A$ 后，这个概率被修正为 $\dfrac47$。
