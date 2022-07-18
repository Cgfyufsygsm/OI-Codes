#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int lcm = 720720;

int main() {
    int n, m; cin >> n >> m;
    FOR(i, 1, n) {
        FOR(j, 1, m) {
            int x; cin >> x;
            if ((i + j) & 1) cout << lcm << ' ';
            else cout << lcm - x * x * x * x << ' ';
        }
        cout << endl;
    }
    return 0;
}