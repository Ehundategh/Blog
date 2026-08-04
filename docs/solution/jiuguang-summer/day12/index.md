# 第十二天

本场为九光暑假第十二天训练赛，时间为 2026 年 8 月 3 日 14:00 至 17:30，出题人为 Ehundategh。

## 下发文件

- [题面 PDF 下载](/Blog/assets/solution/jiuguang-summer/day12/statement.pdf)
- [题解 PDF 下载](/Blog/assets/solution/jiuguang-summer/day12/solution.pdf)
- [题面、附加样例与交互题公开文件](/Blog/assets/solution/jiuguang-summer/day12/files.zip)

## Std 与数据

以下 Std 与数据均来自本场正式工程。

| 题目 | 来源 | Std | 数据点 | 数据 |
| --- | --- | --- | --- | --- |
| 抢修计划 | 改编自 [CF1914C Quests](https://www.luogu.com.cn/problem/CF1914C) | [repair.cpp](/Blog/assets/solution/jiuguang-summer/day12/std/repair.cpp) | $20$ 组输入，$20$ 组答案 | [data-repair.zip](/Blog/assets/solution/jiuguang-summer/day12/data-repair.zip) |
| 风眼定位 | 改编自 [CF1486C1 Guessing the Greatest](https://www.luogu.com.cn/problem/CF1486C1) | [locate.cpp](/Blog/assets/solution/jiuguang-summer/day12/std/locate.cpp) | $3$ 组交互数据 | [data-locate.zip](/Blog/assets/solution/jiuguang-summer/day12/data-locate.zip) |
| 环锁解除 | 改编自 [P12406「CZOI-R3」消除序列](https://www.luogu.com.cn/problem/P12406) | [circle.cpp](/Blog/assets/solution/jiuguang-summer/day12/std/circle.cpp) | $25$ 组输入，$25$ 组答案 | [data-circle.zip](/Blog/assets/solution/jiuguang-summer/day12/data-circle.zip) |
| 风暴止息 | 改编自 [P3750 [六省联考 2017] 分手是祝愿](https://www.luogu.com.cn/problem/P3750) | [calm.cpp](/Blog/assets/solution/jiuguang-summer/day12/std/calm.cpp) | $25$ 组输入，$25$ 组答案 | [data-calm.zip](/Blog/assets/solution/jiuguang-summer/day12/data-calm.zip) |

## 题目简述

### 抢修计划

依次开放抢修区域。首次完成区域 $i$ 获得 $a_i$，重复抢修获得 $b_i$，求不超过 $k$ 次行动的最大总价值。

### 风眼定位

这是一道函数交互题。每次可以询问一个区间内次大值的位置，要求在不超过 $40$ 次询问内确定全局最大值的位置。

### 环锁解除

两个排列在环上移动。旋转方向具有不同代价，并允许交换两种方向的代价，求按给定顺序解除全部符号的最小总代价。

### 风暴止息

每次随机启动一个控制阵式；当局面的最少操作数不超过 $k$ 时改用最优方案。求总操作次数期望乘以 $n!$ 后的值。

## 风眼定位公开文件

- [locate.h](/Blog/assets/solution/jiuguang-summer/day12/locate/locate.h)
- [grader.cpp](/Blog/assets/solution/jiuguang-summer/day12/locate/grader.cpp)
- [template_locate.cpp](/Blog/assets/solution/jiuguang-summer/day12/locate/template_locate.cpp)
- [Windows 编译说明](/Blog/assets/solution/jiuguang-summer/day12/locate/Windows-Compile-Guide.txt)

## 题解

- [抢修计划](repair.md)
- [风眼定位](locate.md)
- [环锁解除](circle.md)
- [风暴止息](calm.md)
