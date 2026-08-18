#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define MAXN 5010
using namespace std;

const long long INF=(1ll<<62);
struct node{
    int Mark;
    long long Val;
};

vector <node> Dp[MAXN];
vector <long long> Suff[MAXN];
long long Val[MAXN],k;
int c,T,n,Leaf,Line[MAXN],Pos[MAXN],Right[MAXN];

long long Add(long long x,long long y){
    if(x>=INF||y>=INF||x>INF-y) return INF;
    return x+y;
}

long long Query(int Now,int x){
    int Left=0,RightPos=Dp[Now].size();
    while(Left<RightPos){
        int Mid=(Left+RightPos)>>1;
        if(Dp[Now][Mid].Mark<=x) Left=Mid+1;
        else RightPos=Mid;
    }
    return Left==(int)Dp[Now].size()?INF:Suff[Now][Left];
}

void Build(int Now){
    if(Now>=Leaf){
        Right[Now]=Now-Leaf+1;
        Dp[Now].push_back({Line[Now],0});
        Suff[Now].push_back(0);
        return;
    }
    int ls=Now<<1,rs=Now<<1|1;
    Build(ls);Build(rs);
    Right[Now]=Right[rs];
    int i=0,j=0,p=0,q=0;
    Dp[Now].reserve(Dp[ls].size()+Dp[rs].size());
    while(i<(int)Dp[ls].size()||j<(int)Dp[rs].size()){
        bool Tag=j==(int)Dp[rs].size()||
            (i<(int)Dp[ls].size()&&Dp[ls][i].Mark<Dp[rs][j].Mark);
        int Mark=Tag?Dp[ls][i].Mark:Dp[rs][j].Mark;
        while(p<(int)Dp[ls].size()&&Dp[ls][p].Mark<=Mark) p++;
        while(q<(int)Dp[rs].size()&&Dp[rs][q].Mark<=Mark) q++;
        if(Tag){
            long long Ret=q==(int)Dp[rs].size()?INF:Suff[rs][q];
            Dp[Now].push_back({Mark,Add(Dp[ls][i].Val,min(Val[Now],Ret))});
            i++;
        }
        else{
            long long Ret=p==(int)Dp[ls].size()?INF:Suff[ls][p];
            Dp[Now].push_back({Mark,Add(Dp[rs][j].Val,Ret)});
            j++;
        }
    }
    Suff[Now].resize(Dp[Now].size());
    for(int i=(int)Dp[Now].size()-1;i>=0;i--){
        Suff[Now][i]=Dp[Now][i].Val;
        if(i+1<(int)Dp[Now].size()) Suff[Now][i]=min(Suff[Now][i],Suff[Now][i+1]);
    }
    return;
}

long long Print(int Now,int x,long long Limit){
    if(Now>=Leaf){printf("%d ",Line[Now]);return 0;}
    int ls=Now<<1,rs=Now<<1|1,Temp=0;
    if(Pos[x]<=Right[ls]){
        long long Need=min(Val[Now],Query(rs,x));
        long long Ret=Print(ls,x,Limit-Need);
        Limit-=Ret;
        for(int i=(int)Dp[rs].size()-1;i>=0;i--){
            long long Extra=Dp[rs][i].Mark<x?Val[Now]:0;
            if(Add(Dp[rs][i].Val,Extra)<=Limit){
                Temp=Dp[rs][i].Mark;
                break;
            }
        }
        long long Extra=Temp<x?Val[Now]:0;
        return Ret+Extra+Print(rs,Temp,Limit-Extra);
    }
    long long Need=Query(ls,x);
    long long Ret=Print(rs,x,Limit-Need);
    Limit-=Ret;
    for(int i=(int)Dp[ls].size()-1;i>=0;i--){
        if(Dp[ls][i].Mark>x&&Dp[ls][i].Val<=Limit){
            Temp=Dp[ls][i].Mark;
            break;
        }
    }
    return Ret+Print(ls,Temp,Limit);
}

void Solve(){
    scanf("%d%lld",&n,&k);Leaf=1<<n;
    for(int i=1;i<(Leaf<<1);i++) Dp[i].clear(),Suff[i].clear();
    for(int i=1;i<Leaf;i++) scanf("%lld",&Val[i]);
    for(int i=Leaf;i<(Leaf<<1);i++){
        scanf("%d",&Line[i]);
        Pos[Line[i]]=i-Leaf+1;
    }
    Build(1);
    int Temp=0;
    for(int i=(int)Dp[1].size()-1;i>=0;i--){
        if(Dp[1][i].Val<=k){
            Temp=Dp[1][i].Mark;
            break;
        }
    }
    Print(1,Temp,k);
    printf("\n");
    return;
}

int main(){
    scanf("%d%d",&c,&T);
    while(T-->0) Solve();
    return 0;
}
