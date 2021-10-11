#include <cstdio>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using uint = unsigned;

uint seed;
inline uint getnext() {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}

const int maxn = 2e7 + 5;
int p[maxn], tot, isp[maxn], n;
uint a[maxn];

int main() {
    scanf("%d %u", &n, &seed);
    FOR(i, 1, n) a[i] = getnext();
    FOR(i, 2, n) {
        if (!isp[i]) p[++tot] = i;
        for (int j = 1; j <= tot && i * p[j] <= n; ++j) {
            isp[i * p[j]] = 1;
            if (i % p[j] == 0) break;
        }
    }
    FOR(j, 1, tot) for (int i = 1; i * p[j] <= n; ++i) a[i * p[j]] += a[i];
    uint ans = 0;
    FOR(i, 1, n) ans ^= a[i];
    printf("%u\n", ans);
    return 0;
}