# 单调队列优化 DP

单调队列优化常用于形如：

$$
f_i=\max_{L_i\le j\le R_i}\{g_j+w(i,j)\}
$$

的转移。若窗口 $[L_i,R_i]$ 随着 $i$ 单调移动，并且 $w(i,j)$ 中关于 $j$ 的部分可以单独提出，就可以尝试用单调队列维护候选转移的最大值。

## 多重背包

[P1776 宝物筛选](https://www.luogu.com.cn/problem/P1776) 是多重背包的模板题。

???+ note "题目描述"

    给定背包容量 $m$，有 $n$ 种物品。第 $i$ 种物品有 $k_i$ 个，每个价值为 $w_i$，体积为 $v_i$。求不超过背包容量时能够得到的最大价值。

??? tip "Hint"

    一个显然的思路是把多重背包拆成若干个 01 背包物品，但当 $n,m$ 较大时仍然会比较慢。

??? success "解法"

    记 $dp_{i,j}$ 表示考虑前 $i$ 种物品，容量为 $j$ 时的最大价值，那么有：

    $$
    dp_{i,j}
    =
    \max_{0\le t\le k_i}
    \{dp_{i-1,j-tv_i}+tw_i\}
    $$

    滚动数组后，我们只需要考虑第 $i$ 种物品如何从上一层转移到这一层。

    注意到 $j-tv_i$ 与 $j$ 在模 $v_i$ 意义下同余。因此我们枚举余数：

    $$
    r\in[0,v_i-1]
    $$

    并令：

    $$
    j=r+pv_i
    $$

    则转移可以写成：

    $$
    dp_{r+pv_i}
    =
    \max_{p-k_i\le q\le p}
    \{old_{r+qv_i}+(p-q)w_i\}
    $$

    将只和 $q$ 有关的部分提出：

    $$
    dp_{r+pv_i}
    =
    \max_{p-k_i\le q\le p}
    \{old_{r+qv_i}-qw_i\}
    +pw_i
    $$

    于是对于固定的 $r$，随着 $p$ 从小到大枚举，只需要维护：

    $$
    old_{r+qv_i}-qw_i
    $$

    的滑动窗口最大值。这个窗口长度为 $k_i+1$，可以用单调队列维护。

    ```cpp
    #include <cstdio>
    #include <cstring>
    #include <algorithm>
    #define MAXN 100010
    using namespace std;
    int n,m,v,w,k,dp[MAXN],old[MAXN],Q[MAXN];
    int main(){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            scanf("%d%d%d",&v,&w,&k);
            for(int j=0;j<=m;j++) old[j]=dp[j];
            for(int r=0;r<v;r++){
                int Head=1,Tail=0;
                for(int p=0;r+p*v<=m;p++){
                    int Now=r+p*v;
                    int Val=old[Now]-p*w;
                    while(Head<=Tail&&Q[Head]<p-k) Head++;
                    while(Head<=Tail&&old[r+Q[Tail]*v]-Q[Tail]*w<=Val) Tail--;
                    Q[++Tail]=p;
                    dp[Now]=old[r+Q[Head]*v]+(p-Q[Head])*w;
                }
            }
        }
        printf("%d",dp[m]);
        return 0;
    }
    ```

??? abstract "复杂度分析"

    对每一种物品，每个容量只会进出单调队列一次，所以总时间复杂度为 $\mathcal{O}(nm)$，空间复杂度为 $\mathcal{O}(m)$。

## 股票交易

[P2569 [SCOI2010] 股票交易](https://www.luogu.com.cn/problem/P2569) 是单调队列优化 DP 的常见例题。

???+ note "题目描述"

    已知未来 $T$ 天内每天的股票信息。第 $i$ 天买入单价为 $ap_i$，卖出单价为 $bp_i$，最多买入 $as_i$ 支，最多卖出 $bs_i$ 支。两次交易之间必须间隔 $w$ 天，同时持有股票数不能超过 $MaxP$。初始有足够的钱，求最后最多能赚多少钱。

??? tip "Hint"

    状态中自然需要记录“第几天”和“当前持有多少股票”。买入和卖出都可以写成一段区间中的最大值。

??? success "解法"

    记 $dp_{i,j}$ 表示第 $i$ 天结束后，手中持有 $j$ 支股票时最多拥有的现金。首先可以不交易：

    $$
    dp_{i,j}=dp_{i-1,j}
    $$

    考虑买入。由于两次交易之间要间隔 $w$ 天，买入时应从第 $i-w-1$ 天转移。若第 $i$ 天买入后持有 $j$ 支，买入前持有 $k$ 支，则：

    $$
    j-as_i\le k\le j-1
    $$

    转移为：

    $$
    dp_{i,j}
    =
    \max_{j-as_i\le k\le j-1}
    \{dp_{i-w-1,k}-(j-k)ap_i\}
    $$

    提出与 $k$ 无关的部分：

    $$
    dp_{i,j}
    =
    \max_{j-as_i\le k\le j-1}
    \{dp_{i-w-1,k}+kap_i\}
    -jap_i
    $$

    因此从小到大枚举 $j$，用单调队列维护：

    $$
    dp_{i-w-1,k}+kap_i
    $$

    的最大值。

    卖出同理。若卖出后持有 $j$ 支，卖出前持有 $k$ 支，则：

    $$
    j+1\le k\le j+bs_i
    $$

    转移为：

    $$
    dp_{i,j}
    =
    \max_{j+1\le k\le j+bs_i}
    \{dp_{i-w-1,k}+(k-j)bp_i\}
    $$

    即：

    $$
    dp_{i,j}
    =
    \max_{j+1\le k\le j+bs_i}
    \{dp_{i-w-1,k}+kbp_i\}
    -jbp_i
    $$

    从大到小枚举 $j$，维护对应窗口即可。

    ```cpp
    #include <cstdio>
    #include <cstring>
    #include <algorithm>
    #define MAXN 4010
    using namespace std;

    struct Point{
        int Pos,Value;
    };

    Point Make(int a,int b){
        Point c; c.Pos=a; c.Value=b;
        return c;
    }

    struct Deque{
        Point Line[MAXN];
        int Head,Tail;
        void Init(){Head=2;Tail=1;}
        bool Empty(){return Tail<Head;}
        Point Back(){return Line[Tail];}
        Point Front(){return Line[Head];}
        void Push(Point a){Line[++Tail]=a;}
        void Pop_Back(){Tail--;}
        void Pop_Front(){Head++;}
    }Q1,Q2;

    int Dp[MAXN][MAXN],n,MaxP,m,In1,In2,In3,In4,Ans=0;

    int main(){
        scanf("%d%d%d",&n,&MaxP,&m);
        memset(Dp,0xcf,sizeof(Dp));
        Dp[0][0]=0;
        for(int i=1;i<=n;i++){
            scanf("%d%d%d%d",&In1,&In2,&In3,&In4);
            Q1.Init();Q2.Init();
            for(int j=0;j<=MaxP;j++){
                Dp[i][j]=max(Dp[i][j],Dp[i-1][j]);
                Q1.Push(Make(0,0));
                while(!Q1.Empty()&&Q1.Front().Pos<j-In3) Q1.Pop_Front();
                if(!Q1.Empty()) Dp[i][j]=max(Dp[i][j],Q1.Front().Value-j*In1);
                while(!Q1.Empty()&&Q1.Back().Value<Dp[max(0,i-m-1)][j]+j*In1) Q1.Pop_Back();
                Q1.Push(Make(j,Dp[max(0,i-m-1)][j]+j*In1));
            }
            for(int j=MaxP;j>=0;j--){
                while(!Q2.Empty()&&Q2.Front().Pos>j+In4) Q2.Pop_Front();
                if(!Q2.Empty()) Dp[i][j]=max(Dp[i][j],Q2.Front().Value-j*In2);
                while(!Q2.Empty()&&Q2.Back().Value<Dp[max(0,i-m-1)][j]+j*In2) Q2.Pop_Back();
                Q2.Push(Make(j,Dp[max(0,i-m-1)][j]+j*In2));
                if(i==n) Ans=max(Dp[i][j],Ans);
            }
        }
        printf("%d",Ans);
        return 0;
    }
    ```

??? abstract "复杂度分析"

    每一天买入和卖出各扫一遍持仓数量，每个状态进入和弹出队列常数次，时间复杂度为 $\mathcal{O}(TMaxP)$。

## 小结

单调队列优化 DP 的重点不是队列本身，而是把转移整理成滑动窗口最值。

通常可以按下面的顺序检查：

1. 写出朴素转移。
2. 找到窗口端点是否随枚举变量单调移动。
3. 把转移中只和候选位置有关的部分提出。
4. 用单调队列维护窗口最大值或最小值。

如果这四步都能完成，那么原本一层枚举转移的复杂度通常就能降到线性。
