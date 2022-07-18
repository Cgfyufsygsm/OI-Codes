#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using pii = pair<int, int>;
using ll = long long;
const int maxn = 505, maxk = 22;
int n, m, k;
const int fx[] = {1, -1, 0, 0};
const int fy[] = {0, 0, 1, -1};
ll tr[maxn][maxn][4];
ll f[maxn][maxn][maxk];
template<typename T> il T chkmin(T &a, const T &b) {return a = (b < a ? b : a);}

int main() {
    cin >> n >> m >> k;
    if (k & 1) {
        FOR(i, 1, n) {
            FOR(j, 1, m) cout << -1 << ' ';
            cout << endl;
        }
        return 0;
    }
    FOR(i, 1, n) FOR(j, 1, m - 1) {
        ll v; cin >> v;// (i,j) -> (i,j+1)
        tr[i][j][2] = tr[i][j + 1][3] = v;
    }
    FOR(i, 1, n - 1) FOR(j, 1, m) {
        ll v; cin >> v;// (i,j) -> (i + 1, j)
        tr[i][j][0] = tr[i + 1][j][1] = v;
    }
    auto check = [](const int &x, const int &y) {
        return x >= 1 && x <= n && y >= 1 && y <= m;
    };
    memset(f, 0x3f, sizeof f);
    FOR(i, 1, n) FOR(j, 1, m) f[i][j][0] = 0;
    FOR(s, 0, k / 2 - 1) FOR(i, 1, n) FOR(j, 1, m) FOR(t, 0, 3) {
        int tx = i + fx[t], ty = j + fy[t];
        if (!check(tx, ty)) continue;
        chkmin(f[tx][ty][s + 1], f[i][j][s] + tr[i][j][t]);
    }
    FOR(i, 1, n) {
        FOR(j, 1, m) cout << f[i][j][k / 2] * 2 << ' ';
        cout << endl;
    }
    return 0;
}