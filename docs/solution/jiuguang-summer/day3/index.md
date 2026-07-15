# 第三天

本场为九光暑假第三天训练赛，时间为 2026 年 7 月 14 日 14:00 至 17:30，出题人为 Ehundategh。

## 下发文件

- [题面 PDF 下载](/Blog/assets/solution/jiuguang-summer/day3/statement.pdf)
- [题解 PDF 下载](/Blog/assets/solution/jiuguang-summer/day3/solution.pdf)
- [题面、样例与参考代码](/Blog/assets/solution/jiuguang-summer/day3/files.zip)

## Std 与数据

以下 Std 来自 `D:\Code and Problem\7.14`，数据包来自对应题目的正式数据目录，并保留 `.in`、`.ans` 与 `std.cpp`。

| 题目 | 来源 | Std | 数据点 | 数据 |
| --- | --- | --- | --- | --- |
| 夜奔 | 原创 | [dash.cpp](/Blog/assets/solution/jiuguang-summer/day3/std/dash.cpp) | $20$ 组输入，$20$ 组答案 | [data-dash.zip](/Blog/assets/solution/jiuguang-summer/day3/data-dash.zip) |
| 何以为我 | 改编自 [P1637 三元上升子序列](https://www.luogu.com.cn/problem/P1637) | [upline.cpp](/Blog/assets/solution/jiuguang-summer/day3/std/upline.cpp) | $20$ 组输入，$20$ 组答案 | [data-upline.zip](/Blog/assets/solution/jiuguang-summer/day3/data-upline.zip) |
| 浮光掠影 | 改编自 [P4513 小白逛公园](https://www.luogu.com.cn/problem/P4513) | [sunset.cpp](/Blog/assets/solution/jiuguang-summer/day3/std/sunset.cpp) | $20$ 组输入，$20$ 组答案 | [data-sunset.zip](/Blog/assets/solution/jiuguang-summer/day3/data-sunset.zip) |
| 锦鲤 | 原创 | [fish.cpp](/Blog/assets/solution/jiuguang-summer/day3/std/fish.cpp) | $25$ 组输入，$25$ 组答案 | [data-fish.zip](/Blog/assets/solution/jiuguang-summer/day3/data-fish.zip) |

## 题目简述

### 夜奔

给定一个环形字符串 $S$ 与目标字符串 $T$。从第 $1$ 个位置之前出发，沿环向前走，每次停留可以记录当前位置的字符，求得到 $T$ 至少需要经过多少个位置。

### 何以为我

给定序列 $a_1,a_2,\cdots,a_n$，统计满足 $i<j<k$ 且 $a_i<a_j<a_k$ 的三元组数量。

### 浮光掠影

维护一个序列，支持单点修改与区间最大子段和查询。所选子区间必须非空。

### 锦鲤

给定正整数序列与参数 $k$。一个区间 $[l,r]$ 合法当且仅当区间和不超过 $k$ 乘以区间最小值。每次询问要求把 $[l,r]$ 划分成最少数量的合法连续段。

## 题解

- [夜奔](dash.md)
- [何以为我](upline.md)
- [浮光掠影](sunset.md)
- [锦鲤](fish.md)
