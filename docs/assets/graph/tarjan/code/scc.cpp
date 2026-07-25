#include <stack>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 200010
#define MAXM 500010
using namespace std;
int n,m,Head[MAXN],Total=0,Dfn[MAXN],Low[MAXN],SCC[MAXN];
int cnt=0,cnd=0,In1,In2;
stack <int> S;
struct edge{
    int Ed,Next;
}Edge[MAXM];
void Edge_Add(int St,int Ed){
    Edge[++Total]={Ed,Head[St]};
    Head[St]=Total;
}
void Tarjan(int Now){
    Dfn[Now]=Low[Now]=++cnt;
    S.push(Now);
    for(int i=Head[Now];i;i=Edge[i].Next){
        int To=Edge[i].Ed;
        if(!Dfn[To]){
            Tarjan(To);
            Low[Now]=min(Low[Now],Low[To]);
        }
        else if(!SCC[To]) Low[Now]=min(Low[Now],Dfn[To]);
    }
    if(Low[Now]==Dfn[Now]){
        cnd++;
        while(S.top()!=Now){
            SCC[S.top()]=cnd;
            S.pop();
        }
        SCC[Now]=cnd;S.pop();
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&In1,&In2);
        Edge_Add(In1,In2);
    }
    for(int i=1;i<=n;i++) if(!Dfn[i]) Tarjan(i);
    printf("%d\n",cnd);
    for(int i=1;i<=n;i++) printf("%d ",SCC[i]);
    return 0;
}
