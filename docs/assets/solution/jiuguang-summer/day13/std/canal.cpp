/*
Author:Ehundategh
Date:2026/8/13
Name:canal.cpp
You steal,I kill.
*/
#include "canal.h"
#include <vector>
using namespace std;

void Init(int c,int T){return;}

long long Calc(const vector <int> &Choice,const vector <int> &w,const vector <int> &v){
    long long Ret=0;
    for(int i=1;i<(int)Choice.size();i++) Ret+=Choice[i]?v[i]:w[i];
    return Ret;
}

bool Judge(vector <int> &Choice,const vector <int> &w,const vector <int> &v){return Travel(Choice)<Calc(Choice,w,v);}

int Find(vector <int> &Pos,vector <int> &Choice,const vector <int> &w,const vector <int> &v){
    while(Pos.size()>1){
        int Mid=Pos.size()>>1;
        for(int i=0;i<Mid;i++) Choice[Pos[i]]^=1;
        bool Has=!Judge(Choice,w,v);
        for(int i=0;i<Mid;i++) Choice[Pos[i]]^=1;
        if(Has) Pos.erase(Pos.begin()+Mid,Pos.end());
        else Pos.erase(Pos.begin(),Pos.begin()+Mid);
    }
    return Pos[0];
}

void Locate(int c,int n,vector <int> w,vector <int> v){
    vector <int> Choice(n+1,0);
    bool Found=Judge(Choice,w,v);
    if(!Found){
        for(int i=1;i<=n;i++) Choice[i]=1;
        Found=Judge(Choice,w,v);
    }
    for(int Bit=0;!Found&&(1<<Bit)<=n;Bit++){
        for(int i=1;i<=n;i++) Choice[i]=(i>>Bit)&1;
        Found=Judge(Choice,w,v);
        if(!Found){
            for(int i=1;i<=n;i++) Choice[i]^=1;
            Found=Judge(Choice,w,v);
        }
    }
    vector <int> Pos;
    for(int i=1;i<=n;i++) Pos.push_back(i);
    int x=Find(Pos,Choice,w,v),a=Choice[x];
    Pos.clear();
    for(int i=1;i<=n;i++) if(i!=x) Pos.push_back(i);
    int y=Find(Pos,Choice,w,v),b=Choice[y];
    Answer(x,a,y,b);
    return ;
}
