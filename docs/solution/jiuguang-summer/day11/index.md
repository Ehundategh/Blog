# 第十一天

本场为九光暑假第十一天训练赛，时间为 2026 年 8 月 1 日 14:00 至 17:30，出题人为 Ehundategh。

## 下发文件

- [题面 PDF 下载](/Blog/assets/solution/jiuguang-summer/day11/statement.pdf)
- [题解 PDF 下载](/Blog/assets/solution/jiuguang-summer/day11/solution.pdf)
- [题面与附加样例](/Blog/assets/solution/jiuguang-summer/day11/files.zip)

## Std 与数据

以下 Std 与数据来自 `D:\Codex\Competition\Summer\day11` 的正式工程。

| 题目 | 来源 | Std | 数据点 | 数据 |
| --- | --- | --- | --- | --- |
| 能量获取 | 改编自 [CF1526C2 Potions (Hard Version)](https://www.luogu.com.cn/problem/CF1526C2) | [select.cpp](/Blog/assets/solution/jiuguang-summer/day11/std/select.cpp) | $20$ 组输入，$20$ 组答案 | [data-select.zip](/Blog/assets/solution/jiuguang-summer/day11/data-select.zip) |
| 策划道路 | 改编自 [P9584「MXOI Round 1」城市](https://www.luogu.com.cn/problem/P9584) | [city.cpp](/Blog/assets/solution/jiuguang-summer/day11/std/city.cpp) | $20$ 组输入，$20$ 组答案 | [data-city.zip](/Blog/assets/solution/jiuguang-summer/day11/data-city.zip) |
| 异色飞羽 | 改编自 [P1972 [SDOI2009] HH 的项链](https://www.luogu.com.cn/problem/P1972) | [beads.cpp](/Blog/assets/solution/jiuguang-summer/day11/std/beads.cpp) | $25$ 组输入，$25$ 组答案 | [数据点 $1\sim 12$](/Blog/assets/solution/jiuguang-summer/day11/data-beads-1.zip)、[数据点 $13\sim 18$](/Blog/assets/solution/jiuguang-summer/day11/data-beads-2.zip)、[数据点 $19\sim 25$](/Blog/assets/solution/jiuguang-summer/day11/data-beads-3.zip) |
| 战争游戏 | 改编自 [P1084 [NOIP2012 提高组] 疫情控制](https://www.luogu.com.cn/problem/P1084) | [wargame.cpp](/Blog/assets/solution/jiuguang-summer/day11/std/wargame.cpp) | $25$ 组输入，$25$ 组答案 | [data-wargame.zip](/Blog/assets/solution/jiuguang-summer/day11/data-wargame.zip) |

## 题目简述

### 能量获取

按顺序处理带有正负能量变化的样本，在能量始终非负的限制下最大化获取数量。

### 策划道路

在一棵带权树上新增一座城市。对每个独立方案，求新增道路建成后全部有序城市对的距离和。

### 异色飞羽

给出一个颜色序列，多次询问区间内不同颜色的数量。

### 战争游戏

若干特工在带权树上同时移动并潜伏，要求截断根到全部叶子的路径，求最短时间。

## 题解

- [能量获取](select.md)
- [策划道路](city.md)
- [异色飞羽](beads.md)
- [战争游戏](wargame.md)
