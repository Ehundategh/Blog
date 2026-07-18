#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n,In1,In2,r,T;
struct point{
    int x,y;
}Point[1000010];

bool cmp(point a,point b){
    if(a.x==b.x) return a.y<b.y;
    return a.x<b.x;
}

void Solve(){
    int Count=0;bool Tag=1;
    scanf("%d%d",&n,&r);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&In1,&In2);
        if(1ll*In1*In1+1ll*In2*In2>1ll*r*r){
            i--,n--;
            continue;
        }
        if(In1==0&&In2==0){Tag=0;i--,n--;continue;}
        int Gcd=__gcd(abs(In1),abs(In2));
        In1/=Gcd;In2/=Gcd;
        Point[i]={In1,In2};
    }
    if (!Tag) {puts("1");return;}
    sort(Point+1,Point+n+1,cmp);
    for(int i=1;i<=n;i++){
        if((Point[i].x!=Point[i-1].x||Point[i].y!=Point[i-1].y)||(i==1)) Count++;
    }
    printf("%d\n",Count);
    return;
}

int main() {
    freopen("smoke.in","r",stdin);
    freopen("smoke.out","w",stdout);
    scanf("%d",&T);
    while (T-->0) {Solve();}
    return 0;
}
