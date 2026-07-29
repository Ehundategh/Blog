#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 100010
using namespace std;
int n,m,r;
long long Ans=0,f[MAXN];
void Solve() {
    scanf("%d%d",&n,&m);
    Ans=0;
    r=min(n,m);
    for (int i=r;i>=1;i--) {
        f[i]=1ll*(n/i)*(m/i);
        for (int j=2;i*j<=r;j++) {
            f[i]-=(f[i*j]);
        }
        Ans+=1ll*2*i*f[i];
    }
    Ans-=1ll*n*m;
    printf("%lld\n",Ans);
}
int main() {
    int c,T;
    scanf("%d%d",&c,&T);
    while(T-->0) Solve();
    return 0;
}
