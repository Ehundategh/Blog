#include <stack>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 2000010
using namespace std;
int Head[MAXN],Total=0,SCC[MAXN],cnt=0,Dfn[MAXN],Low[MAXN],cnt2=0;
int Ans[MAXN],In1,In2,In3,In4,n,m;
stack <int> S;
struct edge{
    int Ed,Next;
}Edge[MAXN<<1];
void Edge_Add(int St,int Ed){
    Edge[++Total]={Ed,Head[St]};
    Head[St]=Total;
}
void Tarjan(int Now){
    Low[Now]=Dfn[Now]=++cnt2;
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
        cnt++;
        while(S.top()!=Now){
            SCC[S.top()]=cnt;
            S.pop();
        }
        SCC[Now]=cnt;S.pop();
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d%d",&In1,&In2,&In3,&In4);
        if(In2>In4){swap(In2,In4);swap(In1,In3);}
        if(In2==In4&&In2==0){
            Edge_Add(In1,In3+n);Edge_Add(In3,In1+n);
        }
        else if(In2==0&&In4==1){
            Edge_Add(In1,In3);Edge_Add(In3+n,In1+n);
        }
        else{
            Edge_Add(In1+n,In3);Edge_Add(In3+n,In1);
        }
    }
    for(int i=1;i<=2*n;i++) if(!Dfn[i]) Tarjan(i);
    for(int i=1;i<=n;i++){
        if(SCC[i]==SCC[i+n]){puts("IMPOSSIBLE");return 0;}
    }
    puts("POSSIBLE");
    for(int i=1;i<=n;i++) Ans[i]=SCC[i]<SCC[i+n];
    for(int i=1;i<=n;i++) printf("%d ",Ans[i]);
    return 0;
}
