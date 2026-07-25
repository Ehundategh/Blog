# 第六天

本场为九光暑假第六天训练赛，时间为 2026 年 7 月 21 日 14:00 至 17:30，出题人为 Ehundategh。

## 下发文件

- [题面 PDF 下载](/Blog/assets/solution/jiuguang-summer/day6/statement.pdf)
- [题解 PDF 下载](/Blog/assets/solution/jiuguang-summer/day6/solution.pdf)
- [题面、样例与参考代码](/Blog/assets/solution/jiuguang-summer/day6/files.zip)

## Std 与数据

以下 Std 与数据来自 `D:\Codex\Competition\Summer\day6` 的正式工程，每题保留 $20$ 组正式输入与 $20$ 组答案。

| 题目 | 来源 | Std | 数据点 | 数据 |
| --- | --- | --- | --- | --- |
| 千仓平丰歉 | 改编自 [Codeforces 2007C Dora and C++](https://codeforces.com/problemset/problem/2007/C) | [balance.cpp](/Blog/assets/solution/jiuguang-summer/day6/std/balance.cpp) | $20$ 组输入，$20$ 组答案 | [data-balance.zip](/Blog/assets/solution/jiuguang-summer/day6/data-balance.zip) |
| 迢迢寻故人 | 原创 | [trail.cpp](/Blog/assets/solution/jiuguang-summer/day6/std/trail.cpp) | $20$ 组输入，$20$ 组答案 | [data-trail.zip](/Blog/assets/solution/jiuguang-summer/day6/data-trail.zip) |
| 万山舆共渡 | 改编自 [P2680 [NOIP 2015 提高组] 运输计划](https://www.luogu.com.cn/problem/P2680) | [trans.cpp](/Blog/assets/solution/jiuguang-summer/day6/std/trans.cpp) | $20$ 组输入，$20$ 组答案 | [data-trans.zip](/Blog/assets/solution/jiuguang-summer/day6/data-trans.zip) |
| 万象启星环 | 改编自 [P3702 [SDOI2017] 序列计数](https://www.luogu.com.cn/problem/P3702) | [circum.cpp](/Blog/assets/solution/jiuguang-summer/day6/std/circum.cpp) | $20$ 组输入，$20$ 组答案 | [data-circum.zip](/Blog/assets/solution/jiuguang-summer/day6/data-circum.zip) |

## 题目简述

### 千仓平丰歉

给定若干仓库的储备量，每次可以任选一个仓库增加 $a$ 或 $b$。求任意次操作后，最大储备量与最小储备量之差的最小值。

### 迢迢寻故人

给定一个带非负整数的网格，允许四联通行走且可以重复经过格子。求从左上角到右下角的路径中，经过数值集合的最小可能 $\operatorname{mex}$。

### 万山舆共渡

给定一棵带边权树和若干运输路径。可以选择一条边令其边权变为 $0$，求所有路径同时完成时的最小最大路径长度。

### 万象启星环

求长度为 $n$、每项在 $[1,m]$ 的有序序列数量，要求序列和为 $p$ 的倍数且至少有一项为质数，答案对 $998{,}244{,}353$ 取模。

## 题解

- [千仓平丰歉](balance.md)
- [迢迢寻故人](trail.md)
- [万山舆共渡](trans.md)
- [万象启星环](circum.md)
