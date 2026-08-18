#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 1000010
using namespace std;

const int Mod=998244353;
int c,T,n,k,m,Line[MAXN],Delta[MAXN],Fac[MAXN],Inv[MAXN];

int Mul(int x,int y){return 1ll*x*y%Mod;}

int Power(int x,int y){
    int Ret=1;
    while(y){
        if(y&1) Ret=Mul(Ret,x);
        x=Mul(x,x);y>>=1;
    }
    return Ret;
}

int C(int n,long long m){
    if(m<0||m>n) return 0;
    return Mul(Fac[n],Mul(Inv[m],Inv[n-m]));
}

void Init(){
    Fac[0]=1;
    for(int i=1;i<MAXN;i++) Fac[i]=Mul(Fac[i-1],i);
    Inv[MAXN-1]=Power(Fac[MAXN-1],Mod-2);
    for(int i=MAXN-1;i>=1;i--) Inv[i-1]=Mul(Inv[i],i);
    return;
}

void Solve(){
    scanf("%d%d%d",&n,&k,&m);
    for(int i=1;i<=n-k+1;i++) scanf("%d",&Line[i]);
    for(int i=1;i<=n-k;i++){
        Delta[i]=Line[i+1]-Line[i];
        if(Delta[i]<-1||Delta[i]>1){printf("0\n");return;}
    }
    int Long=n%k,Length=n/k,FreeLong=0,FreeShort=0;
    long long First=0,Total=0;
    for(int r=1;r<=k;r++){
        int Now=0;bool Can[2]={1,1};long long Count[2]={0,0};
        for(int i=r;i<=n;i+=k){
            if(i!=r) Now+=Delta[i-k];
            for(int x=0;x<=1;x++){
                if(x+Now<0||x+Now>1) Can[x]=0;
                else Count[x]+=x+Now;
            }
        }
        if(!Can[0]&&!Can[1]){printf("0\n");return;}
        if(Can[0]&&Can[1]){
            if(r<=Long) FreeLong++;
            else FreeShort++;
        }
        else{
            int x=Can[1];
            First+=x;Total+=Count[x];
        }
    }
    long long NeedFirst=Line[1]-First,NeedTotal=m-Total;
    long long TakeLong=NeedTotal-NeedFirst*Length;
    long long TakeShort=NeedFirst-TakeLong;
    printf("%d\n",Mul(C(FreeLong,TakeLong),C(FreeShort,TakeShort)));
    return;
}

int main(){
    Init();
    scanf("%d%d",&c,&T);
    while(T-->0) Solve();
    return 0;
}
