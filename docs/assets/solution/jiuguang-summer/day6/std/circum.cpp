#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
const int Mod=998244353;
inline int Add(int a,int b){return a+b>=Mod?a+b-Mod:a+b;}
inline int Mul(int a,int b){return 1ll*a*b%Mod;}
inline int Del(int a,int b){return a-b<0?a-b+Mod:a-b;}
int T,n,m,p;
int Prime[2000100],cnt=0,Count[2][110];
bool Tag[20000010];
void Tackle() {
    Count[0][1%p]++;Count[1][1%p]++;
    for (int i=2;i<=m;i++) {
        Count[0][i%p]++;
        if (!Tag[i]) {
            Prime[++cnt]=i;
        }
        else Count[1][i%p]++;
        for (int j=1;j<=cnt;j++) {
            if (1ll*i*Prime[j]>m) {break;}
            Tag[i*Prime[j]]=true;
            if (i%Prime[j]==0) {break;}
        }
    }
    return;
}
struct Matrix {
    int Num[110][110];
    void Init() {
        memset(Num,0,sizeof(Num));
    }
}I,Ans1,f,g,Ans2;
Matrix operator*(const Matrix &A,const Matrix &B) {
    Matrix C;
    for(int i=1;i<=p;i++) {
        for(int j=1;j<=p;j++) {
            C.Num[i][j]=0;
            for(int k=1;k<=p;k++) {
                C.Num[i][j]=Add(C.Num[i][j],Mul(A.Num[i][k],B.Num[k][j]));
            }
        }
    }
    return C;
}
void Print(Matrix A) {
    for(int i=1;i<=p;i++) {
        for(int j=1;j<=p;j++) {
            cout<<A.Num[i][j]<<" ";
        }
        puts("");
    }
    return;
}
Matrix operator^(Matrix A,int b) {
    Matrix C;
    C=I;
    while(b) {
        if (b&1) C=C*A;
        A=A*A;
        b>>=1;
    }
    return C;
}
Matrix operator-(const Matrix &A,const Matrix &B) {
    Matrix C;
    C.Init();
    for(int i=1;i<=p;i++) {
        for(int j=1;j<=p;j++) {
            C.Num[i][j]=Del(A.Num[i][j],B.Num[i][j]);
        }
    }
    return C;
}
void Solve() {
    scanf("%d%d%d",&n,&m,&p);
    cnt=0;
    memset(Count,0,sizeof(Count));
    memset(Tag,0,(m+1)*sizeof(Tag[0]));
    I.Init();
    Ans1.Init();Ans2.Init();
    for (int i=1;i<=p;i++) I.Num[i][i]=1;
    Tackle();
    f.Init();g.Init();
    Ans1.Num[p][1]=1;Ans2.Num[p][1]=1;
    for (int i=1;i<=p;i++) {
        for (int j=1;j<=p;j++) {
            f.Num[i][j]=Count[0][(j-i+p)%p];
        }
    }
    for (int i=1;i<=p;i++) {
        for (int j=1;j<=p;j++) {
            g.Num[i][j]=Count[1][(j-i+p)%p];
        }
    }
    Matrix Ans=(f^n)*Ans1-(g^n)*Ans2;
    printf("%d\n",Ans.Num[p][1]);
}
int main() {
    scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
