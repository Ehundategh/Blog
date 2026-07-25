/*
Author:Ehundategh
Date:2026/7/21
Name:aroma.cpp
You steal,I kill.
*/
#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 200010
struct item{
    int Val,Limit;
}Line[MAXN];
bool cmp(item a,item b){return a.Val>b.Val;}
int n,q,Fa[MAXN],cnt=0,In1;
long long Ans[MAXN];
int Find(int x){return Fa[x]==x?x:Fa[x]=Find(Fa[x]);}
int main(){
    freopen("aroma.in","r",stdin);
    freopen("aroma.out","w",stdout);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d%d",&Line[i].Val,&Line[i].Limit);
    sort(Line+1,Line+n+1,cmp);
    for(int i=0;i<=n;i++) Fa[i]=i;
    for(int i=1;i<=n;i++){
        int Day=Find(min(Line[i].Limit,n));
        if(Day==0) continue;
        Fa[Day]=Find(Day-1);
        cnt++;
        Ans[cnt]=Ans[cnt-1]+Line[i].Val;
    }
    while(q-->0){
        scanf("%d",&In1);
        printf("%lld\n",Ans[min(In1,cnt)]);
    }
    return 0;
}
