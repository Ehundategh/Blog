/*
Author:Ehundategh
Date:2026/7/30
Name:beads.cpp
You steal,I kill.
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 1000010
using namespace std;
int T,n,q,Line[MAXN],Last[MAXN],C[MAXN],Ans[MAXN];
struct query{
    int l,r,p;
}Q[MAXN];
bool cmp(query a,query b){
    if(a.r!=b.r) return a.r<b.r;
    return a.l<b.l;
}
int lowbit(int x){return x&-x;}
void Modify(int x,int Val){
    for(;x<=n;x+=lowbit(x)) C[x]+=Val;
}
int Query(int x){
    int Ret=0;
    for(;x;x-=lowbit(x)) Ret+=C[x];
    return Ret;
}
void Solve(){
    scanf("%d%d",&n,&q);
    memset(C,0,sizeof(C));
    for(int i=1;i<=n;i++) scanf("%d",&Line[i]);
    for(int i=1;i<=q;i++){
        scanf("%d%d",&Q[i].l,&Q[i].r);
        Q[i].p=i;
    }
    sort(Q+1,Q+q+1,cmp);
    int Now=0;
    for(int i=1;i<=q;i++){
        while(Now<Q[i].r){
            Now++;
            if(Last[Line[Now]]) Modify(Last[Line[Now]],-1);
            Modify(Now,1);
            Last[Line[Now]]=Now;
        }
        Ans[Q[i].p]=Query(Q[i].r)-Query(Q[i].l-1);
    }
    for(int i=1;i<=q;i++) printf("%d\n",Ans[i]);
    for(int i=1;i<=n;i++) Last[Line[i]]=0;
}
int main(){
    int c;
    scanf("%d%d",&c,&T);
    while(T-->0) Solve();
    return 0;
}
