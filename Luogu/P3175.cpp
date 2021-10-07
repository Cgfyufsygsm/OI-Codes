#include <cstdio>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

const int maxn = 1 << 20;
using db = double;
db p[maxn];
int n, cnt[maxn];

int main() {
    scanf("%d", &n); n = (1 << n);
    FOR(i, 0, n - 1) scanf("%lf", p + i);
    for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
        for (int i = 0; i < n; i += o)
            for (int j = 0; j < k; ++j)
                p[i + j + k] += p[i + j];
    db ans = 0;
    FOR(i, 1, n - 1) {
        cnt[i] = cnt[i >> 1] + (i & 1);
        db tmp = 1 - p[i ^ (n - 1)];
        if (tmp < 1e-8) return puts("INF"), 0;
        ans += ((cnt[i] & 1) ? 1 : -1) * 1.0 / tmp;
    }
    printf("%lf\n", ans);
    return 0;
}