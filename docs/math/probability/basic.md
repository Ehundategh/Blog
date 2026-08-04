# 概率的基本概念

## 样本空间与事件

抛一枚均匀硬币，我们当然不知道哪一面会朝上。但是多抛一些，又会发现正面出现的比例逐渐靠近 $\dfrac12$。概率论要研究的就是这种随机现象。

???+ definition "随机试验"

    在相同条件下可以重复进行、结果不止一种，并且试验前不能确定具体结果的过程，称为随机试验。

随机试验的条件和全部可能结果都要能够预先说明，只是我们无法提前知道实际发生哪一个结果。

???+ definition "样本点与样本空间"

    随机试验的每一个可能结果称为样本点。全部样本点构成的集合称为样本空间，记为 $\Omega$。

掷一枚六面骰子时，

$$
\Omega=\{1,2,3,4,5,6\}.
$$

连续抛两次硬币时，必须保留先后顺序，因此

$$
\Omega=\{\text{正正},\text{正反},\text{反正},\text{反反}\}.
$$

样本点怎样定义，后面就要数什么。

???+ definition "事件"

    样本空间 $\Omega$ 的子集称为随机事件，简称事件。事件 $A$ 发生，指实际出现的样本点属于 $A$。

掷骰子时，事件“点数为偶数”可以记为 $A=\{2,4,6\}$。全集 $\Omega$ 称为必然事件，空集 $\varnothing$ 称为不可能事件。

事件本身是集合，因此可以直接使用集合运算：

| 事件 | 含义 |
| --- | --- |
| $A\cup B$ | $A,B$ 至少有一个发生 |
| $A\cap B$ | $A,B$ 同时发生 |
| $A\setminus B$ | $A$ 发生而 $B$ 不发生 |
| $\overline A=\Omega\setminus A$ | $A$ 不发生 |

若 $A\cap B=\varnothing$，称 $A,B$ 互斥。互斥只说明两个事件不能同时发生，与它们各自的概率大小无关。

## 概率

???+ definition "概率的公理化定义"

    对样本空间中的每个事件 $A$，给出一个实数 $P(A)$，称为事件 $A$ 的概率。它满足：

    1. $P(A)\geq 0$；
    2. $P(\Omega)=1$；
    3. 若 $A\cap B=\varnothing$，则 $P(A\cup B)=P(A)+P(B)$。

由这三条性质可以推出后面常用的结论。

???+ theorem "不可能事件与对立事件"

    有

    $$
    P(\varnothing)=0,
    \qquad
    P(\overline A)=1-P(A).
    $$

??? proof "证明"

    因为 $\Omega\cap\varnothing=\varnothing$ 且 $\Omega\cup\varnothing=\Omega$，由可加性，

    $$
    P(\Omega)=P(\Omega)+P(\varnothing),
    $$

    所以 $P(\varnothing)=0$。

    又因为 $A,\overline A$ 互斥，且 $A\cup\overline A=\Omega$，所以

    $$
    P(A)+P(\overline A)=P(\Omega)=1.
    $$

???+ theorem "单调性"

    若 $A\subseteq B$，则 $P(A)\leq P(B)$。

??? proof "证明"

    事件 $A$ 与 $B\setminus A$ 互斥，并且

    $$
    B=A\mathbin{\dot\cup}(B\setminus A).
    $$

    因此

    $$
    P(B)=P(A)+P(B\setminus A)\geq P(A).
    $$

    特别地，由 $\varnothing\subseteq A\subseteq\Omega$ 可得 $0\leq P(A)\leq 1$。

???+ theorem "概率的加法公式"

    对任意事件 $A,B$，有

    $$
    P(A\cup B)=P(A)+P(B)-P(A\cap B).
    $$

??? proof "证明"

    把并集拆成三个两两互斥的部分：

    $$
    A\cup B=(A\setminus B)\mathbin{\dot\cup}(A\cap B)
    \mathbin{\dot\cup}(B\setminus A).
    $$

    在 $P(A)+P(B)$ 中，交集部分被计算了两次，而并集中只应计算一次，因此减去 $P(A\cap B)$ 即得结论。

## 古典概型

???+ definition "古典概型"

    若随机试验的样本空间只含有限个样本点，并且每个样本点出现的概率相同，就称这个试验构成古典概型。

“有限”和“等可能”两个条件都要检查。只有结果数有限，并不能直接使用古典概型。

???+ theorem "古典概型的概率"

    在古典概型中，事件 $A$ 的概率为

    $$
    P(A)=\dfrac{n(A)}{n(\Omega)}.
    $$

??? proof "证明"

    设 $n(\Omega)=N$。每个样本点的概率都是 $\dfrac1N$，而事件 $A$ 中有 $n(A)$ 个样本点。根据互斥可加性，

    $$
    P(A)=n(A)\cdot\dfrac1N
    =\dfrac{n(A)}{n(\Omega)}.
    $$

所以古典概型把概率问题转化成了计数问题。处理时依次完成四件事：明确样本点记录什么；验证结果有限且等可能；计算 $n(\Omega)$；把目标翻译为事件 $A$ 并计算 $n(A)$。

## 例题

???+ note "题目描述"

    [P2911 [USACO08OCT] Bovine Bones G](https://www.luogu.com.cn/problem/P2911)

    三枚均匀骰子的面数分别为 $S_1,S_2,S_3$，各掷一次。求出现概率最大的点数和；若有多个答案，输出最小者。

??? tip "Hint"

    把一次试验结果写成三元组 $(a,b,c)$。全部三元组等可能，所以只需要统计每个点数和出现了多少次。

??? success "解法"

    样本空间大小为

    $$
    n(\Omega)=S_1S_2S_3.
    $$

    对每个可能的和 $s$，定义

    $$
    A_s=\{(a,b,c)\mid a+b+c=s\}.
    $$

    因为所有 $P(A_s)$ 的分母相同，比较概率只需要比较 $n(A_s)$。枚举全部三元组并统计 $a+b+c$ 的出现次数，再从小到大寻找第一次达到最大次数的 $s$。

??? abstract "复杂度分析"

    时间复杂度为 $\mathcal{O}(S_1S_2S_3)$，空间复杂度为 $\mathcal{O}(S_1+S_2+S_3)$。
