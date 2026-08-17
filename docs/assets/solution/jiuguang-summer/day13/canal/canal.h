#ifndef CANAL_H
#define CANAL_H

#include <vector>

void Init(int c,int T);
void Locate(int c,int n,std::vector<int> w,std::vector<int> v);
long long Travel(std::vector<int> choice);
void Answer(int x,int a,int y,int b);

#endif
