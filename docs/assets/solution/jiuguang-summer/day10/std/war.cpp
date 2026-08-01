#include <set>
#include <cstdio>
#include <algorithm>
#define MAXN 100010
using namespace std;

int c,n,m,q,Fa[MAXN],Size[MAXN];
set <int> Against[MAXN];

int Find(int x) {
    return Fa[x]==x?x:Fa[x]=Find(Fa[x]);
}

void Merge(int x,int y) {
    if (Size[x]>Size[y]) swap(x,y);
    for (set<int>::iterator it=Against[x].begin();it!=Against[x].end();it++) {
        int To=Find(*it);
        Against[To].erase(x);
        Against[To].insert(y);
        Against[y].insert(To);
    }
    Against[x].clear();
    Fa[x]=y;
    Size[y]+=Size[x];
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("war.in","r",stdin);
    freopen("war.out","w",stdout);
#endif
    scanf("%d",&c);
    scanf("%d%d%d",&n,&m,&q);
    for (int i=1;i<=n;i++) Fa[i]=i,Size[i]=1;
    for (int i=1;i<=m;i++) {
        int x,y;
        scanf("%d%d",&x,&y);
        Against[x].insert(y);
        Against[y].insert(x);
    }
    while (q-->0) {
        int x,y;
        scanf("%d%d",&x,&y);
        x=Find(x);y=Find(y);
        if (x==y) {
            puts("Yes");
            continue;
        }
        if (Against[x].find(y)!=Against[x].end()) {
            puts("No");
            continue;
        }
        Merge(x,y);
        puts("Yes");
    }
    return 0;
}
