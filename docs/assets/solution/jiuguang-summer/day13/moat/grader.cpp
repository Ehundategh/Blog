#include "moat.h"
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

static int N,B,H,Round,ScoutUsed,ScoutLimit;
static vector<int> Parent,Depth,Size,DFN,Back;
static vector<long long> Weight,Bit;
static vector<bool> Cleaned;
static long long Original,Got;

static void Fail(const char *Message){
    fprintf(stderr,"Interaction error: %s\n",Message);
    exit(1);
}

static void Add(int p,long long v){for(;p<=N;p+=p&-p) Bit[p]+=v;}
static long long Sum(int p){long long Ret=0;for(;p;p-=p&-p) Ret+=Bit[p];return Ret;}

long long Scout(int u){
    if(u<1||u>N) Fail("invalid Scout index");
    if(Round>=B) Fail("Scout called after all rounds");
    if(++ScoutUsed>ScoutLimit) Fail("too many Scout calls");
    return Sum(DFN[u]+Size[u]-1)-Sum(DFN[u]-1);
}

long long Clean(int u){
    if(u<1||u>N) Fail("invalid Clean index");
    if(Round>=B) Fail("too many Clean calls");
    if(Cleaned[u]) Fail("room cleaned more than once");
    Cleaned[u]=true;
    long long Ret=Weight[u];
    Add(DFN[u],-Weight[u]);
    Weight[u]=0;Got+=Ret;Round++;
    return Ret;
}

int main(){
    int c,T;
    if(scanf("%d%d",&c,&T)!=2) Fail("invalid input header");
    Init(c,T);
    vector<double> Ratio;
    vector<long long> Treasure;
    for(int Case=1;Case<=T;Case++){
        scanf("%d%d",&N,&B);
        Weight.assign(N+1,0);Original=0;
        for(int i=1;i<=N;i++) scanf("%lld",&Weight[i]),Original+=Weight[i];
        vector<vector<int>> Adj(N+1);
        for(int i=1,u,v;i<N;i++) scanf("%d%d",&u,&v),Adj[u].push_back(v),Adj[v].push_back(u);
        Parent.assign(N+1,0);Depth.assign(N+1,0);Size.assign(N+1,1);DFN.assign(N+1,0);Back.assign(N+1,0);
        vector<int> It(N+1,0),Stack;Stack.push_back(1);Depth[1]=1;H=1;
        int Timer=0;
        while(!Stack.empty()){
            int u=Stack.back();
            if(!DFN[u]) DFN[u]=++Timer,Back[Timer]=u;
            while(It[u]<(int)Adj[u].size()&&Adj[u][It[u]]==Parent[u]) It[u]++;
            if(It[u]<(int)Adj[u].size()){
                int v=Adj[u][It[u]++];
                Parent[v]=u;Depth[v]=Depth[u]+1;H=max(H,Depth[v]);Stack.push_back(v);
            }
            else{
                Stack.pop_back();
                if(Parent[u]) Size[Parent[u]]+=Size[u];
            }
        }
        Bit.assign(N+1,0);for(int i=1;i<=N;i++) Add(DFN[i],Weight[i]);
        Cleaned.assign(N+1,false);Round=ScoutUsed=0;Got=0;ScoutLimit=2*B*H+20;
        Play(c,N,B,Parent);
        if(Round!=B) Fail("Play returned before all rounds");
        long double P=(long double)N*Got/((long double)B*Original);
        if(P>1) P=1;
        Ratio.push_back((double)P);
        Treasure.push_back(Got);
    }
    double Average=0;for(double p:Ratio) Average+=p;Average/=T;
    puts("Finished!");
    for(int i=0;i<T;i++) printf("Case %d: treasure = %lld, score ratio = %.6f%%\n",i+1,Treasure[i],Ratio[i]*100.0);
    printf("Score ratio: %.6f%%\n",Average*100.0);
    return 0;
}
