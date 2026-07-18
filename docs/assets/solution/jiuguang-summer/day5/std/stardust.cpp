#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 100010
using namespace std;

struct edge {
    int St,Ed;
}Edge[MAXN];

int T,n,Col[MAXN];

bool Check(int Root) {
    for (int i=1;i<=n-1;i++)
        if (Col[Edge[i].St]!=Col[Edge[i].Ed]&&Edge[i].St!=Root&&Edge[i].Ed!=Root) return 0;
    return 1;
}

void Solve() {
    scanf("%d",&n);
    for (int i=1;i<=n-1;i++) {
        scanf("%d%d",&Edge[i].St,&Edge[i].Ed);
    }
    for (int i=1;i<=n;i++) scanf("%d",&Col[i]);
    int u=0,v=0;
    for (int i=1;i<=n-1;i++) {
        if (Col[Edge[i].St]!=Col[Edge[i].Ed]) {
            u=Edge[i].St;v=Edge[i].Ed;
            break;
        }
    }
    if (!u) puts("YES"),puts("1");
    else if (Check(u)) puts("YES"),printf("%d\n",u);
    else if (Check(v)) puts("YES"),printf("%d\n",v);
    else puts("NO");
    return;
}

int main() {
    freopen("stardust.in","r",stdin);
    freopen("stardust.out","w",stdout);
    scanf("%d",&T);
    while (T-->0){Solve();}
    return 0;
}
