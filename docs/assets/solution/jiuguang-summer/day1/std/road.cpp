#include <cstdio>
#include <algorithm>
using namespace std;
int n,Last,Now;
long long Ans=0;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&Now);
        Ans+=max(Now-Last,0);
        Last=Now;
    }
    printf("%lld\n",Ans);
    return 0;
}
