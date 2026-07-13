# 第二天

本场为九光暑假第二天训练赛，出题人为 Ehundategh 与 tfbz。

## 下发文件

- [题面 PDF 下载](/Blog/assets/solution/jiuguang-summer/day2/statement.pdf)
- [题解 PDF 下载](/Blog/assets/solution/jiuguang-summer/day2/solution.pdf)
- [题面、题解、样例与参考代码](/Blog/assets/solution/jiuguang-summer/day2/files.zip)

## Std 与数据

以下数据包来自对应题目的数据目录，并保留 `.in`、`.ans` 与 `std.cpp`。

| 题目 | 来源 | Std | 数据点 | 数据 |
| --- | --- | --- | --- | --- |
| 归零 | 原创 | [reset.cpp](/Blog/assets/solution/jiuguang-summer/day2/std/reset.cpp) | $20$ 组输入，$20$ 组答案 | [data-reset.zip](/Blog/assets/solution/jiuguang-summer/day2/data-reset.zip) |
| 引力之阱 | 原创 | [escape.cpp](/Blog/assets/solution/jiuguang-summer/day2/std/escape.cpp) | $25$ 组输入，$25$ 组答案 | [data-escape.zip](/Blog/assets/solution/jiuguang-summer/day2/data-escape.zip) |
| 商路照影 | 原创 | [trade.cpp](/Blog/assets/solution/jiuguang-summer/day2/std/trade.cpp) | $20$ 组输入，$20$ 组答案 | [data-trade.zip](/Blog/assets/solution/jiuguang-summer/day2/data-trade.zip) |
| 逐风 | 原创 | [wind.cpp](/Blog/assets/solution/jiuguang-summer/day2/std/wind.cpp) | $20$ 组输入，$20$ 组答案 | [data-wind.zip](/Blog/assets/solution/jiuguang-summer/day2/data-wind.zip) |

## 题目简述

### 归零

给定 $n$ 盏星灯，单独归零第 $i$ 盏的代价为 $a_i$，同时归零相邻的第 $i,i+1$ 盏的代价为 $b_i$。每盏星灯必须恰好被归零一次，求最小总代价。

### 引力之阱

给出 $n+1$ 个 $n$ 维点及其到某个未知点的距离平方，求这个未知点的坐标。

### 商路照影

给定一棵有根二叉树，第 $i$ 个节点的权值为 $w_i$。对于每个节点 $x$，统计满足 $u$ 在 $x$ 的左儿子子树内，$v$ 在 $x$ 的右儿子子树内，并且 $w_u<w_x<w_v$ 的有序点对 $(u,v)$ 数量。

### 逐风

给定周期为 $n$ 的风向序列。每天白天可以自行移动不超过 $k$ 的曼哈顿距离，傍晚会被当天的风推动。对于每组数据，要求最早在某天傍晚恰好到达目标点。

## 题解

- [归零](reset.md)
- [引力之阱](escape.md)
- [商路照影](trade.md)
- [逐风](wind.md)
