# 蝶恋花

## 题意简述

维护序列 $a_i$ 与历史最大值 $b_i$。支持区间加、区间取最小值、查询区间和、查询区间最大值、查询区间历史最大值。

## Hint

区间取最小值只会影响当前最大值。若一个线段树结点的最大值大于 $v$ 且严格次大值小于 $v$，就可以只修改最大值那一批元素。

??? note "提示"
    每个结点维护最大值、严格次大值、最大值个数、区间和与历史最大值。区间加和历史最大值需要用标记同时维护“最大值位置”和“非最大值位置”。

## 解法

这是区间最值操作线段树。每个结点维护：

- $\operatorname{Max}$：当前最大值；
- $\operatorname{SecMax}$：严格次大值；
- $\operatorname{MaxCnt}$：最大值个数；
- $\operatorname{Sum}$：区间和；
- $\operatorname{HisMax}$：历史最大值。

对区间取最小值 $v$ 时：

- 若 $\operatorname{Max}\le v$，没有影响；
- 若 $\operatorname{SecMax}<v<\operatorname{Max}$，只把最大值部分压到 $v$，可以整段打标记；
- 否则继续递归。

区间加会同时改变最大值与非最大值；历史最大值要求标记记录当前值变化与历史变化，因此代码中将最大值位置和其他位置分开维护。

## 复杂度

均摊复杂度为 $\mathcal{O}((n+q)\log n)$，空间复杂度为 $\mathcal{O}(n)$。

## 参考代码

[flutter.cpp](/Blog/assets/solution/jiuguang-summer/day8/std/flutter.cpp)
