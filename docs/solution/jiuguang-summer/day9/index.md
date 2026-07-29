# 第九天

本场为九光暑假第九天训练赛，时间为 2026 年 7 月 28 日 14:00 至 17:30，出题人为 Ehundategh。

## 下发文件

- [题面 PDF 下载](/Blog/assets/solution/jiuguang-summer/day9/statement.pdf)
- [题解 PDF 下载](/Blog/assets/solution/jiuguang-summer/day9/solution.pdf)
- [题面与附加样例](/Blog/assets/solution/jiuguang-summer/day9/files.zip)

## Std 与数据

以下 Std 与数据来自 `D:\Codex\Competition\Summer\day9` 的正式工程。

| 题目 | 来源 | Std | 数据点 | 数据 |
| --- | --- | --- | --- | --- |
| 五轮启幽扉 | 改编自 [P9752 [CSP-S 2023] 密码锁](https://www.luogu.com.cn/problem/P9752) | [lock.cpp](/Blog/assets/solution/jiuguang-summer/day9/std/lock.cpp) | $20$ 组输入，$20$ 组答案 | [data-lock.zip](/Blog/assets/solution/jiuguang-summer/day9/data-lock.zip) |
| 双径会深庭 | 改编自 [P3398 仓鼠找 sugar](https://www.luogu.com.cn/problem/P3398) | [cross.cpp](/Blog/assets/solution/jiuguang-summer/day9/std/cross.cpp) | $20$ 组输入，$20$ 组答案 | [data-cross.zip](/Blog/assets/solution/jiuguang-summer/day9/data-cross.zip) |
| 星脉聚流光 | 改编自 [P1447 [NOI2010] 能量采集](https://www.luogu.com.cn/problem/P1447) | [energy.cpp](/Blog/assets/solution/jiuguang-summer/day9/std/energy.cpp) | $25$ 组输入，$25$ 组答案 | [data-energy.zip](/Blog/assets/solution/jiuguang-summer/day9/data-energy.zip) |
| 重彩书遗年 | 改编自 [CF2237F Paint the Array](https://www.luogu.com.cn/problem/CF2237F) | [paint.cpp](/Blog/assets/solution/jiuguang-summer/day9/std/paint.cpp) | $25$ 组输入，$25$ 组答案 | [data-paint.zip](/Blog/assets/solution/jiuguang-summer/day9/data-paint.zip) |

## 题目简述

### 五轮启幽扉

给出若干个五位转轮状态，求有多少个原始密钥能够分别通过一次单轮试拨或相邻双轮同步试拨得到全部状态。

### 双径会深庭

给定一棵树，多次询问两条简单路径是否至少经过同一个结点。

### 星脉聚流光

统计矩形整点中各点到原点的连线所经过的内部整点数量，并求全部传输损失之和。

### 重彩书遗年

每次可以把一个长度为 $m$ 的区间依次覆写为 $1,2,\ldots,m$，求把给定序列修改成某个可生成序列的最少修改次数。

## 题解

- [五轮启幽扉](lock.md)
- [双径会深庭](cross.md)
- [星脉聚流光](energy.md)
- [重彩书遗年](paint.md)
