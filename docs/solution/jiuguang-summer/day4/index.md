# 第四天

本场为九光暑假第四天训练赛，时间为 2026 年 7 月 16 日 14:00 至 17:30，出题人为 Ehundategh。

## 下发文件

- [题面 PDF 下载](/Blog/assets/solution/jiuguang-summer/day4/statement.pdf)
- [题解 PDF 下载](/Blog/assets/solution/jiuguang-summer/day4/solution.pdf)
- [题面、样例与参考代码](/Blog/assets/solution/jiuguang-summer/day4/files.zip)

## Std 与数据

以下 Std 来自 `D:\Code and Problem\7.16`，数据包来自对应题目的正式数据目录，并保留 `.in`、`.ans` 与 `std.cpp`。

| 题目 | 来源 | Std | 数据点 | 数据 |
| --- | --- | --- | --- | --- |
| 灰蕈迷境 | 原创 | [spore.cpp](/Blog/assets/solution/jiuguang-summer/day4/std/spore.cpp) | $20$ 组输入，$20$ 组答案 | [data-spore.zip](/Blog/assets/solution/jiuguang-summer/day4/data-spore.zip) |
| 银淞止境 | 原创 | [rime.cpp](/Blog/assets/solution/jiuguang-summer/day4/std/rime.cpp) | $25$ 组输入，$25$ 组答案 | [data-rime.zip](/Blog/assets/solution/jiuguang-summer/day4/data-rime.zip) |
| 无终奇语 | 原创 | [fable.cpp](/Blog/assets/solution/jiuguang-summer/day4/std/fable.cpp) | $20$ 组输入，$20$ 组答案 | [data-fable.zip](/Blog/assets/solution/jiuguang-summer/day4/data-fable.zip) |
| 黑流树海 | 原创 | [tide.cpp](/Blog/assets/solution/jiuguang-summer/day4/std/tide.cpp) | $25$ 组输入，$25$ 组答案 | [data-tide-part1.zip](/Blog/assets/solution/jiuguang-summer/day4/data-tide-part1.zip)，[data-tide-part2.zip](/Blog/assets/solution/jiuguang-summer/day4/data-tide-part2.zip) |

!!! note "黑流树海数据包说明"
    `tide` 的完整数据超过 GitHub 单文件限制，因此拆为两份：`part1` 包含测试点 $1\sim 15$，`part2` 包含测试点 $16\sim 25$。

## 题目简述

### 灰蕈迷境

给定若干段幻境，每段需要当前清明值至少为 $a_i$，完成后清明值变为 $x-a_i+b_i$。可以任意排列进入顺序，求能够完成所有幻境的最小初始清明值。

### 银淞止境

给定带权无向图、关键观测站集合、核心点 $s$ 与额度 $c$。要求选出一棵生成树，使每个关键观测站度数为 $1$，且最多 $c$ 个关键观测站直接连向 $s$，求最小边权和。

### 无终奇语

给定正整数序列 $h_i$。可以选择一个长度不超过 $k$ 的连续区间直接斩杀，再额外造成不超过 $c$ 的伤害；被攻击过的士兵必须构成一个连续区间。求可攻击区间的最大长度。

### 黑流树海

给定一棵带权树与 $k$ 个关键点。对于每个起点 $u$，求从 $u$ 出发访问所有关键点且不要求回到起点的最小路程。

## 题解

- [灰蕈迷境](spore.md)
- [银淞止境](rime.md)
- [无终奇语](fable.md)
- [黑流树海](tide.md)
