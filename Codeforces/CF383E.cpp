#include <cstdio>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int maxn = 1e4 + 5, maxs = 1 << 24 | 500;
int a[maxn], n, f[maxs];

int main() {
    scanf("%d", &n);
    FOR(i, 1, n) {
        char s[4];
        scanf("%s", s + 1);
        FOR(j, 1, 3) a[i] |= (1 << (s[j] - 'a'));
        ++f[a[i]];
    }
    FOR(j, 0, 23) FOR(i, 0, (1 << 24) - 1) if (i & (1 << j)) f[i] += f[i ^ (1 << j)];
    int ans = 0;
    FOR(S, 0, (1 << 24) - 1) {
        int res = n - f[S ^ ((1 << 24) - 1)];
        ans ^= (res * res);
    }
    printf("%d\n", ans);
    return 0;
}