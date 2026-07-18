# 第五天

本场为九光暑假第五天训练赛，时间为 2026 年 7 月 17 日 14:00 至 17:30，出题人为 Ehundategh。

## 下发文件

- [题面 PDF 下载](/Blog/assets/solution/jiuguang-summer/day5/statement.pdf)
- [题解 PDF 下载](/Blog/assets/solution/jiuguang-summer/day5/solution.pdf)
- [题面、样例与参考代码](/Blog/assets/solution/jiuguang-summer/day5/files.zip)

## Std 与数据

以下 Std 来自 `D:\Code and Problem\7.17`，数据包来自对应题目的正式数据目录，并保留 `.in`、`.ans` 与 `std.cpp`。

| 题目 | 来源 | Std | 数据点 | 数据 |
| --- | --- | --- | --- | --- |
| 我流奥义 | 原创 | [smoke.cpp](/Blog/assets/solution/jiuguang-summer/day5/std/smoke.cpp) | $20$ 组输入，$20$ 组答案 | [data-smoke.zip](/Blog/assets/solution/jiuguang-summer/day5/data-smoke.zip) |
| 星语楠尘 | 改编自 [CF763A Timofey and a tree](https://www.luogu.com.cn/problem/CF763A) | [stardust.cpp](/Blog/assets/solution/jiuguang-summer/day5/std/stardust.cpp) | $20$ 组输入，$20$ 组答案 | [data-stardust.zip](/Blog/assets/solution/jiuguang-summer/day5/data-stardust.zip) |
| 日月风随 | 原创 | [solwind.cpp](/Blog/assets/solution/jiuguang-summer/day5/std/solwind.cpp) | $25$ 组输入，$25$ 组答案 | [data-solwind.zip](/Blog/assets/solution/jiuguang-summer/day5/data-solwind.zip) |
| 推翻暴政 | 原创 | [revolt.cpp](/Blog/assets/solution/jiuguang-summer/day5/std/revolt.cpp) | $25$ 组输入，$25$ 组答案 | [data-revolt.zip](/Blog/assets/solution/jiuguang-summer/day5/data-revolt.zip) |

## 题目简述

### 我流奥义

平面上有若干灌木丛，烟雾从原点向所有方向扩散到半径 $r$。同一条从原点出发的射线上只会标记最近的灌木丛；若原点本身有灌木丛，则只标记原点。求被标记的数量。

### 星语楠尘

给定一棵带颜色的树。选择一个根后，要求每个非根结点对应的子树都同色。判断是否存在合法根，并输出任意一个。

### 日月风随

给定序列 $h_i$。可以先花费代价把若干位置削弱，再选择一个位置投入强度 $x$ 触发一次向两侧递减传播的仪式。要求最终所有位置都被解开，求最小总消耗。

### 推翻暴政

奇数个同伴按顺序到达渡口。每轮新到两人，与上一轮留下的一人组成三人，从中选两人过河，代价为二者时间最大值，最后剩下一人独自过河。求最小总代价。

## 题解

- [我流奥义](smoke.md)
- [星语楠尘](stardust.md)
- [日月风随](solwind.md)
- [推翻暴政](revolt.md)
