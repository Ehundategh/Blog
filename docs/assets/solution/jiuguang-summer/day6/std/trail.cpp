#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int T;
int n,m,Line[2010][2010];
bool Tag[4010];
bool Visit[2010][2010];
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}
void DFS(int i,int j,int W) {
    if (Visit[i][j]) return;
    Visit[i][j]=1;
    if (i==1&&W!=3&&W!=2) Tag[Line[i][j]]=1;
    if (i==n&&W!=4&&W!=1) Tag[Line[i][j]]=1;
    if (j==1&&W!=1&&W!=4) Tag[Line[i][j]]=1;
    if (j==m&&W!=2&&W!=3) Tag[Line[i][j]]=1;
    if (Line[i+1][j]==Line[i][j]&&i+1<=n) DFS(i+1,j,W);
    if (Line[i-1][j]==Line[i][j]&&i-1>=1) DFS(i-1,j,W);
    if (Line[i][j+1]==Line[i][j]&&j+1<=m) DFS(i,j+1,W);
    if (Line[i][j-1]==Line[i][j]&&j-1>=1) DFS(i,j-1,W);

    if (Line[i+1][j+1]==Line[i][j]&&i+1<=n&&j+1<=m) DFS(i+1,j+1,W);
    if (Line[i-1][j+1]==Line[i][j]&&i-1>=1&&j+1<=m) DFS(i-1,j+1,W);
    if (Line[i+1][j-1]==Line[i][j]&&i+1<=n&&j-1>=1) DFS(i+1,j-1,W);
    if (Line[i-1][j-1]==Line[i][j]&&i-1>=1&&j-1>=1) DFS(i-1,j-1,W);
    return;
}
void Solve() {
    memset(Tag,0,sizeof(Tag));
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) {
        for (int j=1;j<=m;j++) {
            Line[i][j]=read();
            Visit[i][j]=0;
        }
    }
    for (int i=1;i<=n;i++) {
        if (Line[i][1]<=n+m) DFS(i,1,1);
        if (Line[i][m]<=n+m) DFS(i,m,2);
    }
    for (int i=1;i<=m;i++) {
        if (Line[1][i]<=n+m) DFS(1,i,3);
        if (Line[n][i]<=n+m) DFS(n,i,4);
    }
    for (int i=0;i<=n+m;i++) {
        if (!Tag[i]){ printf("%d\n",i); return;}
    }
}
int main() {
    scanf("%d",&T);
    while (T-->0) Solve();
    return 0;
}
