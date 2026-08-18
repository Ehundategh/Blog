#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define MAXN 200010
using namespace std;

int c,T,n,q,MaxDepth,LastDepth,Father[MAXN],Depth[MAXN],Right[MAXN];
long long Line[MAXN],Pre[MAXN];

struct data{
    vector <int> St,Ed,Log;
    vector <long long> Sum;
    vector <vector <long long> > ST;
    void Clear(){St.clear();Ed.clear();Log.clear();Sum.clear();ST.clear();}
    void Build(){
        int Len=St.size();
        Sum.resize(Len);Log.assign(Len+1,0);
        for(int i=0;i<Len;i++) Sum[i]=Pre[Ed[i]]-Pre[St[i]-1];
        for(int i=2;i<=Len;i++) Log[i]=Log[i>>1]+1;
        if(!Len) return;
        ST.assign(Log[Len]+1,vector <long long>(Len));ST[0]=Sum;
        for(int j=1;j<(int)ST.size();j++){
            for(int i=0;i+(1<<j)<=Len;i++){
                ST[j][i]=max(ST[j-1][i],ST[j-1][i+(1<<(j-1))]);
            }
        }
        return;
    }
    long long Query(int l,int r){
        if(l>r) return -1;
        int p=Log[r-l+1];
        return max(ST[p][l],ST[p][r-(1<<p)+1]);
    }
}Level[MAXN];

bool Check(int d,int l,int r,long long k){
    data &Now=Level[d];
    int x=lower_bound(Now.Ed.begin(),Now.Ed.end(),l)-Now.Ed.begin();
    int y=upper_bound(Now.St.begin(),Now.St.end(),r)-Now.St.begin()-1;
    if(x>y) return false;
    int Left=max(l,Now.St[x]),RightPos=min(r,Now.Ed[x]);
    long long Ret=Left<=RightPos?Pre[RightPos]-Pre[Left-1]:0;
    if(x!=y){
        Left=max(l,Now.St[y]);RightPos=min(r,Now.Ed[y]);
        if(Left<=RightPos) Ret=max(Ret,Pre[RightPos]-Pre[Left-1]);
    }
    Ret=max(Ret,Now.Query(x+1,y-1));
    return Ret>=k;
}

int Calc(int l,int r,long long k){
    int Left=1,RightPos=MaxDepth;
    while(Left<RightPos){
        int Mid=(Left+RightPos+1)>>1;
        if(Check(Mid,l,r,k)) Left=Mid;
        else RightPos=Mid-1;
    }
    return Left;
}

void Solve(){
    for(int i=1;i<=LastDepth;i++) Level[i].Clear();
    scanf("%d%d",&n,&q);
    Father[1]=0;Depth[1]=1;MaxDepth=1;
    for(int i=2;i<=n;i++) scanf("%d",&Father[i]);
    Pre[0]=0;
    for(int i=1;i<=n;i++){
        scanf("%lld",&Line[i]);
        Pre[i]=Pre[i-1]+Line[i];
        Right[i]=i;
        if(i>1) Depth[i]=Depth[Father[i]]+1;
        MaxDepth=max(MaxDepth,Depth[i]);
    }
    for(int i=n;i>=2;i--) Right[Father[i]]=max(Right[Father[i]],Right[i]);
    for(int i=1;i<=n;i++){
        Level[Depth[i]].St.push_back(i);
        Level[Depth[i]].Ed.push_back(Right[i]);
    }
    for(int i=1;i<=MaxDepth;i++) Level[i].Build();
    LastDepth=MaxDepth;
    while(q-->0){
        int l,r;long long k;
        scanf("%d%d%lld",&l,&r,&k);
        printf("%d\n",Calc(l,r,k));
    }
    return;
}

int main(){
    scanf("%d%d",&c,&T);
    while(T-->0) Solve();
    return 0;
}
