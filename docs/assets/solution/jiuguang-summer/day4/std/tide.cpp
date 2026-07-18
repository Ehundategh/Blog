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
