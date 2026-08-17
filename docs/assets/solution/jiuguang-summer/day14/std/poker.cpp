/*
Author:Ehundategh
Date:2026/8/17
Name:poker.cpp
You steal,I kill.
*/
#include <vector>
#include <cstdio>
#include <cstring>
#define MAXN 21
using namespace std;
int c,T,n,a[MAXN],b[MAXN];
signed char Dp[1<<20];
vector <int> Pair;

int Calc(int Now){
    if(Dp[Now]!=-1) return Dp[Now];
    for(int i=0;i<(int)Pair.size();i++){
        if((Now&Pair[i])==Pair[i]&&!Calc(Now^Pair[i])) return Dp[Now]=1;
    }
    return Dp[Now]=0;
}

void Solve(){
    scanf("%d",&n);Pair.clear();
    for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(a[i]==a[j]||b[i]==b[j]) Pair.push_back((1<<(i-1))|(1<<(j-1)));
        }
    }
    memset(Dp,-1,sizeof(signed char)*(1<<n));
    puts(Calc((1<<n)-1)?"Ehundategh":"tfbz");
}

int main(){
    scanf("%d%d",&c,&T);
    while(T-->0) Solve();
    return 0;
}
