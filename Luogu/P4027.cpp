#include <cstdio>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

typedef double db;
const int maxn = 1e5 + 5;

int n;
db a[maxn], b[maxn], r[maxn], c[maxn], d[maxn];
db f[maxn], K[maxn], B[maxn];

int t[maxn << 2];

il db calc(int i, int u) {return K[i] * c[u] + B[i];}
il db max(db a, db b) {return a > b ? a : b;}

#define M ((i + j) >> 1)
#define L (k << 1)
#define R (L | 1)

void insert(int i, int j, int k, int u) {
    int v = t[k];
    db resu = calc(u, M), resv = calc(v, M);
    if (i == j) {
        if (resu > resv) t[k] = u;
        return;
    }
    if (K[u] > K[v]) {
        if (resu > resv)
            insert(i, M, L, v), t[k] = u;
        else insert(M + 1, j, R, u);
    }
    else {
        if (resu > resv)
            insert(M + 1, j, R, v), t[k] = u;
        else insert(i, M, L, u);
    }
    return;
}

db query(int i, int j, int k, int u) {
    db ret = calc(t[k], u);
    if (i == j) return ret;
    if (u <= M) return max(ret, query(i, M, L, u));
    else return max(ret, query(M + 1, j, R, u));
}

int main() {
    scanf("%d %lf", &n, f + 1);
    FOR(i, 1, n) scanf("%lf %lf %lf", a + i, b + i, r + i), c[i] = a[i] / b[i], d[i] = c[i];
    std::sort(c + 1, c + n + 1);
    K[1] = (f[1] * r[1]) / (r[1] * a[1] + b[1]), B[1] = f[1] / (r[1] * a[1] + b[1]);
    insert(1, n, 1, 1);
    FOR(i, 2, n) {
        f[i] = max(f[i - 1], b[i] * query(1, n, 1, std::lower_bound(c + 1, c + n + 1, d[i]) - c));
        K[i] = f[i] * r[i] / (r[i] * a[i] + b[i]), B[i] = f[i] / (r[i] * a[i] + b[i]);
        insert(1, n, 1, i);
    }
    printf("%.3lf\n", f[n]);
    return 0;
}