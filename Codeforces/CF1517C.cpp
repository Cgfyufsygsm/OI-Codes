#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 505;
int n, a[maxn], ans[maxn][maxn];

int main() {
    cin >> n;
    FOR(i, 1, n) {
        cin >> a[i];
        FOR(j, 1, n) ans[i][j] = 0;
    }
    FOR(i, 1, n) {
        ans[i][i] = a[i];
        int cnt = 1, x = i, y = i;
        while (cnt < a[i]) {
            if (y > 1 && !ans[x][y - 1]) ans[x][--y] = a[i];
            else if (x <= n && !ans[x + 1][y]) ans[++x][y] = a[i];
            ++cnt;
        }
    }
    FOR(i, 1, n) {
        FOR(j, 1, i) cout << ans[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}