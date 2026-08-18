# 第二试

本场为 NOIP 模拟赛第二试，采用 NOIP 2024 仿制赛题面，出题人为 Ehundategh。

## 下发文件

- [题面 PDF 下载](/Blog/assets/solution/noip-mock/test2/statement.pdf)
- [选手下发文件下载](https://github.com/Ehundategh/Blog/releases/download/noip-mock-test2/files.zip)
- 正式评测数据：[编辑字符串](https://github.com/Ehundategh/Blog/releases/download/noip-mock-test2/data-edit.zip)、[遗失的赋值](https://github.com/Ehundategh/Blog/releases/download/noip-mock-test2/data-assign.zip)、[树的遍历](https://github.com/Ehundategh/Blog/releases/download/noip-mock-test2/data-traverse.zip)、[树上查询](https://github.com/Ehundategh/Blog/releases/download/noip-mock-test2/data-query.zip)

## 题目与数据

| 题目 | 来源 | 时限 | 内存限制 | Std | 数据点 |
| --- | --- | --- | --- | --- | --- |
| 编辑字符串 | 原创 | $1\ \mathrm{s}$ | $512\ \mathrm{MiB}$ | [edit.cpp](/Blog/assets/solution/noip-mock/test2/std/edit.cpp) | $20$ 组输入，$20$ 组答案 |
| 遗失的赋值 | 原创 | $1\ \mathrm{s}$ | $512\ \mathrm{MiB}$ | [assign.cpp](/Blog/assets/solution/noip-mock/test2/std/assign.cpp) | $20$ 组输入，$20$ 组答案 |
| 树的遍历 | 改编自 [P10220 迷宫守卫](https://www.luogu.com.cn/problem/P10220) | $1\ \mathrm{s}$ | $512\ \mathrm{MiB}$ | [traverse.cpp](/Blog/assets/solution/noip-mock/test2/std/traverse.cpp) | $25$ 组输入，$25$ 组答案 |
| 树上查询 | 原创 | $2\ \mathrm{s}$ | $1024\ \mathrm{MiB}$ | [query.cpp](/Blog/assets/solution/noip-mock/test2/std/query.cpp) | $25$ 组输入，$25$ 组答案 |

## 题目简述

### 编辑字符串

光标在环形字符串上移动，并在经过的位置修改字符。求将初始字符串变为目标字符串所需的最少操作次数。

### 遗失的赋值

给定一个 $01$ 序列所有长度为 $k$ 的窗口和，以及整个序列中 $1$ 的数量，求符合条件的序列数。

### 树的遍历

在满二叉树上选择若干守卫唤醒。小 X 希望最终叶子遍历序列的字典序最大，小 R 希望其字典序最小，求双方最优策略下的序列。

### 树上查询

在深度优先遍历编号的有根树上，寻找权值和达到给定下界的连续区间，并最大化这些结点最近公共祖先的深度。

## 题解

- [编辑字符串](edit.md)
- [遗失的赋值](assign.md)
- [树的遍历](traverse.md)
- [树上查询](query.md)
