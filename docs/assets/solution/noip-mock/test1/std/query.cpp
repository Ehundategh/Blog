/*
Author:Ehundategh
Date:2026/7/24
Name:query.cpp
You steal,I kill.
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 500010
#define MAXQ 1000010
using namespace std;
int n,q,Line[MAXN],Pre[MAXN],Position[MAXN],Left[MAXN],Right[MAXN];
long long IndexSum[MAXN],Cnt[MAXN],Sum[MAXN],Part[MAXQ],Ans[MAXN];
struct ask{
    int Left,Right,Value,Id;
}Ask[MAXQ];
bool cmpa(int x,int y){return Pre[x]<Pre[y];}
bool cmpb(ask x,ask y){return x.Value<y.Value;}
int lowbit(int x){return x&-x;}
void Modify(int x,long long Val,long long C[]){
    for(;x<=n;x+=lowbit(x)) C[x]+=Val;
}
long long Query(int x,long long C[]){
    long long Ret=0;
    for(;x;x-=lowbit(x)) Ret+=C[x];
    return Ret;
}
void Solve(){
    static int LastN=0;
    scanf("%d%d",&n,&q);
    int ClearN=max(n,LastN);
    memset(Cnt,0,sizeof(long long)*(ClearN+1));
    memset(Sum,0,sizeof(long long)*(ClearN+1));
    Pre[0]=IndexSum[0]=0;
    LastN=n;
    for(int i=1;i<=n;i++){
        scanf("%d",&Line[i]);
        Pre[i]=Pre[i-1]+(Line[i]==(i&1)?1:-1);
        IndexSum[i]=IndexSum[i-1]+Pre[i];
        Position[i]=i;
    }
    int Total=0;
    for(int i=1;i<=q;i++){
        scanf("%d%d",&Left[i],&Right[i]);
        Ask[++Total]={Left[i],Right[i]-1,Pre[Left[i]-1],i*2-1};
        Ask[++Total]={Left[i],Right[i]-1,Pre[Right[i]],i*2};
    }
    sort(Position+1,Position+n+1,cmpa);
    sort(Ask+1,Ask+Total+1,cmpb);
    int Now=1;
    for(int i=1;i<=Total;i++){
        while(Now<=n&&Pre[Position[Now]]<=Ask[i].Value){
            Modify(Position[Now],1,Cnt);
            Modify(Position[Now],Pre[Position[Now]],Sum);
            Now++;
        }
        int l=Ask[i].Left,r=Ask[i].Right;
        long long CntLow=Query(r,Cnt)-Query(l-1,Cnt);
        long long SumLow=Query(r,Sum)-Query(l-1,Sum);
        long long Count=r-l+1,SumAll=IndexSum[r]-IndexSum[l-1];
        Part[Ask[i].Id]=1ll*Ask[i].Value*CntLow-SumLow+
                        SumAll-SumLow-1ll*Ask[i].Value*(Count-CntLow);
    }
    for(int i=1;i<=q;i++){
        Ans[i]=(Part[i*2-1]+Part[i*2]-
                1ll*(Right[i]-Left[i])*abs(Pre[Right[i]]-Pre[Left[i]-1]))/2;
        printf("%lld\n",Ans[i]);
    }
}
int main(){
    int c,T;
    scanf("%d%d",&c,&T);
    while(T-->0) Solve();
    return 0;
}
