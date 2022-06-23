#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 1005;
bitset<maxn> f[2][maxn];
int n, m, a[maxn][maxn];

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n >> m;
        FOR(i, 1, n) FOR(j, 1, m) cin >> a[i][j];
        FOR(i, 0, 1) FOR(j, 1, m) f[i][j].reset();
        if ((n + m) % 2 == 0) cout << "No" << '\n';
        else {
            FOR(i, 1, n) FOR(j, 1, m) {
                if (i == 1 && j == 1) f[i & 1][j][a[i][j] == 1] = 1;
                else {
                    if (a[i][j] == 1) f[i & 1][j] = ((f[(i - 1) & 1][j] | f[i & 1][j - 1]) << 1);
                    else f[i & 1][j] = (f[(i - 1) & 1][j] | f[i & 1][j - 1]);
                }
            }
            cout << (f[n & 1][m].test((n + m - 1) / 2) ? "Yes" : "No") << '\n';
        }
    }
    return 0;
}