# Gioush OI Website

这是一个仿 OI Wiki 信息架构的个人算法博客，使用 MkDocs 和 Material for MkDocs 构建。

## 本地预览

```bash
pip install -r requirements.txt
mkdocs serve
```

默认访问地址为 <http://127.0.0.1:8000/>。

## 发布到 GitHub Pages

1. 将 `Blog` 目录作为仓库根目录推送到 GitHub。
2. 在仓库设置中启用 Pages，来源选择 GitHub Actions。
3. 推送到 `main` 或 `master` 后，工作流会自动构建并发布站点。

## 内容组织

- `docs/data-structure/`：数据结构。
- `docs/string/`：字符串。
- `docs/dp/`：动态规划。
- `docs/graph/`：图论。
- `docs/geometry/`：计算几何。
- `docs/solution/`：题目以及题解。
- `docs/misc/`：杂项。
