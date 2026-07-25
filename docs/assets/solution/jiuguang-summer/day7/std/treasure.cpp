/*
Author:Ehundategh
Date:2026/7/21
Name:treasure.cpp
You steal,I kill.
*/
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n,m;
int Val[13][13],In1,In2,In3,Pow[13]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096},B[4097];
long long Dp[13][4097],Cost[13][4097],Ans=0x3f3f3f3f3f3f3f3f;
int Lowbit(int x){return x&-x;}
vector <int> Valid[4097];
vector <long long> Pri[4097];
int main(){
    freopen("treasure.in","r",stdin);
    freopen("treasure.out","w",stdout);
    memset(Val,0x3f,sizeof(Val));
    memset(Cost,0x3f,sizeof(Cost));
    memset(Dp,0x3f,sizeof(Dp));
    scanf("%d%d",&n,&m);
    int Temp=1;
    for(int i=1;i<=n;i++){
        B[Temp]=i;
        Temp<<=1;
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&In1,&In2,&In3);
        Val[In1][In2]=min(Val[In1][In2],In3);
        Val[In2][In1]=min(Val[In2][In1],In3);
    }
    for(int i=0;i<(1<<n);i++){
        for(int j=1;j<=n;j++){
            if((i&(1<<(j-1)))==0) continue;
            for(int k=1;k<=n;k++){
                Cost[k][i]=min(Cost[k][i],1ll*Val[k][j]);
            }
        }
    }
    for(int i=0;i<(1<<n);i++){
        for(int j=(i-1)&i;;j=(j-1)&i){
            int Diff=i-j; bool Tag=1;
            long long Sum=0;
            while(Diff){
                if(Cost[B[Lowbit(Diff)]][j]>1e6){Tag=0; break;}
                Sum+=Cost[B[Lowbit(Diff)]][j];
                Diff-=Lowbit(Diff);
            }
            if(Tag){Valid[i].push_back(j); Pri[i].push_back(Sum);}
            if(j==0) break;
        }
    }
    for (int i=1;i<=n;i++) {
        Dp[1][1<<(i-1)]=0;
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=(1<<n)-1;j++){
            for(int k=0;k<Valid[j].size();k++){
                Dp[i][j]=min(Dp[i][j],Dp[i-1][Valid[j][k]]+(i-1)*Pri[j][k]);
            }
        }
        Ans=min(Ans,Dp[i][(1<<n)-1]);
    }
    printf("%lld\n",Ans);
    return 0;
}
