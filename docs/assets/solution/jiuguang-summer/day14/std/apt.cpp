#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 1000010
using namespace std;
const int Inf=0x3f3f3f3f;
char S[MAXN];
int PreApt[MAXN],PreTpa[MAXN],MinVal[16],c,T,n;

bool Apt(int Pos){
    return Pos>=1&&Pos+2<=n&&S[Pos]=='A'&&S[Pos+1]=='P'&&S[Pos+2]=='T';
}
bool Tpa(int Pos){
    return Pos>=1&&Pos+2<=n&&S[Pos]=='T'&&S[Pos+1]=='P'&&S[Pos+2]=='A';
}
char Get(int Pos,int l,int r){
    if(Pos<l||Pos>r) return S[Pos];
    return S[l+r-Pos];
}
int Calc(int l,int r,int Total){
    int Ret=Total;
    for(int i=max(1,l-2);i<=min(n-2,r);i++){
        Ret-=Apt(i);
        Ret+=(Get(i,l,r)=='A'&&Get(i+1,l,r)=='P'&&Get(i+2,l,r)=='T');
    }
    return Ret;
}
int LeftMask(int l){
    int Ret=0;
    if(l>=3&&S[l-2]=='A'&&S[l-1]=='P') Ret|=1;
    if(l>=2&&S[l-1]=='A') Ret|=2;
    if(l+1<=n&&S[l+1]=='A'&&S[l]=='P') Ret|=4;
    if(S[l]=='A') Ret|=8;
    return Ret;
}
int RightMask(int r){
    int Ret=0;
    if(S[r]=='T') Ret|=1;
    if(r>=2&&S[r]=='P'&&S[r-1]=='T') Ret|=2;
    if(r+1<=n&&S[r+1]=='T') Ret|=4;
    if(r+2<=n&&S[r+1]=='P'&&S[r+2]=='T') Ret|=8;
    return Ret;
}
void Solve(){
    scanf("%s",S+1);n=strlen(S+1);
    for(int i=1;i<=n;i++){
        PreApt[i]=PreApt[i-1]+Apt(i);
        PreTpa[i]=PreTpa[i-1]+Tpa(i);
    }
    int Total=PreApt[n],Ans=Total;
    for(int l=1;l<=n;l++) for(int r=l;r<=min(n,l+3);r++) Ans=min(Ans,Calc(l,r,Total));
    memset(MinVal,0x3f,sizeof(MinVal));
    for(int r=5;r<=n;r++){
        int l=r-4;
        int LVal=PreApt[l-1]-PreTpa[l-1]-Apt(l-2)-Apt(l-1);
        int LMask=LeftMask(l);
        MinVal[LMask]=min(MinVal[LMask],LVal);
        int RVal=Total-PreApt[r-2]+PreTpa[r-2]-Apt(r-1)-Apt(r);
        int RMask=RightMask(r);
        for(int Mask=0;Mask<16;Mask++) if(MinVal[Mask]<Inf){
            Ans=min(Ans,MinVal[Mask]+RVal+__builtin_popcount(Mask&RMask));
        }
    }
    printf("%d\n",Ans);
}
int main(){
    scanf("%d%d",&c,&T);
    while(T--) Solve();
    return 0;
}
