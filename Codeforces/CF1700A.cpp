#include <bits/stdc++.h>
#define il inline

using namespace std;
using ll = long long;

int main() {
    int T; cin >> T;
    while (T--) {
        ll n, m; cin >> n >> m;
        cout << (1 + m) * m / 2 + m * (1 + n) * n / 2 - m << endl;
    }
    return 0;
}