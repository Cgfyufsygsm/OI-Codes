#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
template<typename T> il T chkmax(T &a, const T &b) {return a = (b > a ? b : a);}

const int maxn = 3e5 + 5;
const int LG = 31;
int t[maxn * 60], ch[maxn * 60][2], tot = 1;
int f[maxn * 60][2][2], g[maxn], n, a[maxn];

void insert(int u, int j, int x, int a, int v) {
    if (j == -1) return;
    int c = ((x ^ a) >> j) & 1;
    if (!ch[u][c]) ch[u][c] = ++tot;
    insert(ch[u][c], j - 1, x, a, v);
    chkmax(f[u][(x >> j) & 1][(a >> j) & 1], v);
    return;
}

int query(int u, int j, int x, int v) {
    if (!u || j < 0) return 0;
    int c = ((x ^ v) >> j) & 1;
    if (c) {
        int d = (x >> j) & 1;
        return max(f[u][d][d], query(ch[u][1], j - 1, x, v));
    } else {
        int d = ((x >> j) & 1) ^ 1;
        return max(f[u][d][d ^ 1], query(ch[u][0], j - 1, x, v));
    }
}

void solve() {
    FOR(i, 1, tot) {
        t[i] = 0;
        FOR(a, 0, 1) {
            ch[i][a] = 0;
            FOR(b, 0, 1) f[i][a][b] = 0;
        }
    }
    tot = 1;
    cin >> n;
    FOR(i, 0, n - 1) cin >> a[i];
    int ans = 1;
    g[0] = 1, insert(1, LG - 1, 0, a[0], g[0]);
    FOR(i, 1, n - 1) {
        g[i] = query(1, LG - 1, i, a[i]) + 1;
        insert(1, LG - 1, i, a[i], g[i]);
        chkmax(ans, g[i]);
    }
    cout << ans << endl;
    return;
}

int main() {
    int T; cin >> T;
    while (T--) solve();
    return 0;
}