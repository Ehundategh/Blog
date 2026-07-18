#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct point {
    int a,b;
}P[200010];

bool cmp(point x,point y) {
    if (x.a<=x.b && y.a>y.b) return true;
    if (x.a>x.b && y.a<=y.b) return false;
    else if (x.a<=x.b && y.a<=y.b) return x.a<y.a;
    else return x.b>y.b;
}

int main() {
    freopen("spore.in","r",stdin);
    freopen("spore.out","w",stdout);
    int n;long long Now=0,Ans=0;
    scanf("%d",&n);
    for (int i=1;i<=n;i++) {
        scanf("%d%d",&P[i].a,&P[i].b);
    }
    sort(P+1,P+n+1,cmp);
    for (int i=1;i<=n;i++) {
        if (P[i].a>Now){Ans+=(1ll*P[i].a-Now);Now=1ll*P[i].a;}
        Now-=1ll*P[i].a;Now+=1ll*P[i].b;
    }
    printf("%lld\n",Ans);
    return 0;
}