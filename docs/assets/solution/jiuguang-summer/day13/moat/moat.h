#ifndef MOAT_H
#define MOAT_H

#include <vector>

void Init(int c,int T);
void Play(int c,int n,int b,std::vector<int> parent);
long long Scout(int u);
long long Clean(int u);

#endif
