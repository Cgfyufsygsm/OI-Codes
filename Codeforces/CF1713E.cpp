#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

const int maxn = 1e3 + 5;
int n, a[maxn][maxn], b[maxn][maxn];
int fa[maxn];

int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}
il void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    fa[x] = y;
    return;
}

il bool antagonize(int x, int y) {
    if (find(x) == find(y) || find(x + n) == find(y + n)) return false;
    merge(x, y + n), merge(y, x + n);
    return true;
}

il bool ally(int x, int y) {
    if (find(x) == find(y + n) || find(x + n) == find(y)) return false;
    merge(x, y), merge(x + n, y + n);
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> n;
        FOR(i, 1, n) FOR(j, 1, n) cin >> a[i][j];
        FOR(i, 1, n << 1) fa[i] = i;
        FOR(i, 1, n) FOR(j, i, n) {
            bool flg = 0;
            if (a[i][j] < a[j][i]) if (!ally(i, j)) flg = 1;
            if (a[i][j] > a[j][i]) if (antagonize(i, j)) flg = 1;
            if (!flg) b[i][j] = a[i][j], b[j][i] = a[j][i];
            else b[i][j] = a[j][i], b[j][i] = a[i][j];
        }
        FOR(i, 1, n) {
            FOR(j, 1, n) cout << b[i][j] << ' ';
            cout << '\n';
        }
    }
    return 0;
}