#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 12
#define MAXL 2000010
const int Mod1=1e9+7;
const int Mod2=1e9+9;
const int Inv1=489437524;
const int Inv2=793611037;
const int p=20070903;
using namespace std;
int n,Length[MAXN],StLen,cns,q,Mark[MAXN],a;
char S[MAXL],In[MAXL];
class BKDRHash{
private:
    int Mod,Inv,Hash[MAXL<<1],P[MAXL<<1];
    inline int Calc(int a,int b){return (a+=b)<Mod?a:a-Mod;}
    inline int Mul(int a,int b){return 1ll*a*b%Mod;}
    inline int Del(int a,int b){return (a-=b)<0?a+Mod:a;}
public:
    void Init(int a,int b){
        Mod=a;Inv=b;
        P[0]=1;
        for(int i=1;i<=cns;i++){
            Hash[i]=Mul(Hash[i-1],p);
            P[i]=Mul(P[i-1],p);
            Hash[i]+=S[i];
        }
    }
    int Query(int Left,int Right){
        return Del(Hash[Right],Mul(Hash[Left-1],P[Right-Left+1]));
    }
}Hash1,Hash2;
bool Judge(int L1,int R1,int L2,int R2){
    int V11,V12,V21,V22;
    V11=Hash1.Query(L1,R1);
    V12=Hash2.Query(L1,R1);
    V21=Hash1.Query(L2,R2);
    V22=Hash2.Query(L2,R2);
    return (V11==V21&&V22==V12);
}
int Get_LCP(int x,int Pre){
    int L=0,R=min(StLen-Pre,Length[x]-Pre);
    while(L<R){
        int Mid=(L+R)>>1;
        if(Mid==L) Mid++;
        if(Judge(1+Pre,1+Mid+Pre-1,Mark[x]+Pre,Mark[x]+Mid+Pre-1)) L=Mid;
        else R=Mid-1;
    }
    return L;
}
int main(){
    scanf("%s",S+1);
    cns=strlen(S+1); StLen=cns;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%s",In+1);
        Length[i]=strlen(In+1);
        Mark[i]=cns+1;
        for(int j=1;j<=Length[i];j++){
            S[++cns]=In[j];
        }
    }
    Hash1.Init(Mod1,Inv1);
    Hash2.Init(Mod2,Inv2);
    while(q-->0){
        scanf("%d",&a);
        int Ans=1,MaxLen=0;
        for(int i=1;i<=n;i++){
            int NowLen=Get_LCP(i,a);
            if(NowLen>MaxLen){
                MaxLen=NowLen;
                Ans=i;
            }
        }
        printf("%d\n",Ans);
    }
    return 0;
}
