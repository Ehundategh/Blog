/*
Author:Ehundategh
Date:2026/7/23
Name:flutter.cpp
You steal,I kill.
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 500010
#define LSon Node[Now].LeftSon
#define RSon Node[Now].RightSon
using namespace std;
const int INF=2000000000;

int n,m,In1,In2,In3,cnt=0,Line[MAXN];

struct Data{
    int Len,Max,SecMax,HisMax,MaxCnt;
    long long Sum;
};

struct tag{
    int MaxAdd,OtherAdd,MaxHis,OtherHis;
};

tag Empty(){return {0,0,0,0};}
Data Null(){return {0,-INF,-INF,-INF,0,0};}

Data operator+(const Data &A,const Data &B){
    if(!A.Len) return B;
    if(!B.Len) return A;
    Data Ret={A.Len+B.Len,0,0,max(A.HisMax,B.HisMax),0,A.Sum+B.Sum};
    if(A.Max==B.Max) Ret.Max=A.Max,Ret.MaxCnt=A.MaxCnt+B.MaxCnt,Ret.SecMax=max(A.SecMax,B.SecMax);
    else if(A.Max>B.Max) Ret.Max=A.Max,Ret.MaxCnt=A.MaxCnt,Ret.SecMax=max(A.SecMax,B.Max);
    else Ret.Max=B.Max,Ret.MaxCnt=B.MaxCnt,Ret.SecMax=max(A.Max,B.SecMax);
    return Ret;
}

Data operator*(const tag &Tag,const Data &B){
    Data Ret=B;
    Ret.HisMax=max(Ret.HisMax,Ret.Max+Tag.MaxHis);
    Ret.Sum+=1ll*Tag.MaxAdd*Ret.MaxCnt+1ll*Tag.OtherAdd*(Ret.Len-Ret.MaxCnt);
    Ret.Max+=Tag.MaxAdd;
    if(Ret.SecMax!=-INF) Ret.SecMax+=Tag.OtherAdd;
    return Ret;
}

tag operator*(const tag &A,const tag &B){
    tag Ret=B;
    Ret.MaxHis=max(Ret.MaxHis,Ret.MaxAdd+A.MaxHis);
    Ret.OtherHis=max(Ret.OtherHis,Ret.OtherAdd+A.OtherHis);
    Ret.MaxAdd+=A.MaxAdd;Ret.OtherAdd+=A.OtherAdd;
    return Ret;
}

struct node{
    int l,r,LeftSon,RightSon;
    Data Val;
    tag Tag;
}Node[MAXN<<2];

void Update(int Now){Node[Now].Val=Node[LSon].Val+Node[RSon].Val;}

void Mark(int Now,tag Tag){
    Node[Now].Val=Tag*Node[Now].Val;
    Node[Now].Tag=Tag*Node[Now].Tag;
    return;
}

void PushDown(int Now){
    tag Tag=Node[Now].Tag;
    if(!Tag.MaxAdd&&!Tag.OtherAdd&&!Tag.MaxHis&&!Tag.OtherHis) return;
    int Max=max(Node[LSon].Val.Max,Node[RSon].Val.Max);
    tag Other={Tag.OtherAdd,Tag.OtherAdd,Tag.OtherHis,Tag.OtherHis};
    if(Node[LSon].Val.Max==Max) Mark(LSon,Tag);else Mark(LSon,Other);
    if(Node[RSon].Val.Max==Max) Mark(RSon,Tag);else Mark(RSon,Other);
    Node[Now].Tag=Empty();
    return;
}

int Build(int l,int r){
    int Now=++cnt;
    Node[Now]={l,r,0,0,{r-l+1,-INF,-INF,-INF,0,0},Empty()};
    if(l==r){Node[Now].Val={1,Line[l],-INF,Line[l],1,Line[l]};return Now;}
    int Mid=(l+r)>>1;
    LSon=Build(l,Mid);
    RSon=Build(Mid+1,r);
    Update(Now);
    return Now;
}

void Modify(int Now,int l,int r,tag Tag){
    if(Node[Now].l>=l&&Node[Now].r<=r){Mark(Now,Tag);return;}
    else if(Node[Now].l>r||Node[Now].r<l) return;
    PushDown(Now);
    Modify(LSon,l,r,Tag);Modify(RSon,l,r,Tag);
    Update(Now);
    return;
}

void Limit(int Now,int l,int r,int Val){
    if(Node[Now].l>r||Node[Now].r<l||Node[Now].Val.Max<=Val) return;
    if(Node[Now].l>=l&&Node[Now].r<=r&&Node[Now].Val.SecMax<Val){
        Mark(Now,{Val-Node[Now].Val.Max,0,0,0});
        return;
    }
    PushDown(Now);
    Limit(LSon,l,r,Val);Limit(RSon,l,r,Val);
    Update(Now);
    return;
}

Data Query(int Now,int l,int r){
    if(Node[Now].l>=l&&Node[Now].r<=r) return Node[Now].Val;
    else if(Node[Now].l>r||Node[Now].r<l) return Null();
    PushDown(Now);
    return Query(LSon,l,r)+Query(RSon,l,r);
}

int main(){
    freopen("flutter.in","r",stdin);
    freopen("flutter.out","w",stdout);
    int c,T;
    scanf("%d%d",&c,&T);
    while(T-->0){
        scanf("%d%d",&n,&m);
        cnt=0;
        for(int i=1;i<=n;i++) scanf("%d",&Line[i]);
        Build(1,n);
        while(m-->0){
            scanf("%d%d%d",&In1,&In2,&In3);
            if(In1==1){scanf("%d",&In1);Modify(1,In2,In3,{In1,In1,In1,In1});}
            else if(In1==2){scanf("%d",&In1);Limit(1,In2,In3,In1);}
            else if(In1==3) printf("%lld\n",Query(1,In2,In3).Sum);
            else if(In1==4) printf("%d\n",Query(1,In2,In3).Max);
            else printf("%d\n",Query(1,In2,In3).HisMax);
        }
    }
    return 0;
}
