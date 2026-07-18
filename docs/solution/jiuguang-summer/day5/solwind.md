# 日月风随

## 题意简述

给定序列 $h_i$。可以先花费代价把若干位置削弱，再选择一个位置投入强度 $x$ 触发一次向两侧递减传播的仪式。要求最终所有位置都被解开，求最小总消耗。

## 部分分

若固定峰顶 $p$ 与投入强度，最终保留下来的韧度形状必须从 $p$ 向两侧每次最多下降 $1$，且每个位置不超过原来的 $h_i$。因此可以枚举峰顶后模拟两侧可保留的最大形状。

## 正解

答案等于总韧度减去两侧能够保留的最大贡献，再加上峰顶投入。分别从左到右、从右到左计算以每个位置作为右端或左端时，需要削弱掉的最小代价。这个值由一段段被斜率为 $1$ 的上界截断的区间组成，可以用单调栈维护区间贡献。合并时枚举峰顶 $i$，取 `Need[0][i]+Need[1][i]+Line[i]` 的最小值。

## 复杂度

两次单调栈扫描和一次合并，时间复杂度为 $\mathcal{O}(n)$，空间复杂度为 $\mathcal{O}(n)$。所有和与答案均需使用 `long long`。

## 参考代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN 300010
int T,n;
long long Need[2][MAXN],Line[MAXN],Ans=0x7fffffffffffffff,PreSum=0,SuffSum=0;
class Container{
public:
    int Head=1,Tail=0,Pos[MAXN];;
    long long Sum=0;
    void Init(){Head=1,Tail=0;}
    void Push_Back(int a){Pos[++Tail]=a;}
    void Pop_Back(){Tail--;}
    int Back(){return Pos[Tail];}
    bool Empty(){return Head>=Tail;}
}Q;
long long Calc(long long Height,long long Length){//计算元素贡献
    Length=min(Length,Height);
    return 1ll*(Height+Height-Length+1)*Length/2;
}
void Ehundategh_Clear(){//清空
    PreSum=SuffSum=0;
    Q.Head=1;Q.Tail=0;
    Q.Sum=0;
    Q.Push_Back(0);
    Ans=0x7fffffffffffffff;
}
int main(){
    freopen("solwind.in","r",stdin);
    freopen("solwind.out","w",stdout);
    scanf("%d",&T);
    while(T-->0){
        scanf("%d",&n);
        Ehundategh_Clear();
        for(int i=1;i<=n;i++) scanf("%lld",&Line[i]);
        for(int i=1;i<=n;i++){
            PreSum+=Line[i];
            while(i-Q.Back()>Line[i]-Line[Q.Back()]&&!Q.Empty()){
                Q.Sum-=Calc(Line[Q.Back()],(long long)(Q.Back()-Q.Pos[Q.Tail-1]));
                Q.Pop_Back();
            }
            Q.Push_Back(i);
            Q.Sum+=Calc(Line[Q.Back()],(long long)(Q.Back()-Q.Pos[Q.Tail-1]));
            Need[0][i]=PreSum-Q.Sum;
        }
        Q.Head=1;Q.Tail=0;
        Q.Sum=0;
        Line[n+1]=0;
        Q.Push_Back(n+1);
        for(int i=n;i>=1;i--){
            SuffSum+=Line[i];
            while(Q.Back()-i>Line[i]-Line[Q.Back()]&&!Q.Empty()){
                Q.Sum-=Calc(Line[Q.Back()],(long long)(Q.Pos[Q.Tail-1]-Q.Back()));
                Q.Pop_Back();
            }
            Q.Push_Back(i);
            Q.Sum+=Calc(Line[Q.Back()],(long long)(Q.Pos[Q.Tail-1]-Q.Back()));
            Need[1][i]=SuffSum-Q.Sum;
        }
        for(int i=1;i<=n;i++){
            if(Need[0][i]+Need[1][i]+Line[i]<Ans) Ans=Need[0][i]+Need[1][i]+Line[i];
        }
        printf("%lld\n",Ans);
    }
    return 0;
}
```
