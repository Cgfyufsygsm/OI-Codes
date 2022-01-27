#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int maxn = 5e5 + 5;
int n, m;
int t[maxn << 2], M;

int main() {
    scanf("%d %d", &n, &m);
    for (M = 1; M <= n; M <<= 1);
    FOR(i, 1, n) scanf("%d", t + M + i);
    DEC(i, M - 1, 1) t[i] = t[i << 1] + t[i << 1 | 1];
    while (m--) {
        int op, x, y; scanf("%d %d %d", &op, &x, &y);
        if (op == 1) {
            t[x += M] += y;
            for (x >>= 1; x; x >>= 1) t[x] = t[x << 1] + t[x << 1 | 1];
        } else {
            int ans = 0;
            for (int l = x + M - 1, r = y + M + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
                if (~l & 1) ans += t[l ^ 1];
                if (r & 1) ans += t[r ^ 1];
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}