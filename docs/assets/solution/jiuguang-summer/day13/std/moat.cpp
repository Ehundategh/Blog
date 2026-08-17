/*
Author:Ehundategh
Date:2026/8/13
Name:moat.cpp
You steal,I kill.
*/
#include "moat.h"
#include <vector>
using namespace std;

void Init(int c,int T){return;}

void Play(int c,int n,int b,vector <int> parent){
    vector <vector <int> > Son(n+1);
    vector <int> Size(n+1,1),Cleaned(n+1,0),Order;
    Order.push_back(1);
    for(int i=2;i<=n;i++) Son[parent[i]].push_back(i),Order.push_back(i);
    for(int i=n-1;i>0;i--) Size[parent[Order[i]]]+=Size[Order[i]];
    long long Total=Scout(1);
    for(int Round=0;Round<b;Round++){
        long long Current=Total;
        int Remain=n-Round,Now=1;
        while(true){
            vector <long long> Sum(Son[Now].size());
            long long ChildSum=0;
            for(int i=0;i<(int)Son[Now].size();i++) Sum[i]=Scout(Son[Now][i]),ChildSum+=Sum[i];
            long long Own=Current-ChildSum;
            if(Own*Remain>=Total) break;
            int Next=0,NextPos=-1;
            for(int i=0;i<(int)Son[Now].size();i++){
                int To=Son[Now][i],Count=Size[To]-Cleaned[To];
                if(Count&&Sum[i]*Remain>=Total*Count){Next=To;NextPos=i;break;}
            }
            Now=Next;Current=Sum[NextPos];
        }
        Total-=Clean(Now);
        for(int To=Now;To;To=parent[To]) Cleaned[To]++;
    }
    return ;
}
