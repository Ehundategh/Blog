# 第十天

本场为九光暑假第十天训练赛，时间为 2026 年 7 月 30 日 14:00 至 17:30，出题人为 Ehundategh。

## 下发文件

- [题面 PDF 下载](/Blog/assets/solution/jiuguang-summer/day10/statement.pdf)
- [题解 PDF 下载](/Blog/assets/solution/jiuguang-summer/day10/solution.pdf)
- [题面与附加样例](/Blog/assets/solution/jiuguang-summer/day10/files.zip)

## Std 与数据

以下 Std 与数据来自 `D:\Codex\Competition\Summer\day10` 的正式工程。

| 题目 | 来源 | Std | 数据点 | 数据 |
| --- | --- | --- | --- | --- |
| 员题 | 改编自 [P1650 田忌赛马](https://www.luogu.com.cn/problem/P1650) | [race.cpp](/Blog/assets/solution/jiuguang-summer/day10/std/race.cpp) | $10$ 组输入，$10$ 组答案 | [data-race.zip](/Blog/assets/solution/jiuguang-summer/day10/data-race.zip) |
| 翻转字符 | 改编自 [CF1430E String Reversal](https://www.luogu.com.cn/problem/CF1430E) | [flip.cpp](/Blog/assets/solution/jiuguang-summer/day10/std/flip.cpp) | $10$ 组输入，$10$ 组答案 | [data-flip.zip](/Blog/assets/solution/jiuguang-summer/day10/data-flip.zip) |
| 战争 | 改编自 [P10648 NordicOI 2023 Island Alliances](https://www.luogu.com.cn/problem/P10648) | [war.cpp](/Blog/assets/solution/jiuguang-summer/day10/std/war.cpp) | $30$ 组输入，$30$ 组答案 | [data-war.zip](/Blog/assets/solution/jiuguang-summer/day10/data-war.zip) |
| 我们最好的最短路 | 改编自 [CF1051F The Shortest Statement](https://www.luogu.com.cn/problem/CF1051F) | [shortest.cpp](/Blog/assets/solution/jiuguang-summer/day10/std/shortest.cpp) | $10$ 组输入，$10$ 组答案 | [data-shortest.zip](/Blog/assets/solution/jiuguang-summer/day10/data-shortest.zip) |

## 题目简述

### 员题

给出双方各 $n$ 匹马的速度，在一一配对比赛的条件下，最大化胜场数与负场数之差。

### 翻转字符

只允许交换相邻字符，求把一个字符串的翻转串变回原串所需的最少交换次数。

### 战争

维护不断合并的联盟。每次合并前，需要判断两个联盟之间是否存在一对初始敌对的参与者。

### 我们最好的最短路

给出一张满足 $m-n\leq 20$ 的连通无向图，多次询问两点之间的最短路。

## 题解

- [员题](race.md)
- [翻转字符](flip.md)
- [战争](war.md)
- [我们最好的最短路](shortest.md)
