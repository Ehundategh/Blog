#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const long long INF=1e18;
int T;
long long n,k,x,y,X[100010],Y[100010];
long long PreX,PreY,Ans=0,NowX,NowY;
void Deal(long long a,long long b,long long &Max,long long &Min){
    if (a==0&&b>0) {Max=0,Min=INF;}
    if (a>0&&b>0) {
        Min=max(Min,(a+b-1)/a);
    }
    if (a<0) {
        if (b>0) {Max=0,Min=INF;}
        else if (b==0) {Max=min(Max,0ll);Min=max(Min,0ll);}
        else Max=min(Max,b/a);
    }
    return;
}
long long Get(long long a,long long b,long long t) {
    long long Max=INF,Min=0;
    Deal(n*k+PreX+PreY,a+b-t*k,Max,Min);
    Deal(n*k-PreX+PreY,-a+b-t*k,Max,Min);
    Deal(n*k+PreX-PreY,a-b-t*k,Max,Min);
    Deal(n*k-PreX-PreY,-a-b-t*k,Max,Min);
    if (Max>=Min) return Min*n+t;
    else return INF;
}
void Solve() {
    PreX=PreY=NowX=NowY=0;Ans=INF;
    scanf("%lld%lld%lld%lld",&n,&k,&x,&y);
    for (int i=1;i<=n;i++) {
        scanf("%lld%lld",&X[i],&Y[i]);
        PreX+=1ll*X[i];
        PreY+=1ll*Y[i];
    }
    if (x==0&&y==0) {puts("0");return;}
    for (int i=1;i<=n;i++) {
        NowX+=1ll*X[i];
        NowY+=1ll*Y[i];
        Ans=min(Get(x-NowX,y-NowY,i),Ans);
    }
    if (Ans==INF) puts("-1");
    else printf("%lld\n",Ans);
    return;
}

int main() {
    freopen("wind.in","r",stdin);
    freopen("wind.out","w",stdout);
    scanf("%d",&T);
    while (T-->0) Solve();
    return 0;
}