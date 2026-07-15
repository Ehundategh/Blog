/*
Author:Ehundategh
Date:2026/7/14
Name:sunset.cpp
You steal,I kill.
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LSon Node[Now].LeftS
#define RSon Node[Now].RightS
#define MAXN 200010
const long long INF=1ll<<60;
using namespace std;
int Line[MAXN],n,q;
class matrix{
    long long Num[4][4];
public:
    void Init(long long a){for(int i=1;i<=3;i++) for(int j=1;j<=3;j++) Num[i][j]=a;}
    matrix(){Init(-INF);}
    matrix(long long a){Init(a);}
    matrix operator*(const matrix &t) const{
        matrix ans;
        for(int i=1;i<=3;i++){
            for(int j=1;j<=3;j++){
                for(int k=1;k<=3;k++){
                    ans.Num[i][j]=max(ans.Num[i][j],Num[i][k]+t.Num[k][j]);
                }
            }
        }
        return ans;
    }
    void Modify(int a){
        Num[1][1]=Num[1][3]=Num[2][1]=Num[2][3]=a;
        Num[2][2]=Num[3][3]=0;
    }
    long long Back() const{return max(Num[2][1],Num[2][3]);}
};
class Segment_Tree{
    int cnt=0;
    struct node{
        matrix Value;
        int LeftS,RightS;
        int Left,Right;
    }Node[MAXN<<2];
public:
    int Build(int L,int R){
        int Now=++cnt;
        Node[Now].Left=L;Node[Now].Right=R;
        if(L==R){Node[Now].Value.Modify(Line[L]);return Now;}
        int Mid=(L+R)>>1;
        LSon=Build(L,Mid);
        RSon=Build(Mid+1,R);
        Node[Now].Value=Node[LSon].Value*Node[RSon].Value;
        return Now;
    }
    void Modify(int Now,int Pos,int Value){
        if(Node[Now].Left==Node[Now].Right){Node[Now].Value.Modify(Value);return;}
        else{
            if(Pos<=Node[LSon].Right) Modify(LSon,Pos,Value);
            else Modify(RSon,Pos,Value);
            Node[Now].Value=Node[LSon].Value*Node[RSon].Value;
        }
    }
    matrix Query(int Now,int Left,int Right){
        if( Node[Now].Left>=Left && Right>=Node[Now].Right )return Node[Now].Value;
        else{
            if(Node[LSon].Right>=Left&&Node[RSon].Left<=Right) return Query(LSon,Left,Right)*Query(RSon,Left,Right);
            else if(Node[LSon].Right>=Left) return Query(LSon,Left,Right);
            else return Query(RSon,Left,Right);
        }
    }
}T;
int main(){
    freopen("sunset.in","r",stdin);
    freopen("sunset.out","w",stdout);
    char Option[4];
    int In1,In2;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",&Line[i]);
    }
    T.Build(1,n);
    while(q-->0){
        scanf("%s%d%d",Option+1,&In1,&In2);
        if(Option[1]=='Q') printf("%lld\n",T.Query(1,In1,In2).Back());
        else T.Modify(1,In1,In2);
    }
    return 0;
}