#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 200010
using namespace std;

int C[MAXN];
int lowbit(int x){return x&-x;}
int Query(int x) {
    int Ret=0;
    for (;x;x-=lowbit(x)) Ret+=C[x];
    return Ret;
}
void Modify(int x,int Val) {
    for (;x<MAXN;x+=lowbit(x)) C[x]+=Val;
    return ;
}
struct Q{
    int Value,DFN,Mark,From,Times;
}q[MAXN<<2];
bool cmp(Q a,Q b){return a.DFN<b.DFN;}
int n,MaxD[MAXN],MinD[MAXN],Size[MAXN][2],Val[MAXN],ls[MAXN],rs[MAXN],dfn[MAXN],Line[MAXN],Mapping[MAXN],Back[MAXN],cnt=0,cnd=0,cnq=0;

void Discrete() {
    sort(Line+1,Line+n+1);
    for (int i=1;i<=n;i++) {
        if (i==1||Line[i]!=Line[i-1]) Mapping[++cnt]=Line[i];
    }
    return;
}

int Find(int x) {return lower_bound(Mapping+1,Mapping+cnt+1,x)-Mapping;}

void DFS(int Now) {
    if (Now==0) return;
    dfn[Now]=++cnd;Back[cnd]=Now;
    DFS(ls[Now]);DFS(rs[Now]);
    MaxD[Now]=max(MaxD[ls[Now]],max(MaxD[rs[Now]],dfn[Now]));MinD[Now]=dfn[Now];
    if (ls[Now]) {
        q[++cnq]={Val[Now]-1,MaxD[ls[Now]],Now,0,1};
        q[++cnq]={Val[Now]-1,MinD[ls[Now]]-1,Now,0,-1};
    }
    if (rs[Now]) {
        q[++cnq]={Val[Now],MaxD[rs[Now]],Now,1,1};
        q[++cnq]={Val[Now],MinD[rs[Now]]-1,Now,1,-1};
    }
}

void Deal() {
    sort(q+1,q+cnq+1,cmp);
    int p=0;
    for (int i=1;i<=cnq;i++) {
        while (p<q[i].DFN) {
            p++;
            Modify(Val[Back[p]],1);
        }
        if (q[i].From==0) {
            Size[q[i].Mark][0]+=Query(q[i].Value)*q[i].Times;
        }
        else {
            Size[q[i].Mark][1]+=(Query(cnt)-Query(q[i].Value))*q[i].Times;
        }
    }
    return ;
}

int main() {
    freopen("trade.in","r",stdin);
    freopen("trade.out","w",stdout);
    memset(Size,0,sizeof(Size));
    scanf("%d",&n);
    for (int i=1;i<=n;i++) {
        scanf("%d",&Line[i]); Val[i]=Line[i];
    }
    Discrete();for (int i=1;i<=n;i++) Val[i]=Find(Val[i]);
    for (int i=1;i<=n;i++) {
        scanf("%d%d",&ls[i],&rs[i]);
    }
    DFS(1);
    Deal();long long Ans=0;
    for (int i=1;i<=n;i++) {
        Ans+=1ll*Size[i][0]*Size[i][1];
    }
    printf("%lld\n",Ans);
    return 0;
}