#include <cstdio>
#include <algorithm>
#define MAXN 100010
using namespace std;
int T,n,a,b,c[MAXN];
int Gcd(int x,int y){
    return y?Gcd(y,x%y):x;
}
void Solve(){
    scanf("%d%d%d",&n,&a,&b);
    int d=Gcd(a,b);
    for(int i=1;i<=n;i++) scanf("%d",&c[i]),c[i]%=d;
    sort(c+1,c+n+1);
    int Max=c[1]+d-c[n];
    for(int i=2;i<=n;i++) Max=max(Max,c[i]-c[i-1]);
    printf("%d\n",d-Max);
}
int main(){
    scanf("%d",&T);
    while(T-->0) Solve();
    return 0;
}
