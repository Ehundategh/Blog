#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 1000100
using namespace std;

int n,a[MAXN],b[MAXN];
long long dp[MAXN];

int main() {
    freopen("reset.in","r",stdin);
    freopen("reset.out","w",stdout);
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    for (int i=1;i<=n-1;i++) scanf("%d",&b[i]);
    dp[0]=0;dp[1]=a[1];
    for (int i=2;i<=n;i++) {
        dp[i]=min(dp[i-1]+1ll*a[i],dp[i-2]+1ll*b[i-1]);
    }
    printf("%lld\n",dp[n]);
    return 0;
}