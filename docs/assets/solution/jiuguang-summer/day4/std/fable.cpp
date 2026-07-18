#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 200010
using namespace std;

int n,k,Line[MAXN],Ans=0;
long long c,Pre[MAXN];

struct Queue {
    int Tail=0,Head=1,Num[MAXN<<1];
    void Push(int a){Num[++Tail]=a;}
    void PopF(){Head++;} void PopB(){Tail--;}
    int Front(){return Num[Head];} int Back(){return Num[Tail];}
    int Size(){return Tail-Head+1;}
}Q;

long long Calc(int x) {
    return Pre[x]-Pre[x-k];
}

int main() {
    freopen("fable.in","r",stdin);
    freopen("fable.out","w",stdout);
    scanf("%d%d%lld",&n,&k,&c);
    for (int i=1;i<=n;i++) {
        scanf("%d",&Line[i]); Pre[i]=Pre[i-1]+Line[i]*1ll;
    }
    int p=k;
    Q.Push(k);
    for (int i=1;i<=n-k+1;i++) {
        if (Q.Size()&&Q.Front()-k<i-1) Q.PopF();
        long long Max=0;
        if (p<n) { Max=Calc(p+1); if (Q.Size()) Max=max(Max,Calc(Q.Front())); }
        while (p<n&&Pre[p+1]-Pre[i-1]-Max<=c) {
            p++;
            while (Q.Size()&&Calc(Q.Back())<=Calc(p)) Q.PopB();
            Q.Push(p);
            if(p<n) Max=max(Calc(p+1),Calc(Q.Front()));
        }
        Ans=max(p-i+1,Ans);
    }
    printf("%d\n",Ans);
}