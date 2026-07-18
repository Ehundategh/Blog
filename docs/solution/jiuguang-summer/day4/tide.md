# 黑流树海

## 题意简述

给定一棵带权树与 $k$ 个关键点。对于每个起点 $u$，求从 $u$ 出发访问所有关键点且不要求回到起点的最小路程。

## 部分分

若固定起点，必须经过连接所有关键点与起点的最小连通子树。若所有边都需要走完并返回，代价是子树边权和的两倍；由于最后不需要返回，可以省去从起点到某个关键点的最长距离。

## 正解

设 $F(u)$ 表示从 $u$ 出发时需要覆盖的最小子树边权和的两倍，设 $D(u)$ 表示 $u$ 到关键点的最远距离，则答案为 $F(u)-D(u)$。第一次 DFS 以 $1$ 为根，求每个子树内关键点数量、子树贡献与向下最远关键点距离。第二次 DFS 换根，维护父侧是否含有关键点，以及来自父侧的最远距离。这样每个点都能得到完整的 $F(u)$ 与 $D(u)$。

## 复杂度

两次 DFS 均只经过每条边常数次，时间复杂度为 $\mathcal{O}(n)$，空间复杂度为 $\mathcal{O}(n)$。距离与答案需要使用 `long long`。

## 参考代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 500100
using namespace std;
int Head[MAXN],Total=0,n,m,k;
long long Dp[MAXN],Size[MAXN],Dis[MAXN][2],Ans[MAXN],F[MAXN];
bool Key[MAXN];
struct edge{
    int St,Ed,Next;
    int Value;
}Edge[MAXN<<1];
void Edge_Add(int St,int Ed,int Value){
    Edge[++Total]={St,Ed,Head[St],Value};
    Head[St]=Total;
}
void DFS(int Now,int From){
    if(Key[Now]) Size[Now]=1;
    else Size[Now]=0;
    for(int i=Head[Now];i;i=Edge[i].Next){
        int To=Edge[i].Ed;
        if(To==From) continue;
        DFS(To,Now);
        Size[Now]+=Size[To];
        if(Size[To]){
            Dp[Now]+=2*Edge[i].Value+Dp[To];
            if(Dis[To][0]+Edge[i].Value>Dis[Now][0]){
                Dis[Now][1]=Dis[Now][0];
                Dis[Now][0]=Dis[To][0]+Edge[i].Value;
            }
            else if(Dis[To][0]+Edge[i].Value>Dis[Now][1]){
                Dis[Now][1]=Dis[To][0]+Edge[i].Value;
            }
        }
    }
}
void Dynamic(int Now,int From,int LastLen){
    if(Now==1) Ans[Now]=Dp[Now]-Dis[Now][0],F[1]=Dp[1];
    else{
        if(Size[Now]==0) F[Now]=F[From]+2*LastLen;
        else if(k-Size[Now]==0) F[Now]=Dp[Now];
        else F[Now]=F[From];
        long long NowD;
        if(Size[Now]&&Dis[From][0]==LastLen+Dis[Now][0]){
            NowD=Dis[From][1]+LastLen;
            if(Dis[From][1]==0&&!Key[From]) NowD=-1;
        }
        else NowD=Dis[From][0]+LastLen;
        if(NowD>Dis[Now][0]){
            Dis[Now][1]=Dis[Now][0];
            Dis[Now][0]=NowD;
        }
        else if(NowD>Dis[Now][1]){
            Dis[Now][1]=NowD;
        }
        Ans[Now]=F[Now]-Dis[Now][0];
    }
    for(int i=Head[Now];i;i=Edge[i].Next){
        int To=Edge[i].Ed;
        if(To==From) continue;
        Dynamic(To,Now,Edge[i].Value);
    }
    return ;
}
int main(){
    freopen("tide.in","r",stdin);
    freopen("tide.out","w",stdout);
    int In1,In2,In3;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n-1;i++){
        scanf("%d%d%d",&In1,&In2,&In3);
        Edge_Add(In1,In2,In3);
        Edge_Add(In2,In1,In3);
    }
    for(int i=1;i<=k;i++){
        scanf("%d",&In1);
        Key[In1]=true;
    }
    DFS(1,1);
    Dynamic(1,1,0);
    for(int i=1;i<=n;i++){ printf("%lld\n",Ans[i]);}
}
```
