/*
Author:Ehundategh
Date:2026/8/13
Name:echo.cpp
You steal,I kill.
*/
#include <stack>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#define MAXN 200010
#define MAXS 20
using namespace std;

const long long INF=-(1ll<<60);
int c,T,n,k,cnt,Line[MAXN],Weight[MAXN],Mapping[MAXN];
long long Old[MAXN][MAXS];
vector <int> Son[MAXN];

class SegmentTree{
public:
    int n;
    vector <long long> Val;
    void Init(int m){n=1;while(n<m) n<<=1;Val.assign(n<<1,INF);}
    long long Get(int Pos){return Val[n+Pos-1];}
    void Modify(int Pos,long long Value){
        int Now=n+Pos-1;
        Val[Now]=Value;
        for(Now>>=1;Now;Now>>=1) Val[Now]=max(Val[Now<<1],Val[Now<<1|1]);
        return ;
    }
    long long Query(int l,int r){
        if(l>r) return INF;
        long long Ret=INF;
        for(l=n+l-1,r=n+r-1;l<=r;l>>=1,r>>=1){
            if(l&1) Ret=max(Ret,Val[l++]);
            if(!(r&1)) Ret=max(Ret,Val[r--]);
        }
        return Ret;
    }
}Tree[MAXS];

void Discrete(){
    for(int i=1;i<=n;i++) Mapping[i]=Line[i];
    sort(Mapping+1,Mapping+n+1);
    cnt=unique(Mapping+1,Mapping+n+1)-Mapping-1;
    return ;
}

int Find(int x){return lower_bound(Mapping+1,Mapping+cnt+1,x)-Mapping;}

void Solve(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) Son[i].clear();
    for(int i=2,From;i<=n;i++) scanf("%d",&From),Son[From].push_back(i);
    for(int i=1;i<=n;i++) scanf("%d",&Line[i]);
    for(int i=1;i<=n;i++) scanf("%d",&Weight[i]);
    Discrete();
    int State=1+2*(k+1);
    for(int i=0;i<State;i++) Tree[i].Init(cnt);
    stack <pair <int,bool> > S;
    S.push({1,0});
    long long Ans=0;
    while(!S.empty()){
        int Now=S.top().first;
        bool Exit=S.top().second;
        S.pop();
        int Pos=Find(Line[Now]);
        if(Exit){
            for(int i=0;i<State;i++) Tree[i].Modify(Pos,Old[Now][i]);
            continue;
        }
        long long Dp[MAXS];
        for(int i=0;i<State;i++) Dp[i]=INF;
        Dp[0]=Weight[Now];
        for(int j=0;j<=k;j++){
            int Up=1+(j<<1),Down=Up+1;
            long long Temp=max(Tree[0].Query(1,Pos-1),Tree[Up].Query(1,Pos-1));
            if(j) Temp=max(Temp,Tree[1+((j-1)<<1)+1].Query(1,Pos-1));
            if(Temp>INF/2) Dp[Up]=Temp+Weight[Now];
            Temp=max(Tree[0].Query(Pos+1,cnt),Tree[Down].Query(Pos+1,cnt));
            if(j) Temp=max(Temp,Tree[1+((j-1)<<1)].Query(Pos+1,cnt));
            if(Temp>INF/2) Dp[Down]=Temp+Weight[Now];
        }
        for(int i=0;i<State;i++){
            Old[Now][i]=Tree[i].Get(Pos);
            Tree[i].Modify(Pos,max(Old[Now][i],Dp[i]));
            Ans=max(Ans,Dp[i]);
        }
        S.push({Now,1});
        for(int i=(int)Son[Now].size()-1;i>=0;i--) S.push({Son[Now][i],0});
    }
    printf("%lld\n",Ans);
    return ;
}

int main(){
    scanf("%d%d",&c,&T);
    while(T-->0) Solve();
    return 0;
}
