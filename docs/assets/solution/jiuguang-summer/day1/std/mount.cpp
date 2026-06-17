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
