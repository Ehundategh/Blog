/*
Author:Ehundategh
Date:2026/7/14
Name:fish.cpp
You steal,I kill.
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 200010
using namespace std;

int n,q,k;
int Line[MAXN],Jump[MAXN][24],In1,In2;
long long Sum=0;

struct Queue {
    int Tail=0,Head=1,Num[MAXN<<1];
    void Push(int a){Num[++Tail]=a;}
    void PopF(){Head++;} void PopB(){Tail--;}
    int Front(){return Num[Head];} int Back(){return Num[Tail];}
    int Size(){return Tail-Head+1;}
}Q;

int main() {
    freopen("fish.in","r",stdin);
    freopen("fish.out","w",stdout);
    scanf("%d%d%d",&n,&q,&k);
    for (int i=1;i<=n;i++){scanf("%d",&Line[i]);}
    int p=n+1;
    for (int i=n;i>=1;i--) {
        while (Q.Size()&&Line[Q.Back()]>=Line[i]) Q.PopB();
        Q.Push(i);
        int Min=Line[Q.Front()];
        Sum+=Line[i];
        while (Sum>1ll*k*Min) {
            p--;
            if (Q.Size()&&Q.Front()==p) Q.PopF(),Min=Line[Q.Front()];
            Sum-=Line[p];
        }
        Jump[i][0]=p;
    }
    Jump[n+1][0]=n+1;
    for (int j=1;j<=22;j++) {
        for (int i=1;i<=n;i++) {
            Jump[i][j]=Jump[Jump[i][j-1]][j-1];
        }
        Jump[n+1][j]=n+1;
    }
    while (q-->0) {
        scanf("%d%d",&In1,&In2);
        int Now=In1;int Ans=0;
        for (int i=22;i>=0;i--) {
            if (Jump[Now][i]<=In2) {
                Ans+=(1<<i);Now=Jump[Now][i];
            }
        }
        Ans++;
        printf("%d\n",Ans);
    }
    return 0;
}