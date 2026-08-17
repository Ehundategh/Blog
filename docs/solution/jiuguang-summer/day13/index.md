# 第十三天

本场为九光暑假第十三天训练赛，时间为 2026 年 8 月 16 日 14:00 至 17:30，出题人为 Ehundategh。

## 下发文件

- [题面 PDF 下载](/Blog/assets/solution/jiuguang-summer/day13/statement.pdf)
- [题解 PDF 下载](/Blog/assets/solution/jiuguang-summer/day13/solution.pdf)
- [题面与交互题公开文件](/Blog/assets/solution/jiuguang-summer/day13/files.zip)

## Std 与数据

| 题目 | 来源 | Std | 数据点 | 数据 |
| --- | --- | --- | --- | --- |
| 天地皆可往 | 改编自 [CF1203F1 Complete the Projects (easy version)](https://www.luogu.com.cn/problem/CF1203F1) | [roam.cpp](/Blog/assets/solution/jiuguang-summer/day13/std/roam.cpp) | $20$ 组输入，$20$ 组答案 | [data-roam.zip](/Blog/assets/solution/jiuguang-summer/day13/data-roam.zip) |
| 单舟见京杭 | 原创 | [canal.cpp](/Blog/assets/solution/jiuguang-summer/day13/std/canal.cpp) | $4$ 组交互数据 | [data-canal.zip](/Blog/assets/solution/jiuguang-summer/day13/data-canal.zip) |
| 新水濯旧隍 | 原创 | [moat.cpp](/Blog/assets/solution/jiuguang-summer/day13/std/moat.cpp) | $4$ 组交互数据 | [data-moat.zip](/Blog/assets/solution/jiuguang-summer/day13/data-moat.zip) |
| 云止聆佳响 | 原创 | [echo.cpp](/Blog/assets/solution/jiuguang-summer/day13/std/echo.cpp) | $20$ 组输入，$20$ 组答案 | [data-echo.zip](/Blog/assets/solution/jiuguang-summer/day13/data-echo.zip) |

## 题目简述

### 天地皆可往

每个任务具有进入门槛 $a_i$ 与完成后的能力变化 $b_i$，要求安排全部任务的顺序，并最小化初始能力。

### 单舟见京杭

在 $n$ 组左右景观中恰有两处表示同一景观。每次可指定全部选择并得到不同景观的价值和，要求在有限次询问内定位这两处景观。

### 新水濯旧隍

树上每个结点具有未知权值。每轮可以查询子树剩余权值和，再清空一个结点，要求在查询次数限制内取得足够多的总权值。

### 云止聆佳响

在一条祖先链上选择若干结点，要求相邻音高不同且升降方向改变次数不超过 $k$，最大化权值和。

## 交互题公开文件

### 单舟见京杭

- [canal.h](/Blog/assets/solution/jiuguang-summer/day13/canal/canal.h)
- [grader.cpp](/Blog/assets/solution/jiuguang-summer/day13/canal/grader.cpp)
- [template_canal.cpp](/Blog/assets/solution/jiuguang-summer/day13/canal/template_canal.cpp)

### 新水濯旧隍

- [moat.h](/Blog/assets/solution/jiuguang-summer/day13/moat/moat.h)
- [grader.cpp](/Blog/assets/solution/jiuguang-summer/day13/moat/grader.cpp)
- [template_moat.cpp](/Blog/assets/solution/jiuguang-summer/day13/moat/template_moat.cpp)

## 题解

- [天地皆可往](roam.md)
- [单舟见京杭](canal.md)
- [新水濯旧隍](moat.md)
- [云止聆佳响](echo.md)
