# 第一试

本场为 NOIP 模拟赛第一试，比赛时间为 2026 年 7 月 27 日 14:00 至 17:30，出题人为 Ehundategh。

## 下发文件

- [题面 PDF 下载](/Blog/assets/solution/noip-mock/test1/statement.pdf)
- [题解 PDF 下载](/Blog/assets/solution/noip-mock/test1/solution.pdf)
- [选手下发文件下载](/Blog/assets/solution/noip-mock/test1/files.zip)
- [完整评测数据下载](/Blog/assets/solution/noip-mock/test1/judge-data.zip)

## 题目与数据

| 题目 | 来源 | 时限 | Std | 数据点 |
| --- | --- | --- | --- | --- |
| 糖果店 | 改编自 [CF1282B1 K for the Price of One](https://www.luogu.com.cn/problem/CF1282B1) | $1\ \mathrm{s}$ | [candy.cpp](/Blog/assets/solution/noip-mock/test1/std/candy.cpp) | $20$ 组输入，$20$ 组答案 |
| 清仓甩卖 | 削弱自 [CF808E Selling Souvenirs](https://www.luogu.com.cn/problem/CF808E) | $1\ \mathrm{s}$ | [sale.cpp](/Blog/assets/solution/noip-mock/test1/std/sale.cpp) | $25$ 组输入，$25$ 组答案 |
| 树的价值 | 原创 | $2\ \mathrm{s}$ | [tree.cpp](/Blog/assets/solution/noip-mock/test1/std/tree.cpp) | $25$ 组输入，$25$ 组答案 |
| 序列询问 | 加强自 [P15850 宝石](https://www.luogu.com.cn/problem/P15850) | $2\ \mathrm{s}$ | [query.cpp](/Blog/assets/solution/noip-mock/test1/std/query.cpp) | $20$ 组输入，$20$ 组答案 |

四题内存限制均为 $512\ \mathrm{MiB}$。

## 题目简述

### 糖果店

每个礼盒可以装入两颗糖果，并只按较贵者结算。给定预算与礼盒数量，求最多能够购买多少颗糖果。

### 清仓甩卖

每件物品的清仓价格只可能为 $1$ 或 $2$。在预算限制下选择若干物品，使其原价总和最大。

### 树的价值

依次探索有根树的全部叶子。每次新出现的结点构成一条链，并按照链顶权值与链长系数计算价值，求探索序列的最大总价值。

### 序列询问

对二进制序列的两个子段分别进行相邻相同元素消除，再拼接并继续消除。对每次区间询问，求所有分割点产生的新消除次数之和。

## 题解

- [糖果店](candy.md)
- [清仓甩卖](sale.md)
- [树的价值](tree.md)
- [序列询问](query.md)
