/*
Author:Ehundategh
Date:2026/7/30
Name:locate.cpp
You steal,I kill.
*/
#include "locate.h"
using namespace std;

void Init(int c,int T){
    return;
}

int Locate(int c,int n){
    int Second=Query(1,n);
    bool Left;
    if(Second==1) Left=false;
    else if(Second==n) Left=true;
    else Left=(Query(1,Second)==Second);
    if(Left){
        int l=1,r=Second-1;
        while(l<r){
            int Mid=(l+r+1)>>1;
            if(Query(Mid,Second)==Second) l=Mid;
            else r=Mid-1;
        }
        return l;
    }
    int l=Second+1,r=n;
    while(l<r){
        int Mid=(l+r)>>1;
        if(Query(Second,Mid)==Second) r=Mid;
        else l=Mid+1;
    }
    return l;
}
