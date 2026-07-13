# 补题 OJ

这里收录可以在本地评测的补题题目。网站负责提供题目索引、数据包与评测配置，本地评测器负责在选手机器上编译、运行、比对答案，并把账号、记录与报告保存在本机。

## 安装评测器

下载评测器：

- [gioush-judge-windows.zip](/Blog/assets/oj/gioush-judge-windows.zip)
- [gioush-judge.py](/Blog/assets/oj/gioush-judge.py)

Windows 下推荐下载 `gioush-judge-windows.zip`。解压后直接运行 `Gioush Judge.exe`，也可以继续使用命令行入口。这个版本不需要 Python。

需要本机已经安装：

- `g++`

检查方式：

```bash
g++ --version
```

## 可视化使用

在解压目录中运行：

```bat
Gioush Judge.exe
```

可以在软件中注册本地账号、登录、查看题目列表、选择源文件并直接 `Submit`。账号只保存在本机，不用于公网排名。

## 命令行使用

评测一份 C++ 代码：

```bat
gioush-judge.cmd run jiuguang-day2-trade main.cpp
```

查看题目列表：

```bat
gioush-judge.cmd list
```

设置本地身份：

```bat
gioush-judge.cmd profile --name Ehundategh --handle Ehundategh
```

导出某题最近一次评测报告：

```bat
gioush-judge.cmd export jiuguang-day2-wind --format md
gioush-judge.cmd export jiuguang-day2-wind --format json
```

默认记录与报告会写入：

```text
~/.gioush-judge/
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

这一版只用于补题与自测，不用于可信比赛排名。
