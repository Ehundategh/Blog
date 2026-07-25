/*
Author:Ehundategh
Date:2026/7/21
Name:elixir.cpp
You steal,I kill.
*/
#include <cstdio>
#include <algorithm>
using namespace std;
long long n,Ans;
int main(){
    freopen("elixir.in","r",stdin);
    freopen("elixir.out","w",stdout);
    scanf("%lld",&n);
    long long Limit=n/2;
    for(long long Left=1,Right;Left<=Limit;Left=Right+1){
        long long Value=n/Left;
        Right=min(Limit,n/Value);
        Ans+=(Value-1)*(Right-Left+1);
    }
    printf("%lld\n",Ans);
    return 0;
}
