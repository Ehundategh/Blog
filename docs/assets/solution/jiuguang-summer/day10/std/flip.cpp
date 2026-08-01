#include <queue>
#include <cstdio>
#define MAXN 200010
using namespace std;

int c,n,Line[MAXN],Tree[MAXN<<2];
char Str[MAXN];
queue <int> Pos[26];

void Modify(int Now,int l,int r,int x) {
    if (l==r) {
        Tree[Now]=1;
        return;
    }
    int Mid=(l+r)>>1;
    if (x<=Mid) Modify(Now<<1,l,Mid,x);
    else Modify(Now<<1|1,Mid+1,r,x);
    Tree[Now]=Tree[Now<<1]+Tree[Now<<1|1];
}

int Query(int Now,int l,int r,int x,int y) {
    if (x>y||l>y||r<x) return 0;
    if (l>=x&&r<=y) return Tree[Now];
    int Mid=(l+r)>>1;
    return Query(Now<<1,l,Mid,x,y)+Query(Now<<1|1,Mid+1,r,x,y);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("flip.in","r",stdin);
    freopen("flip.out","w",stdout);
#endif
    scanf("%d",&c);
    scanf("%d%s",&n,Str+1);
    for (int i=1;i<=n;i++) Pos[Str[i]-'a'].push(i);
    for (int i=n;i>=1;i--) {
        int x=Str[i]-'a';
        Line[n-i+1]=Pos[x].front();
        Pos[x].pop();
    }
    long long Ans=0;
    for (int i=1;i<=n;i++) {
        Ans+=Query(1,1,n,Line[i]+1,n);
        Modify(1,1,n,Line[i]);
    }
    printf("%lld\n",Ans);
    return 0;
}
