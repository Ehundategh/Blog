#include <stack>
#include <queue>
#include <cstdio>
#include <climits>
#include <algorithm>
#define MAXN 200010
#define MAXM 500010
using namespace std;
int n,m,Head[MAXN],Head2[MAXN],Total=0,Total2=0;
int Dfn[MAXN],Low[MAXN],SCC[MAXN],Deg[MAXN],cnt=0,cnd=0;
int In1,In2;
long long Value[MAXN],Sum[MAXN],DP[MAXN],Ans=LLONG_MIN;
stack <int> S;
queue <int> Q;
struct edge{
    int St,Ed,Next;
}Edge[MAXM],Edge2[MAXM];
void Edge_Add(int St,int Ed){
    Edge[++Total]={St,Ed,Head[St]};
    Head[St]=Total;
}
void Edge_Add2(int St,int Ed){
    Edge2[++Total2]={St,Ed,Head2[St]};
    Head2[St]=Total2;
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
    for(int i=1;i<=n;i++) scanf("%lld",&Value[i]);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&In1,&In2);
        Edge_Add(In1,In2);
    }
    for(int i=1;i<=n;i++) if(!Dfn[i]) Tarjan(i);
    for(int i=1;i<=n;i++) Sum[SCC[i]]+=Value[i];
    for(int i=1;i<=Total;i++){
        int St=SCC[Edge[i].St],Ed=SCC[Edge[i].Ed];
        if(St==Ed) continue;
        Edge_Add2(St,Ed);Deg[Ed]++;
    }
    for(int i=1;i<=cnd;i++){
        DP[i]=Sum[i];
        if(!Deg[i]) Q.push(i);
    }
    while(!Q.empty()){
        int Now=Q.front();Q.pop();
        Ans=max(Ans,DP[Now]);
        for(int i=Head2[Now];i;i=Edge2[i].Next){
            int To=Edge2[i].Ed;
            DP[To]=max(DP[To],DP[Now]+Sum[To]);
            if(!--Deg[To]) Q.push(To);
        }
    }
    printf("%lld\n",Ans);
    return 0;
}
