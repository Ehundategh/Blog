# 战争

## 题意简述

初始有 $n$ 个彼此独立的联盟，并给出 $m$ 对敌对参与者。每次提出合并两个参与者所在联盟的请求；若两个联盟之间存在敌对关系，则拒绝，否则合并。输出每次请求是否被接受。

## Hint

??? tip "提示"
    并查集维护当前联盟，同时为每个根维护与它敌对的联盟根集合。合并时使用启发式合并，并同步修改敌对集合中的根。

## 数据点 $1\sim 3$

可以使用位集合维护每个联盟包含的成员及其敌对对象，或者在每次请求时扫描全部初始敌对关系。它们分别得到 $\mathcal{O}((n+q)n/w)$ 与 $\mathcal{O}(qm\alpha(n))$ 的做法。

这些做法已经说明，查询所需的信息并不是联盟的全部成员，而是当前联盟之间是否存在敌对关系。

## 数据点 $4$

暂时接受全部请求并按时间建立并查集重构树。一对敌对参与者首次连通的时刻，就是它们在重构树上最近公共祖先的权值。特殊性质保证只需跳过唯一可能被拒绝的请求。

## 正解

用并查集维护当前联盟。对于每个并查集根 $u$，维护集合 $\operatorname{Against}(u)$，保存与联盟 $u$ 存在敌对关系的其他联盟根。

始终维持三个不变量：

1. $\operatorname{Against}(u)$ 中只保存当前并查集根；
2. 若 $v\in\operatorname{Against}(u)$，则 $u\in\operatorname{Against}(v)$；
3. $v\in\operatorname{Against}(u)$ 当且仅当两个联盟之间至少存在一对初始敌对参与者。

初始时每个人各自组成联盟，并把每条敌对关系同时加入两端集合。

处理请求 $(x,y)$ 时，先令 $x=\operatorname{Find}(x)$，$y=\operatorname{Find}(y)$。

- 若 $x=y$，两个参与者已经在同一联盟中，直接接受；
- 若 $y\in\operatorname{Against}(x)$，两个联盟之间存在敌对关系，拒绝请求且不修改任何结构；
- 否则合并两个联盟。

设把较小联盟 $x$ 合并到较大联盟 $y$。对每个 $v\in\operatorname{Against}(x)$，在 $\operatorname{Against}(v)$ 中删除 $x$ 并加入 $y$，同时将 $v$ 加入 $\operatorname{Against}(y)$。最后清空 $\operatorname{Against}(x)$，并令 $x$ 的并查集父亲为 $y$。这一步把所有原来连接到 $x$ 的敌对关系改接到 $y$，所以三个不变量继续成立。

每次只迁移较小联盟的敌对集合。一个元素被迁移后，它所属联盟的大小至少翻倍，因此每个元素至多迁移 $\mathcal{O}(\log n)$ 次。

## 复杂度分析

使用 `set` 维护敌对集合时，总时间复杂度为

$$
\mathcal{O}\bigl((n+q)\alpha(n)+m\log^2 n\bigr),
$$

空间复杂度为 $\mathcal{O}(n+m)$。

## 参考代码

[war.cpp](/Blog/assets/solution/jiuguang-summer/day10/std/war.cpp)
