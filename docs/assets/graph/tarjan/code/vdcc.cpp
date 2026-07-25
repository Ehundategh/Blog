#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 200010
#define MAXM 500010
using namespace std;
int n,m,Head[MAXN],Total=1,Dfn[MAXN],Low[MAXN],cnt=0;
int Stack[MAXM<<1],Top=0,Tag[MAXN],cnd=0,In1,In2;
vector <int> DCC[MAXM];
struct edge{
    int St,Ed,Next;
}Edge[MAXM<<1];
void Edge_Add(int St,int Ed){
    Edge[++Total]={St,Ed,Head[St]};
    Head[St]=Total;
}
void Add_Point(int Now,int x){
    if(Tag[x]==Now) return;
    Tag[x]=Now;DCC[Now].push_back(x);
}
void Tarjan(int Now,int From){
    Dfn[Now]=Low[Now]=++cnt;
    for(int i=Head[Now];i;i=Edge[i].Next){
        if(i==(From^1)) continue;
        int To=Edge[i].Ed;
        if(!Dfn[To]){
            Stack[++Top]=i;
            Tarjan(To,i);
            Low[Now]=min(Low[Now],Low[To]);
            if(Low[To]>=Dfn[Now]){
                cnd++;
                while(Stack[Top]!=i){
                    Add_Point(cnd,Edge[Stack[Top]].St);
                    Add_Point(cnd,Edge[Stack[Top]].Ed);
                    Top--;
                }
                Add_Point(cnd,Edge[i].St);
                Add_Point(cnd,Edge[i].Ed);
                Top--;
            }
        }
        else if(Dfn[To]<Dfn[Now]){
            Stack[++Top]=i;
            Low[Now]=min(Low[Now],Dfn[To]);
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&In1,&In2);
        Edge_Add(In1,In2);Edge_Add(In2,In1);
    }
    for(int i=1;i<=n;i++){
        if(Dfn[i]) continue;
        if(!Head[i]){cnd++;DCC[cnd].push_back(i);Tag[i]=cnd;}
        else Tarjan(i,0);
    }
    printf("%d\n",cnd);
    for(int i=1;i<=cnd;i++){
        sort(DCC[i].begin(),DCC[i].end());
        printf("%d ",(int)DCC[i].size());
        for(int x:DCC[i]) printf("%d ",x);
        puts("");
    }
    return 0;
}
