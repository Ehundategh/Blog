#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "locate.h"
using namespace std;

const int MaxQuery=200;
int n,Count,MaxCount,Case;
vector<int> Line,Used;

void Fail(const char *Message){
    fprintf(stderr,"Case %d: %s\n",Case,Message);
    exit(1);
}

int Query(int l,int r){
    if(l<1||r>n||l>=r) Fail("Invalid query interval");
    if(++Count>MaxQuery) Fail("Too many queries");
    int Max=-1,Second=-1,MaxPos=-1,SecondPos=-1;
    for(int i=l;i<=r;i++){
        if(Line[i]>Max){
            Second=Max;SecondPos=MaxPos;
            Max=Line[i];MaxPos=i;
        }
        else if(Line[i]>Second){
            Second=Line[i];SecondPos=i;
        }
    }
    return SecondPos;
}

int GetScore(){
    if(MaxCount<=40) return 100;
    if(MaxCount<=80) return 70;
    if(MaxCount<=120) return 40;
    return 20;
}

int main(){
    int c,T;
    if(scanf("%d%d",&c,&T)!=2||c<0||T<1) Fail("Invalid test header");
    Init(c,T);
    for(Case=1;Case<=T;Case++){
        if(scanf("%d",&n)!=1||n<2) Fail("Invalid n");
        Line.assign(n+1,0);Used.assign(n+1,0);
        for(int i=1;i<=n;i++){
            if(scanf("%d",&Line[i])!=1||Line[i]<1||
               Line[i]>n||Used[Line[i]]) Fail("Invalid permutation");
            Used[Line[i]]=1;
        }
        Count=0;
        int Ans=Locate(c,n),Correct=1;
        for(int i=1;i<=n;i++) if(Line[i]==n) Correct=i;
        if(Ans!=Correct){
            puts("Wrong answer");
            return 0;
        }
        MaxCount=max(MaxCount,Count);
    }
    puts("Correct!");
    printf("Max queries used: %d\n",MaxCount);
    printf("Score ratio: %d%%\n",GetScore());
}
