#include <cstdio>
#include <algorithm>
#define MAXN 1000010
using namespace std;

int c,n,LineA[MAXN],LineB[MAXN];

int main() {
#ifndef ONLINE_JUDGE
    freopen("race.in","r",stdin);
    freopen("race.out","w",stdout);
#endif
    scanf("%d",&c);
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&LineB[i]);
    for (int i=1;i<=n;i++) scanf("%d",&LineA[i]);
    sort(LineA+1,LineA+n+1);
    sort(LineB+1,LineB+n+1);
    int LeftA=1,RightA=n,LeftB=1,RightB=n,Ans=0;
    while (LeftA<=RightA) {
        if (LineA[RightA]>LineB[RightB]) {
            Ans++;
            RightA--;RightB--;
        }
        else if (LineA[LeftA]>LineB[LeftB]) {
            Ans++;
            LeftA++;LeftB++;
        }
        else {
            if (LineA[LeftA]<LineB[RightB]) Ans--;
            LeftA++;RightB--;
        }
    }
    printf("%d\n",Ans);
    return 0;
}
