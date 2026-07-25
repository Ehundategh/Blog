/*
- Author:Ehundategh
- Update:2023/9/25
- Tile:blo.cpp
- You steal,I kill
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 100010
#define MAXM 500010
using namespace std;
int Head[MAXN],Total=0;
int DFN[MAXN],Low[MAXN],cnt=0,Root,Size[MAXN],n,m;
long long Ans[MAXN];
bool Cut[MAXN];
struct edge{
    int St,Ed;
    int Next;
}Edge[MAXM<<1];
void Edge_Add(int St,int Ed){
    Edge[++Total]=(edge){St,Ed,Head[St]};
    Head[St]=Total;
}
void Tarjan(int Now){
    DFN[Now]=Low[Now]=++cnt;
    Size[Now]=1;
    int Son=0,Sum=0;
    for(int i=Head[Now];i;i=Edge[i].Next){
        int To=Edge[i].Ed;
        if(!DFN[To]){
            Son++;
            Tarjan(To);
            Size[Now]+=Size[To];
            Low[Now]=min(Low[Now],Low[To]);
            if(Low[To]>=DFN[Now]){
                Ans[Now]+=1ll*Size[To]*(n-Size[To]);
                Sum+=Size[To];
                if(Now!=Root||Son>=2) Cut[Now]=1;
            }
        }
        else Low[Now]=min(Low[Now],DFN[To]);
    }
    if(Cut[Now]){
        Ans[Now]+=1ll*(n-Sum-1)*(Sum+1)+(n-1);
    }
    else{
        Ans[Now]=1ll*(n-1)*2;
    }
}
int main(){
    int In1,In2;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&In1,&In2);
        Edge_Add(In1,In2);
        Edge_Add(In2,In1);
    }
    Root=1;
    Tarjan(1);
    for(int i=1;i<=n;i++){
        printf("%lld\n",Ans[i]);
    }
    return 0;
}
