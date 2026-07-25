/*
Author:Ehundategh
Date:2026/7/23
Name:goldknot.cpp
You steal,I kill.
*/
#include <cmath>
#include <stack>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 1000010
using namespace std;

int Head[2][MAXN],Total[2]={0,0},Dfn[MAXN],Low[MAXN],cnd=0,SCC[MAXN],cns=0,Deg[MAXN];
int n,m,In1,In2,In3,s,c,T;
long long Sum[MAXN],Dp[MAXN],Ans=0;
stack <int> S;
queue <int> Q;

struct edge {
    int St,Ed,Next,Val;
}Edge[2][MAXN<<1];

void Edge_Add(int St,int Ed,int Val,int Type) {
    Edge[Type][++Total[Type]]={St,Ed,Head[Type][St],Val};
    Head[Type][St]=Total[Type];
}

void Tarjan(int Now) {
    Dfn[Now]=Low[Now]=++cnd;
    S.push(Now);
    for (int i=Head[0][Now];i;i=Edge[0][i].Next) {
        int To=Edge[0][i].Ed;
        if (!Dfn[To]) {
            Tarjan(To);
            Low[Now]=min(Low[Now],Low[To]);
        }
        else if (!SCC[To]) {
            Low[Now]=min(Low[Now],Dfn[To]);
        }
    }
    if (Dfn[Now]==Low[Now]) {
        cns++;
        while (S.top()!=Now) {
            SCC[S.top()]=cns;S.pop();
        }
        SCC[S.top()]=cns;S.pop();
    }
}

long long Calc(int x) {
    int Bottom=floor(sqrt(2*x*1.0+0.25)-0.5);
    return 1ll*x*(Bottom+1)-1ll*(Bottom+1)*(Bottom+2)*Bottom/6;
}

void TopSort() {
    for (int i=1;i<=cns;i++) {
        Dp[i]=-(1ll<<60);
        if (Deg[i]==0) Q.push(i);
    }
    Dp[s]=Sum[s];
    while (Q.size()) {
        int Now=Q.front(); Q.pop();
        Ans=max(Ans,Dp[Now]);
        for (int i=Head[1][Now];i;i=Edge[1][i].Next) {
            int To=Edge[1][i].Ed;
            Dp[To]=max(Dp[To],Dp[Now]+Edge[1][i].Val+Sum[To]);
            Deg[To]--;
            if (Deg[To]==0) Q.push(To);
        }
    }
    return;
}

void Solve() {
    scanf("%d%d",&n,&m); Ans=0,Total[0]=Total[1]=0,cnd=0,cns=0;
    for (int i=1;i<=n;i++) Head[0][i]=Head[1][i]=0,Dfn[i]=Low[i]=0,SCC[i]=0,Deg[i]=0,Dp[i]=0,Sum[i]=0;
    for (int i=1;i<=m;i++) {
        scanf("%d%d%d",&In1,&In2,&In3);
        Edge_Add(In1,In2,In3,0);
    }
    scanf("%d",&s);
    for (int i=1;i<=n;i++) {
        if (!Dfn[i]) Tarjan(i);
    }s=SCC[s];
    for (int i=1;i<=m;i++) {
        int S1=SCC[Edge[0][i].St],S2=SCC[Edge[0][i].Ed],V=Edge[0][i].Val;
        if (S1==S2) {
            Sum[S1]+=Calc(V);
        }
        else {
            Edge_Add(S1,S2,V,1); Deg[S2]++;
        }
    }
    TopSort();
    printf("%lld\n",Ans);
}

int main() {
    freopen("goldknot.in","r",stdin);
    freopen("goldknot.out","w",stdout);
    scanf("%d%d",&c,&T);
    while (T-->0) Solve();
    return 0;
}
