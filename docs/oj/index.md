# 补题 OJ

这里收录可以在本地评测的补题题目。

第一版补题 OJ 不依赖服务器评测。网站负责提供题目索引、数据包与评测配置，本地评测器负责在选手机器上编译、运行、比对答案，并把记录保存在本机。

## 安装评测器

下载评测器：

- [gioush-judge-windows.zip](/Blog/assets/oj/gioush-judge-windows.zip)
- [gioush-judge.py](/Blog/assets/oj/gioush-judge.py)

需要本机已经安装：

- `g++`

检查方式：

```bash
g++ --version
```

Windows 下推荐下载 `gioush-judge-windows.zip`，解压后直接在目录中使用 `gioush-judge.cmd`。这个版本不需要 Python。

## 使用方式

评测一份 C++ 代码：

```bat
gioush-judge.cmd run jiuguang-day2-trade main.cpp
```

查看题目列表：

```bat
gioush-judge.cmd list
```

查看本地补题记录：

```bat
gioush-judge.cmd records
```

## Period 2：本地身份与评测报告

这一阶段仍然不依赖服务器。评测器可以在本机保存一个身份，并把最近一次评测结果导出成报告，方便之后人工收档或自行留存。

设置本地身份：

```bat
gioush-judge.cmd profile --name Ehundategh --handle Ehundategh
```

查看本地身份：

```bat
gioush-judge.cmd profile
```

导出某题最近一次评测报告：

```bat
gioush-judge.cmd export jiuguang-day2-wind --format md
gioush-judge.cmd export jiuguang-day2-wind --format json
```

默认报告会写入：

```text
~/.gioush-judge/exports/
```

## Period 3：Windows 下载即用包

这一阶段补上 Windows 版入口。压缩包中包含 `gioush-judge.cmd`、`gioush-judge.ps1` 与简短说明，解压后可以直接运行，不需要额外安装 Python。评测器仍然只在本机编译、运行和保存记录，网站只提供题目配置与数据包。

若需要指定本地题目配置，可以写成：

```bat
gioush-judge.cmd --manifest docs\oj\problems.json list
```

Python 版评测器仍然保留，已经习惯旧命令的机器可以继续使用：

```bash
python gioush-judge.py run jiuguang-day2-trade main.cpp
```

## 题目列表

### 九光暑假第一天

| 题号 | 题目 | 命令 |
| --- | --- | --- |
| `jiuguang-day1-road` | 道路建设 | `gioush-judge.cmd run jiuguang-day1-road main.cpp` |
| `jiuguang-day1-gather` | 相聚 | `gioush-judge.cmd run jiuguang-day1-gather main.cpp` |
| `jiuguang-day1-song` | 流光之歌 | `gioush-judge.cmd run jiuguang-day1-song main.cpp` |
| `jiuguang-day1-mount` | 峰翠铜炉 | `gioush-judge.cmd run jiuguang-day1-mount main.cpp` |

### 九光暑假第二天

| 题号 | 题目 | 命令 |
| --- | --- | --- |
| `jiuguang-day2-reset` | 归零 | `gioush-judge.cmd run jiuguang-day2-reset main.cpp` |
| `jiuguang-day2-escape` | 引力之阱 | `gioush-judge.cmd run jiuguang-day2-escape main.cpp` |
| `jiuguang-day2-trade` | 商路照影 | `gioush-judge.cmd run jiuguang-day2-trade main.cpp` |
| `jiuguang-day2-wind` | 逐风 | `gioush-judge.cmd run jiuguang-day2-wind main.cpp` |

## 评测说明

评测器会自动下载对应题目的数据包并缓存到本机。对于使用文件输入输出的代码，评测器会在运行目录中写入对应的 `.in` 文件；如果程序生成了 `.out` 文件，则优先使用该文件作为输出，否则使用标准输出。

输出比较采用按空白字符分割后的 token 比较。也就是说，行末空格与末尾换行不会影响结果。

本地记录位于：

```text
~/.gioush-judge/records.json
```

这一版只用于补题与自测，不用于可信比赛排名。
