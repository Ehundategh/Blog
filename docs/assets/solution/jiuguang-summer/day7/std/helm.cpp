#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 600100
#define MAXM 300100
#define MAXK 250100
using namespace std;
int Head[MAXN],Total=0,S,n,m,Deg[MAXN],cnt=0,k;
int St[MAXM],Ed[MAXM],cne=0,Tag[MAXM],Back[MAXN];
long long Dist[MAXN<<1],Pre[MAXK],Ans[MAXN],UpValue[MAXK],DownValue[MAXK],EdgeV[MAXM];
bool Visited[MAXN];
vector <int> Mark[MAXN];
struct edge{
    int St,Ed;
    int Next;
    long long Value;
}Edge[MAXM<<2];
void Edge_Add(int a,int b,long long Value){
    Edge[++Total]={a,b,Head[a],Value};
    Head[a]=Total;
}
priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> Q;
void Dijkstra(){
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

int main(){
    freopen("helm.in","r",stdin);
    freopen("helm.out","w",stdout);
    memset(Ans,0x3f,sizeof(Ans));
    Pre[1]=0;
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=k-1;i++){
        scanf("%lld",&UpValue[i]);
    }
    for(int i=2;i<=k;i++){
        scanf("%lld",&DownValue[i]);
        Pre[i]=DownValue[i]+Pre[i-1];
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&Deg[i]);
        cnt++;
        Mark[i].push_back(cnt);
        Back[cnt]=i;
        for(int j=1;j<=Deg[i];j++){
            cnt++;
            Mark[i].push_back(cnt);
            Back[cnt]=i;
            if(j!=1){
                Edge_Add(Mark[i][j],Mark[i][j-1],DownValue[j]);
                Edge_Add(Mark[i][j-1],Mark[i][j],UpValue[j-1]);
            }
        }
        for(int j=1;j<=Deg[i];j++){
            cne++;
            scanf("%d%d",&Ed[cne],&EdgeV[cne]);
            Tag[cne]=j;St[cne]=i;
        }
    }
    S=Mark[1][Deg[1]?1:0];
    for(int i=1;i<=m;i++){
        if(!Deg[Ed[i]]){
            Edge_Add(Mark[St[i]][Tag[i]],Mark[Ed[i]][0],EdgeV[i]);
        }
        else if(Deg[Ed[i]]<Tag[i]){
            cnt++;Mark[Ed[i]].push_back(cnt);Back[cnt]=Ed[i];
            Edge_Add(Mark[St[i]][Tag[i]],cnt,EdgeV[i]);
            Edge_Add(cnt,Mark[Ed[i]][Deg[Ed[i]]],
                     Pre[Tag[i]]-Pre[Deg[Ed[i]]]);
        }
        else{
            Edge_Add(Mark[St[i]][Tag[i]],Mark[Ed[i]][Tag[i]],EdgeV[i]);
        }
    }
    Dijkstra();
    Ans[1]=0;
    for(int i=1;i<=cnt;i++){
        Ans[Back[i]]=min(Ans[Back[i]],Dist[i]);
    }
    for(int i=1;i<=n;i++){
        if(Ans[i]==0x3f3f3f3f3f3f3f3f){
            printf("-1 ");
        }
        else printf("%lld ",Ans[i]);
    }
    return 0;
}
