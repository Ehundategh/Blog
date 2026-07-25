# 第七天

本场为九光暑假第七天训练赛，时间为 2026 年 7 月 22 日 14:00 至 17:30，出题人为 Ehundategh。

## 下发文件

- [题面 PDF 下载](/Blog/assets/solution/jiuguang-summer/day7/statement.pdf)
- [题解 PDF 下载](/Blog/assets/solution/jiuguang-summer/day7/solution.pdf)
- [题面、样例与参考代码](/Blog/assets/solution/jiuguang-summer/day7/files.zip)

## Std 与数据

以下 Std 与数据来自 `D:\Codex\Competition\Summer\day7` 的正式工程，每题保留 $20$ 组正式输入与 $20$ 组答案。

| 题目 | 来源 | Std | 数据点 | 数据 |
| --- | --- | --- | --- | --- |
| 藿香正气液 | 原创 | [elixir.cpp](/Blog/assets/solution/jiuguang-summer/day7/std/elixir.cpp) | $20$ 组输入，$20$ 组答案 | [data-elixir.zip](/Blog/assets/solution/jiuguang-summer/day7/data-elixir.zip) |
| 晨汐散余香 | 原创 | [aroma.cpp](/Blog/assets/solution/jiuguang-summer/day7/std/aroma.cpp) | $20$ 组输入，$20$ 组答案 | [data-aroma.zip](/Blog/assets/solution/jiuguang-summer/day7/data-aroma.zip) |
| 灵舵渡千屿 | 改编自 [P13271 [NOI2025] 机器人](https://www.luogu.com.cn/problem/P13271) | [helm.cpp](/Blog/assets/solution/jiuguang-summer/day7/std/helm.cpp) | $20$ 组输入，$20$ 组答案 | [data-helm.zip](/Blog/assets/solution/jiuguang-summer/day7/data-helm.zip) |
| 沧溟探秘藏 | 改编自 [P3959 [NOIP 2017 提高组] 宝藏](https://www.luogu.com.cn/problem/P3959) | [treasure.cpp](/Blog/assets/solution/jiuguang-summer/day7/std/treasure.cpp) | $20$ 组输入，$20$ 组答案 | [data-treasure.zip](/Blog/assets/solution/jiuguang-summer/day7/data-treasure.zip) |

## 题目简述

### 藿香正气液

求满足 $1\le x<y\le n$ 且 $\gcd(x,y)=y-x$ 的整数对数量。

### 晨汐散余香

给定若干带价值与截止时间的物品，多次询问最多选择 $p_i$ 个交易日时的最大收益。

### 灵舵渡千屿

给定有序出边图与档位调整代价，初始位于点 $1$ 且档位为 $1$，求到每个点的最小代价。

### 沧溟探秘藏

给定带权无向图，选择任意起点逐层扩展所有点，每条边代价乘以扩展层数，求最小总代价。

## 题解

- [藿香正气液](elixir.md)
- [晨汐散余香](aroma.md)
- [灵舵渡千屿](helm.md)
- [沧溟探秘藏](treasure.md)
