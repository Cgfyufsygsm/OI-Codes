#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 45;
int n, m, a[maxn][maxn];

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n >> m;
        int x, y, maxv = -2e9;
        FOR(i, 1, n) FOR(j, 1, m) {
            cin >> a[i][j];
            if (a[i][j] > maxv) maxv = a[i][j], x = i, y = j;
        }
        cout << max(x, n - x + 1) * max(y, m - y + 1) << endl;
    }
    return 0;
}