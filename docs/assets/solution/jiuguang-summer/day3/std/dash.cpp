/*
Author:Ehundategh
Date:2026/7/14
Name:dash.cpp
You steal,I kill.
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 200010
using namespace std;
int n,m;
char S[MAXN],T[MAXN];
int Jump[MAXN][26],Dis[MAXN][26],FPos[26];
int main() {
    freopen("dash.in","r",stdin);
    freopen("dash.out","w",stdout);
    memset(FPos,0x3f,sizeof(FPos));
    scanf("%d%d",&n,&m);
    scanf("%s%s",S+1,T+1);
    for (int i=1;i<=n;i++) {
        FPos[S[i]-'a']=min(i,FPos[S[i]-'a']);
    }
    for (int i=n;i>=1;i--) {
        if (i!=n) Jump[i][S[i+1]-'a']=i+1,Dis[i][S[i+1]-'a']=1;
        for (int j=0;j<=25;j++) {
            if (i!=n&&S[i+1]==j+'a') continue;
            if (i==n||!Jump[i+1][j]) {
                if (FPos[j]<=n&&i>=FPos[j]) Jump[i][j]=FPos[j],Dis[i][j]=n-(i-FPos[j]);
            }
            else Jump[i][j]=Jump[i+1][j],Dis[i][j]=Dis[i+1][j]+1;
        }
    }
    int Now=1;
    long long Ans=1;
    if (S[1]!=T[1]) {
        if (!Jump[1][T[1]-'a']) {
            puts("-1"); return 0;
        }
        else Ans+=Dis[1][T[1]-'a'],Now=Jump[1][T[1]-'a'];
    }
    for (int i=2;i<=m;i++) {
        if (!Jump[Now][T[i]-'a']) {
            puts("-1"); return 0;
        }
        else Ans+=Dis[Now][T[i]-'a'],Now=Jump[Now][T[i]-'a'];
    }
    printf("%lld\n",Ans);
    return 0;
}