#include <cstdio>
#define MAXN 100010
using namespace std;
int n,Last,Now;
long long Ans;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&Now);
        if(Now>Last) Ans+=Now-Last;
        Last=Now;
    }
    printf("%lld\n",Ans);
    return 0;
}
