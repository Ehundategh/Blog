/*
Author:Ehundategh
Date:2026/6/18
Name:F.cpp
You steal,I kill.
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LSon Node[Now].LeftSon
#define RSon Node[Now].RightSon
using namespace std;

int T,n,m,Line[500010],cnt=0;

struct node {
    int l,r;
    int LeftSon,RightSon;
    int Max,Tag,Add;
}Node[4000010];

void Update(int Now) {
    Node[Now].Max=max(Node[LSon].Max,Node[RSon].Max);return;
}

void PushDown(int Now) {
    if (Node[Now].Tag==-1) return;
    Node[LSon].Max=max(Node[Now].Tag,Node[LSon].Max);
    Node[RSon].Max=max(Node[Now].Tag,Node[RSon].Max);
    Node[LSon].Tag=max(Node[LSon].Tag,Node[Now].Tag);
    Node[RSon].Tag=max(Node[RSon].Tag,Node[Now].Tag);
    Node[Now].Tag=-1;return;
}

inline int Build(int l,int r) {
    int Now=++cnt;
    Node[Now]={l,r,0,0,-0x3f3f3f3f,-1,0};
    if (l==r) return Now;
    int Mid=(l+r)>>1;
    LSon=Build(l,Mid);RSon=Build(Mid+1,r);Update(Now);
    return Now;
}

inline void Modify(int Now,int l,int r,int Val) {
    if (l>r) return;
    if (Node[Now].l>r||Node[Now].r<l) return;
    else if (Node[Now].l>=l&&Node[Now].r<=r) Node[Now].Tag=max(Node[Now].Tag,Val),Node[Now].Max=max(Node[Now].Max,Val);
    else {
        PushDown(Now);
        Modify(LSon,l,r,Val);Modify(RSon,l,r,Val);Update(Now);
        return;
    }
}

inline int Add(int Now,int Pos) {
    int Ret;
    if (Node[Now].l==Node[Now].r) {Node[Now].Max++;return Node[Now].Max;}
    else {
        PushDown(Now);
        if (Node[LSon].r>=Pos) Ret=Add(LSon,Pos);
        else Ret=Add(RSon,Pos);
        Update(Now);
    }
    return Ret;
}

inline int Query(int Now,int l,int r) {
    if (l>r) return -0x3f3f3f3f;
    if (Node[Now].l>r||Node[Now].r<l) return -0x3f3f3f3f;
    else if (Node[Now].l>=l&&Node[Now].r<=r) return Node[Now].Max;
    else {
        PushDown(Now);Update(Now);
        return max(Query(LSon,l,r),Query(RSon,l,r));
    }
}

void Solve() {
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) {
        scanf("%d",&Line[i]);
    }
    int nl=n;cnt=0;
    Build(1,n+m+10);
    Modify(1,nl,nl,(Line[1]==1));
    int Best=(Line[1]==1);
    for (int i=2;i<=n;i++) {
        int Last=Query(1,nl+m-1,nl+m-1);
        nl--;
        Modify(1,nl,nl,Best);
        Modify(1,nl+1,nl+m-1,Last);
        int NewVal=Add(1,nl-1+Line[i]);
        Best=max(Best,NewVal);
    }
    printf("%d\n",n-Query(1,nl+m-1,nl+m-1));
    return ;
}

int main() {
    int c;
    scanf("%d%d",&c,&T);
    while (T-->0) Solve();
    return 0;
}
