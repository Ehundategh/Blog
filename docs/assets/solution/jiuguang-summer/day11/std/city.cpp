#include <cstdio>
#include <cstring>
#define MAXN 200010
const int Mod=998244353;
using namespace std;
int Calc(int a,int b){return (a+=b)<Mod?a:a-Mod;}
int Mul(int a,int b){return 1ll*a*b%Mod;}
int Del(int a,int b){return (a-=b)>0?a:a+Mod;}
int Total=0,Head[MAXN],Count[MAXN],Root=1,Size[MAXN],n;
int Sum=0;
struct E{
    int St,Ed;
    int Next;
    int Value;
}Edge[MAXN<<1];
void Edge_Add(int St,int Ed,int Value){
    Total++;
    Edge[Total].St=St;
    Edge[Total].Ed=Ed;
    Edge[Total].Value=Value;
    Edge[Total].Next=Head[St];
    Head[St]=Total;
}
void DFS_F(int Now,int From,int Value){
    Size[Now]=1;
    for(int i=Head[Now];i;i=Edge[i].Next){
        int To=Edge[i].Ed;
        if(To==From) continue;
        DFS_F(To,Now,Calc(Value,Edge[i].Value));
        Size[Now]+=Size[To];
        Count[Root]=Calc(Count[Root],Calc(Value,Edge[i].Value));
    }
}
void DFS_Pass(int Now,int From){
    for(int i=Head[Now];i;i=Edge[i].Next){
        int To=Edge[i].Ed;
        if(To==From) continue;
        Count[To]=Calc(Count[Now],Mul((n-Size[To]-Size[To]),Edge[i].Value));
        Count[To]=(Count[To]%Mod+Mod)%Mod;
        DFS_Pass(To,Now);
    }
}
void Build(int Line,int Cost){
    printf("%d\n",Calc(Sum,Mul(2,Calc(Count[Line],Mul(Cost,n)))));
}
void Solve(){
    int Q;
    scanf("%d%d",&n,&Q);
    memset(Head,0,sizeof(int)*(n+2));
    memset(Count,0,sizeof(int)*(n+2));
    memset(Size,0,sizeof(int)*(n+2));
    Total=Sum=0;Root=1;
    int In1,In2,In3;
    for(int i=1;i<=n-1;i++){
        scanf("%d%d%d",&In1,&In2,&In3);
        Edge_Add(In1,In2,In3);
        Edge_Add(In2,In1,In3);
    }
    DFS_F(Root,Root,0);
    DFS_Pass(Root,Root);
    for(int i=1;i<=n;i++) Sum=Calc(Sum,Count[i]);
    while(Q--){
        scanf("%d%d",&In1,&In2);
        Build(In1,In2);
    }
}
int main(){
    int c,T;
    scanf("%d%d",&c,&T);
    while(T-->0) Solve();
    return 0;
}
