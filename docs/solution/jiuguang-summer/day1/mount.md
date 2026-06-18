# 峰翠铜炉

## 题目简述

给定一张有向带权图，其中有 $k$ 个心仪建设地。我们需要选择两个不同的心仪建设地作为起点和终点，并选择至多 $a$ 条边修建索道，使这些边的代价视为 $0$，要求最小化从起点到终点的逃难时间。

## 第一档部分分

首先最好分析的是 $k=2$ 的情况。此时起点和终点已经固定，只需要考虑从其中一个点到另一个点的最短路。由于图是有向图，两个方向都需要尝试。

接下来考虑如何处理可以免费经过至多 $a$ 条边的问题。观察到 $a$ 很小，最大只有 $5$，所以可以使用分层图最短路。

具体做法如下：

1. 建出 $a+1$ 层原图，第 $i$ 层表示已经使用了 $i$ 条免费边。
2. 对于原图中的每条边 $u\to v$，在每一层内连边 $(u,i)\to(v,i)$，边权为原边权。
3. 如果 $i<a$，再连一条跨层边 $(u,i)\to(v,i+1)$，边权为 $0$，表示把这条边修成索道。

![峰翠铜炉中的分层图：跨层边表示使用一条免费索道](/Blog/assets/solution/jiuguang-summer/day1/solution_layered.svg)

这样，每向下一层走一次，就代表使用了一条免费边。对固定起点跑一遍 $\texttt{Dijkstra}$，取终点在所有层中的最小距离即可。

对两个方向各跑一次最短路。时间复杂度为：

$$
\mathcal{O}\left(2ma\log(na)\right)
$$

空间复杂度为 $\mathcal{O}(ma)$。

## 第二档部分分

此时 $a=0$，也就是不需要考虑索道，只需要处理 $k$ 很大的问题。

一个自然的想法是多源最短路。把所有心仪建设地同时放入优先队列中，并记录每个状态来自哪个心仪建设地。每次从队列中取出一个点 $u$，若沿边到达某个点时遇到了来自不同源的路径，就可以尝试用两条路径拼出一对心仪建设地之间的最短距离。

但是单纯维护最短路会漏情况，因为一个点的最短路和次短路可能来自同一个心仪建设地。为了保证拼出的两个端点不同，需要对每个点维护来自不同源的最短和次短信息。

这样可以求出没有索道时任意两个心仪建设地之间最短路径的最小值。

## 正解

现在同时考虑 $k$ 很大和 $a$ 很小。

题目并不要求我们输出到底选择了哪两个心仪建设地，只需要知道最短逃难时间。因此我们可以考虑分组。

对于一次分组，将心仪建设地分为 $\texttt{A}$、$\texttt{B}$ 两组。建立超级源点 $\texttt{S}$ 和超级汇点 $\texttt{T}$：

- 从 $\texttt{S}$ 向 $\texttt{A}$ 组中的所有心仪建设地连边，边权为 $0$。
- 从 $\texttt{B}$ 组中的所有心仪建设地向 $\texttt{T}$ 连边，边权为 $0$。

然后在这张图上跑分层图最短路。得到的 $\operatorname{Dist}_T$ 就是从 $\texttt{A}$ 组任意一个心仪建设地到 $\texttt{B}$ 组任意一个心仪建设地，并且最多使用 $a$ 条免费边时的最短距离。

问题变成：如何保证任意一对不同的心仪建设地都曾经被分到不同的两组中？

使用二进制分组即可。把每个心仪建设地的编号或其在心仪点列表中的下标看成二进制数。对于每一位，将这一位为 $0$ 的点放入 $\texttt{A}$，这一位为 $1$ 的点放入 $\texttt{B}$。任意两个不同点在二进制下必然至少有一位不同，所以它们一定会在某一次分组中被分开。

由于图是有向图，还需要反过来再做一次，即把原来的 $\texttt{A}$、$\texttt{B}$ 对调。这样才能同时覆盖从 $\texttt{A}$ 到 $\texttt{B}$ 和从 $\texttt{B}$ 到 $\texttt{A}$ 的方向。

每次分组跑一遍分层图 $\texttt{Dijkstra}$，取所有分组结果的最小值即为答案。

## 复杂度

分组次数为 $\mathcal{O}(\log k)$，每次需要跑一次分层图最短路，且每一位需要考虑两个方向。

时间复杂度为：

$$
\mathcal{O}\left(\log k\cdot ma\log(na)\right)
$$

空间复杂度为 $\mathcal{O}(ma)$。

## 参考代码

```cpp
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 500010
#define MAXM 1000010
using namespace std;
int Head[MAXN],Total=0,S,T,n,m,k,Dist[MAXN],In1[MAXM],In2[MAXM],In3[MAXM],a,Mark[MAXN][7],cnm=0;
int Key[MAXN];
bool Visited[MAXN];
struct edge{
    int St,Ed;
    int Next,Value;
}Edge[MAXM<<2];
void Edge_Add(int St,int Ed,int Value){
    Edge[++Total]={St,Ed,Head[St],Value};
    Head[St]=Total;
}
priority_queue<pair<int,int>,vector<pair<int,int>>,greater< pair<int,int>>> Q;
void Dijkstra(){
    memset(Visited,0,sizeof(Visited));
    memset(Dist,0x3f,sizeof(Dist));
    Q.emplace(0,S);Dist[S]=0;
    while(!Q.empty()){
        int Now=Q.top().second;Q.pop();
        if(Visited[Now]) continue;
        Visited[Now]=true;
        for(int i=Head[Now];i;i=Edge[i].Next){
            int To=Edge[i].Ed;
            if(Dist[To]>Dist[Now]+Edge[i].Value){
                Dist[To]=Dist[Now]+Edge[i].Value;
                Q.emplace(Dist[To],To);
            }
        }
    }
}
void Solve(){
    int In,Ans=1<<30;
    for(int i=1;i<=k;i++) scanf("%d",&Key[i]);
    for(int j=1;j<=a+1;j++){
        for(int i=1;i<=n;i++){
            Mark[i][j]=++cnm;
        }
    }
    S=++cnm; T=++cnm;
    int Temp=1<<16;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&In1[i],&In2[i],&In3[i]);
    }
    while(Temp){
        memset(Head,0,sizeof(Head));Total=0;
        for(int i=1;i<=m;i++){
            for(int j=1;j<=a+1;j++){
                Edge_Add(Mark[In1[i]][j],Mark[In2[i]][j],In3[i]);
                if(j<a+1) Edge_Add(Mark[In1[i]][j],Mark[In2[i]][j+1],0);
            }
        }
        for(int i=1;i<=k;i++){
            if(Key[i]&Temp){
                for(int j=1;j<=a+1;j++){
                    Edge_Add(Mark[Key[i]][j],T,0);
                }
            }
            else Edge_Add(S,Mark[Key[i]][1],0);
        }
        Dijkstra();
        Ans=min(Ans,Dist[T]);
        memset(Head,0,sizeof(Head));Total=0;
        for(int i=1;i<=m;i++){
            for(int j=1;j<=a+1;j++){
                Edge_Add(Mark[In1[i]][j],Mark[In2[i]][j],In3[i]);
                if(j<a+1) Edge_Add(Mark[In1[i]][j],Mark[In2[i]][j+1],0);
            }
        }
        for(int i=1;i<=k;i++){
            if(!(Key[i]&Temp)){
                for(int j=1;j<=a+1;j++){
                    Edge_Add(Mark[Key[i]][j],T,0);
                }
            }
            else Edge_Add(S,Mark[Key[i]][1],0);
        }
        Dijkstra();
        Ans=min(Ans,Dist[T]);
        Temp>>=1;
    }
    printf("%lld\n",Ans);
}
int main(){
    scanf("%d%d%d%d",&n,&m,&k,&a);
    Solve();
    return 0;
}
```
