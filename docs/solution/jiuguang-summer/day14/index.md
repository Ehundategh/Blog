# 第十四天

本场为九光暑假第十四天训练赛，时间为 2026 年 8 月 17 日 14:00 至 17:30，出题人为 Ehundategh。

## 下发文件

- [题面 PDF 下载](/Blog/assets/solution/jiuguang-summer/day14/statement.pdf)
- [第十四天下发文件下载](/Blog/assets/solution/jiuguang-summer/day14/files.zip)

## Std 与数据

| 题目 | 来源 | Std | 数据点 | 数据 |
| --- | --- | --- | --- | --- |
| 挑战不被发现 | 原创 | [apt.cpp](/Blog/assets/solution/jiuguang-summer/day14/std/apt.cpp) | $20$ 组输入，$20$ 组答案 | [data-apt.zip](/Blog/assets/solution/jiuguang-summer/day14/data-apt.zip) |
| 卡牌游戏 | 原创 | [poker.cpp](/Blog/assets/solution/jiuguang-summer/day14/std/poker.cpp) | $20$ 组输入，$20$ 组答案 | [data-poker.zip](/Blog/assets/solution/jiuguang-summer/day14/data-poker.zip) |
| 康神开播了 | 改编自 [P16968 [SCCPC 2026] 博德之跃 3](https://www.luogu.com.cn/problem/P16968) | [kskbl.cpp](/Blog/assets/solution/jiuguang-summer/day14/std/kskbl.cpp) | $20$ 组输入，$20$ 组答案 | [data-kskbl.zip](/Blog/assets/solution/jiuguang-summer/day14/data-kskbl.zip) |
| A 病毒 | 削弱自 [P10789 [NOI2024] 登山](https://www.luogu.com.cn/problem/P10789) | [cancer.cpp](/Blog/assets/solution/jiuguang-summer/day14/std/cancer.cpp) | $20$ 组输入，$20$ 组答案 | [data-cancer.zip](/Blog/assets/solution/jiuguang-summer/day14/data-cancer.zip) |

## 题目简述

### 挑战不被发现

至多反转一次字符串区间，最小化子串 `APT` 的出现次数。

### 卡牌游戏

两人轮流删除正面值或背面值相同的两张卡牌，无法操作者失败，判断先手是否必胜。

### 康神开播了

每次取出当前字符串首字符、尾字符，或在 $S=ABA^R$ 时取出 $A$ 并保留 $B$，求能够得到的字典序最小字符串。

### A 病毒

病毒在树上进行向上跳跃或向下移动，并受到此前经过结点的限制。求从每个非根结点出发到达根的合法路径数量。

## 题解

- [挑战不被发现](apt.md)
- [卡牌游戏](poker.md)
- [康神开播了](kskbl.md)
- [A 病毒](cancer.md)
