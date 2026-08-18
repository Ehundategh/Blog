#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 100010
using namespace std;

int c,T,n,Cnt,Pos[MAXN];
char s[MAXN],t[MAXN];

void Solve(){
    scanf("%d%s%s",&n,s+1,t+1);
    Cnt=0;
    for(int i=1;i<=n;i++){
        if(s[i]!=t[i]) Pos[++Cnt]=i-1;
    }
    if(!Cnt){printf("0\n");return;}
    int Move=n;
    for(int i=0;i<=Cnt;i++){
        int Clockwise=i?Pos[i]:0;
        int Counter=i==Cnt?0:n-Pos[i+1];
        Move=min(Move,min(Clockwise*2+Counter,Clockwise+Counter*2));
    }
    printf("%d\n",Cnt+Move);
    return;
}

int main(){
    scanf("%d%d",&c,&T);
    while(T-->0) Solve();
    return 0;
}
