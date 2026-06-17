# 第一天

本场为九光暑假第一天训练赛，出题人为 Ehundategh。当前题面 PDF 中的日期为暂定，最终时间以正式发布版本为准。

## 下发文件

- [题面 PDF 下载](/Blog/assets/solution/jiuguang-summer/day1/statement.pdf)
- [题面、样例与参考代码](/Blog/assets/solution/jiuguang-summer/day1/files.zip)

## Std 与数据

以下数据包来自对应含有 `datamaker.cpp` 的题目目录，并保留 `.in`、`.ans`、`datamaker.cpp` 与 `std.cpp`。

| 题目 | Std | 数据点 | 数据 |
| --- | --- | --- | --- |
| 道路建设 | [road.cpp](/Blog/assets/solution/jiuguang-summer/day1/std/road.cpp) | 当前目录未找到 `road` 数据目录 |  |
| 相聚 | [gather.cpp](/Blog/assets/solution/jiuguang-summer/day1/std/gather.cpp) | $20$ 组输入，$20$ 组答案 | [data-gather.zip](/Blog/assets/solution/jiuguang-summer/day1/data-gather.zip) |
| 流光之歌 | [song.cpp](/Blog/assets/solution/jiuguang-summer/day1/std/song.cpp) | $20$ 组输入，$20$ 组答案 | [data-song.zip](/Blog/assets/solution/jiuguang-summer/day1/data-song.zip) |
| 峰翠铜炉 | [mount.cpp](/Blog/assets/solution/jiuguang-summer/day1/std/mount.cpp) | $25$ 组输入，$25$ 组答案 | [data-mount.zip](/Blog/assets/solution/jiuguang-summer/day1/data-mount.zip) |

## 题目简述

### 道路建设

给定序列 $\{d_i\}$，每次可以选择一段所有数均大于 $0$ 的连续区间并整体减一，要求将整个序列清零的最少操作次数。

### 相聚

给定一棵带边权的树。每次询问给出 $2$ 或 $3$ 个点，要求选择一个集合点，使这些点到集合点的距离和最小。

### 流光之歌

给定歌魔声音 $T$ 和若干成员声音 $S_i$。每次询问给出不可用前缀长度，比较忽略该前缀后的最长公共前缀，并输出最优成员编号。

### 峰翠铜炉

给定有向带权图和若干心仪建设地，可以将至多 $a$ 条边修建为代价 $0$ 的索道，要求选择两个不同心仪建设地并最小化逃难时间。

## 题解

- [道路建设](road.md)
- [相聚](gather.md)
- [流光之歌](song.md)
- [峰翠铜炉](mount.md)
