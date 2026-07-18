#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN 300010
int T,n;
long long Need[2][MAXN],Line[MAXN],Ans=0x7fffffffffffffff,PreSum=0,SuffSum=0;
class Container{
public:
    int Head=1,Tail=0,Pos[MAXN];;
    long long Sum=0;
    void Init(){Head=1,Tail=0;}
    void Push_Back(int a){Pos[++Tail]=a;}
    void Pop_Back(){Tail--;}
    int Back(){return Pos[Tail];}
    bool Empty(){return Head>=Tail;}
}Q;
long long Calc(long long Height,long long Length){//计算元素贡献
    Length=min(Length,Height);
    return 1ll*(Height+Height-Length+1)*Length/2;
}
void Ehundategh_Clear(){//清空
    PreSum=SuffSum=0;
    Q.Head=1;Q.Tail=0;
    Q.Sum=0;
    Q.Push_Back(0);
    Ans=0x7fffffffffffffff;
}
int main(){
    freopen("solwind.in","r",stdin);
    freopen("solwind.out","w",stdout);
    scanf("%d",&T);
    while(T-->0){
        scanf("%d",&n);
        Ehundategh_Clear();
        for(int i=1;i<=n;i++) scanf("%lld",&Line[i]);
        for(int i=1;i<=n;i++){
            PreSum+=Line[i];
            while(i-Q.Back()>Line[i]-Line[Q.Back()]&&!Q.Empty()){
                Q.Sum-=Calc(Line[Q.Back()],(long long)(Q.Back()-Q.Pos[Q.Tail-1]));
                Q.Pop_Back();
            }
            Q.Push_Back(i);
            Q.Sum+=Calc(Line[Q.Back()],(long long)(Q.Back()-Q.Pos[Q.Tail-1]));
            Need[0][i]=PreSum-Q.Sum;
        }
        Q.Head=1;Q.Tail=0;
        Q.Sum=0;
        Line[n+1]=0;
        Q.Push_Back(n+1);
        for(int i=n;i>=1;i--){
            SuffSum+=Line[i];
            while(Q.Back()-i>Line[i]-Line[Q.Back()]&&!Q.Empty()){
                Q.Sum-=Calc(Line[Q.Back()],(long long)(Q.Pos[Q.Tail-1]-Q.Back()));
                Q.Pop_Back();
            }
            Q.Push_Back(i);
            Q.Sum+=Calc(Line[Q.Back()],(long long)(Q.Pos[Q.Tail-1]-Q.Back()));
            Need[1][i]=SuffSum-Q.Sum;
        }
        for(int i=1;i<=n;i++){
            if(Need[0][i]+Need[1][i]+Line[i]<Ans) Ans=Need[0][i]+Need[1][i]+Line[i];
        }
        printf("%lld\n",Ans);
    }
    return 0;
}