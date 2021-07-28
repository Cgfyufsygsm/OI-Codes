#include <cstdio>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 255;
int n, f[maxn][maxn], a[maxn], sum[maxn], s[maxn][maxn];

il int cost(int i, int j, int k) {return sum[j] - sum[i - 1] - a[k];}
il bool to_min(int &a, int b) {return b < a ? (a = b, 1) : 0;}

int main() {
    while (~scanf("%d", &n)) {
        FOR(i, 1, n) scanf("%d", a + i), sum[i] = sum[i - 1] + a[i], s[i][i] = i;
        memset(f, 0x3f, sizeof f);
        FOR(i, 1, n) f[i + 1][i] = f[i][i - 1] = 0, f[i][i] = 0;
        FOR(len, 2, n)
            for (int i = 1, j = i + len - 1; j <= n; ++i, ++j)
                for (int k = s[i][j - 1]; k <= s[i + 1][j]; ++k)
                    if (to_min(f[i][j], f[i][k - 1] + f[k + 1][j] + cost(i, j, k)))
                        s[i][j] = k;
        printf("%d\n", f[1][n]);
    }
    return 0;
}