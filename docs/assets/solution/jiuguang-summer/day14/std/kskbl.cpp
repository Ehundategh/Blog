#include <cstdio>
#include <cstring>
#define MAXN 500010
using namespace std;
char S[MAXN];
int Right[MAXN],Left[MAXN];
int c,T,n;
void Solve(){
    scanf("%s",S+1);n=strlen(S+1);
    Left[1]=1;
    for(int i=2;i<=n;i++) Left[i]=S[i]==S[i-1]?Left[i-1]:i;
    Right[n]=n;
    for(int i=n-1;i>=1;i--) Right[i]=S[i]==S[i+1]?Right[i+1]:i;
    int l=1,r=n;
    while(l<=r){
        if(S[l]!=S[r]||r-l<2){
            if(S[l]<S[r]) putchar(S[l++]);
            else putchar(S[r--]);
            continue;
        }
        int LLen=(Right[l]<r?Right[l]:r)-l+1;
        int RLen=r-(Left[r]>l?Left[r]:l)+1;
        if(LLen==r-l+1){
            int Time=LLen/2+1;
            while(Time--) putchar(S[l]);
            break;
        }
        int Time;char Value=S[l];
        if(S[l+LLen]>S[l]&&S[r-RLen]>S[r]){
            Time=LLen+RLen;l+=LLen;r-=RLen;
        }
        else if(S[l+LLen]<S[l]&&S[r-RLen]<S[r]){
            Time=LLen<RLen?LLen:RLen;l+=Time;r-=Time;
        }
        else if(S[l+LLen]<S[r-RLen]){
            Time=LLen;l+=Time;
        }
        else{
            Time=RLen;r-=Time;
        }
        while(Time--) putchar(Value);
    }
    putchar('\n');
}
int main(){
    scanf("%d%d",&c,&T);
    while(T--) Solve();
    return 0;
}
