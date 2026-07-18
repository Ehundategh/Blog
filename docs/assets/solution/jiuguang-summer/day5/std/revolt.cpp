#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 200010
#define LSon Node[Now].LeftSon
#define RSon Node[Now].RightSon
using namespace std;
const long long INF=10000000000000000;

int n,m,cnt=0,Line[MAXN],Mapping[MAXN];
long long Tag=0;

void Discrete() {sort(Mapping+1,Mapping+n+1);m=unique(Mapping+1,Mapping+n+1)-Mapping-1;return;}
int Find(int x) {return lower_bound(Mapping+1,Mapping+m+1,x)-Mapping;}

struct node {
    int l,r,LeftSon,RightSon;
    long long Min,MinSum;
}Node[MAXN<<2];

void Update(int Now) {Node[Now].Min=min(Node[LSon].Min,Node[RSon].Min);Node[Now].MinSum=min(Node[LSon].MinSum,Node[RSon].MinSum);return;}

int Build(int l,int r) {
    int Now=++cnt;
    Node[Now]={l,r,0,0,INF,INF};
    if (l==r) return Now;
    int Mid=(l+r)>>1;
    LSon=Build(l,Mid);RSon=Build(Mid+1,r);
    return Now;
}

void Modify(int Now,int Pos,long long Val) {
    if (Node[Now].l==Node[Now].r) {
        Node[Now].Min=min(Node[Now].Min,Val);
        Node[Now].MinSum=min(Node[Now].MinSum,Val+Mapping[Node[Now].l]);
        return;
    }
    int Mid=(Node[Now].l+Node[Now].r)>>1;
    if (Pos<=Mid) Modify(LSon,Pos,Val);
    else Modify(RSon,Pos,Val);
    Update(Now);return;
}

long long Query(int Now,int l,int r,int Type) {
    if (l>r||Node[Now].l>r||Node[Now].r<l) return INF;
    if (Node[Now].l>=l&&Node[Now].r<=r) return Type?Node[Now].MinSum:Node[Now].Min;
    return min(Query(LSon,l,r,Type),Query(RSon,l,r,Type));
}

long long Calc(int Val) {
    int Pos=Find(Val);
    return Tag+min(Query(1,1,Pos,0)+Val,Query(1,Pos+1,m,1));
}

int main() {
    freopen("revolt.in","r",stdin);
    freopen("revolt.out","w",stdout);
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&Line[i]),Mapping[i]=Line[i];
    Discrete();
    Build(1,m);
    int Pos=Find(Line[1]);
    Modify(1,Pos,0);
    for (int i=3;i<=n;i+=2) {
        long long Left=Calc(Line[i]);
        long long Right=Calc(Line[i-1]);
        Tag+=max(Line[i],Line[i-1]);
        Pos=Find(Line[i-1]);
        Modify(1,Pos,Left-Tag);
        Pos=Find(Line[i]);
        Modify(1,Pos,Right-Tag);
    }
    printf("%lld\n",Tag+Node[1].MinSum);
    return 0;
}
