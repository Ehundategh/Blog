#include "canal.h"
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

static int N,HiddenX,HiddenA,HiddenY,HiddenB,Used,MaxUsed;
static bool Answered;
static vector<int> W,V;

static void Fail(const char *Message){
    fprintf(stderr,"Interaction error: %s\n",Message);
    exit(1);
}

long long Travel(vector<int> Choice){
    if(Answered) Fail("Travel called after Answer");
    if((int)Choice.size()!=N+1) Fail("invalid choice length");
    if(++Used>200) Fail("too many travelers");
    long long Ret=0;
    for(int i=1;i<=N;i++){
        if(Choice[i]!=0&&Choice[i]!=1) Fail("choice must be 0 or 1");
        Ret+=Choice[i]?V[i]:W[i];
    }
    if(Choice[HiddenX]==HiddenA&&Choice[HiddenY]==HiddenB){
        Ret-=HiddenA?V[HiddenX]:W[HiddenX];
    }
    return Ret;
}

void Answer(int x,int a,int y,int b){
    if(Answered) Fail("Answer called more than once");
    if(x<1||x>N||y<1||y>N||x==y) Fail("invalid waterway index");
    if((a!=0&&a!=1)||(b!=0&&b!=1)) Fail("invalid direction");
    bool Ok=(x==HiddenX&&a==HiddenA&&y==HiddenY&&b==HiddenB)||
            (x==HiddenY&&a==HiddenB&&y==HiddenX&&b==HiddenA);
    if(!Ok){
        puts("Wrong answer");
        exit(0);
    }
    Answered=true;
}

int main(){
    int c,T;
    if(scanf("%d%d",&c,&T)!=2) Fail("invalid input header");
    Init(c,T);
    MaxUsed=0;
    for(int Case=1;Case<=T;Case++){
        scanf("%d",&N);
        W.assign(N+1,0);V.assign(N+1,0);
        for(int i=1;i<=N;i++) scanf("%d",&W[i]);
        for(int i=1;i<=N;i++) scanf("%d",&V[i]);
        scanf("%d%d%d%d",&HiddenX,&HiddenA,&HiddenY,&HiddenB);
        Used=0;Answered=false;
        Locate(c,N,W,V);
        if(!Answered) Fail("Locate returned without Answer");
        MaxUsed=max(MaxUsed,Used);
    }
    double Ratio=MaxUsed<=80?1.0:80.0/MaxUsed;
    puts("Correct!");
    printf("Max travelers used: %d\n",MaxUsed);
    if(Ratio==1.0) puts("Score ratio: 100%");
    else printf("Score ratio: %.6f%%\n",Ratio*100.0);
    return 0;
}
