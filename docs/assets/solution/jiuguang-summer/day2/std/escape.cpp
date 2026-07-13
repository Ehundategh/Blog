#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
double A[18];
double Num[18][18],In1;

int main(){
    freopen("escape.in","r",stdin);
    freopen("escape.out","w",stdout);
    memset(Num,0,sizeof(Num));
    scanf("%d",&n);
    for (int i=1;i<=n+1;i++) {
        scanf("%lf",&A[i]);
    }
    for (int i=1;i<=n;i++) {
        for (int j=1;j<=n;j++) {
            scanf("%lf",&In1);
            Num[i][j]=-2*In1+2*A[j];
            Num[i][n+1]-=In1*In1-A[j]*A[j];
        }
        scanf("%lf",&In1);
        Num[i][n+1]+=In1-A[n+1];
    }
    for(int i=1;i<=n;i++){
        if(fabs(Num[i][i])<1e-8){
            for(int j=i+1;j<=n;j++){
                if(fabs(Num[j][i])>1e-8){
                    for(int k=1;k<=n+1;k++) swap(Num[j][k],Num[i][k]);
                    break;
                }
            }
        }
        double Temp=Num[i][i];
        for(int j=i;j<=n+1;j++) Num[i][j]/=Temp;
        for(int j=1;j<=n;j++){
            if(j==i) continue;
            double Times=Num[j][i]/Num[i][i];
            for(int k=1;k<=n+1;k++){
                Num[j][k]-=Num[i][k]*Times;
            }
        }
    }
    for (int i=1;i<=n;i++) {
        if (fabs(Num[i][n+1])<0.0005) printf("0.000 ");
        else printf("%.3lf ",Num[i][n+1]);
    }
    return 0;
}