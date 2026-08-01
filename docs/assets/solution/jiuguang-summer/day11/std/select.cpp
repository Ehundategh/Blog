#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, T;
    if (!(cin >> c >> T)) return 0;
    while (T--) {
        int n;
        long long h;
        cin >> n >> h;
        priority_queue<long long, vector<long long>, greater<long long> > Heap;
        long long Energy = h;
        for (int i = 1; i <= n; ++i) {
            long long Value;
            cin >> Value;
            Energy += Value;
            Heap.push(Value);
            if (Energy < 0) {
                Energy -= Heap.top();
                Heap.pop();
            }
        }
        cout << Heap.size() << '\n';
    }
    return 0;
}
