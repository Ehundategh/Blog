/*
- @Author: Ehundategh
- @Date: 2023-10-23 11:49:08
- @FilePath: \Code\CSP-S\lock.cpp
- @Description: You Steal,I kill
 */
#include <cstdio>
#include <cstring>
#define MAXN 10
using namespace std;
int n,Ans=0;
int Condition[MAXN][7];
bool Try(int a,int b,int c,int d,int e){
	for(int i=1;i<=n;i++){
		int Da=0,Db=0,Dc=0,Dd=0,De=0,Times=0;
		Da=(a-Condition[i][1]+10)%10;
		if(Da) Times++;
		Db=(b-Condition[i][2]+10)%10;
		if(Db) Times++;
		Dc=(c-Condition[i][3]+10)%10;
		if(Dc) Times++;
		Dd=(d-Condition[i][4]+10)%10;
		if(Dd) Times++;
		De=(e-Condition[i][5]+10)%10;
		if(De) Times++;
		if(!Times) return false;
		if(Times==1) continue;
		if(Times==2){
			if((Da==Db&&Da!=0)||(Db==Dc&&Db!=0)||(Dc==Dd&&Dc!=0)||(Dd==De&&Dd!=0)) continue;
			else return false;
		}
		if(Times>2) return false;
	}
	return true;
}
void Solve(){
	scanf("%d",&n);
	Ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=5;j++){
			scanf("%d",&Condition[i][j]);
		}
	}
	if(n==1) printf("81\n");
	else{
		for(int i=0;i<=9;i++){
			for(int j=0;j<=9;j++){
				for(int k=0;k<=9;k++){
					for(int r=0;r<=9;r++){
						for(int o=0;o<=9;o++){
							if(Try(i,j,k,r,o)){
								Ans++;
							}
						}
					}
				}
			}
		}
		printf("%d\n",Ans);
	}
}
int main(){
	int c,T;
	scanf("%d%d",&c,&T);
	while(T-->0) Solve();
	return 0;
}
