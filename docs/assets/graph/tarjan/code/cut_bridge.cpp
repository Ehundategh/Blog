#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 200010
#define MAXM 500010
using namespace std;
int n,m,Head[MAXN],Total=1,Dfn[MAXN],Low[MAXN],cnt=0;
int In1,In2;
bool Cut[MAXN],Bridge[MAXM<<1];
struct edge{
    int St,Ed,Next;
}Edge[MAXM<<1];
void Edge_Add(int St,int Ed){
    Edge[++Total]={St,Ed,Head[St]};
    Head[St]=Total;
}
void Tarjan(int Now,int From){
    Dfn[Now]=Low[Now]=++cnt;
    int Son=0;
    for(int i=Head[Now];i;i=Edge[i].Next){
        if(i==(From^1)) continue;
        int To=Edge[i].Ed;
        if(!Dfn[To]){
            Son++;
            Tarjan(To,i);
            Low[Now]=min(Low[Now],Low[To]);
            if(Low[To]>Dfn[Now]) Bridge[i]=Bridge[i^1]=true;
            if(From&&Low[To]>=Dfn[Now]) Cut[Now]=true;
        }
        else Low[Now]=min(Low[Now],Dfn[To]);
    }
    if(!From&&Son>=2) Cut[Now]=true;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&In1,&In2);
        Edge_Add(In1,In2);Edge_Add(In2,In1);
    }
    for(int i=1;i<=n;i++) if(!Dfn[i]) Tarjan(i,0);
    for(int i=1;i<=n;i++) printf("%d ",Cut[i]);
    puts("");
    for(int i=1;i<=m;i++) printf("%d ",Bridge[i<<1]);
    return 0;
}
