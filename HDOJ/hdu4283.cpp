#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define s(i, j) (sum[j] - sum[i - 1])

int read()
{
    int ret = 0; int rev = 0;
    char c = getchar();
    while (!isdigit(c))
        rev |= (c == '-'), c = getchar();
    while (isdigit(c))
        ret = 10 * ret + c - '0', c = getchar();
    return rev ? -ret : ret;
}

inline int min(int a, int b) {return a < b ? a : b;}

const int maxn = 100 + 5;
int f[maxn][maxn], D[maxn], sum[maxn];

int main()
{
    int T = read();
    FOR(kase, 1, T)
    {
        int n = read();
        memset(f, 0, sizeof f);
        FOR(i, 1, n) D[i] = read(), f[i][i] = 0, sum[i] = sum[i - 1] + D[i];
        FOR(i, 1, n)
            FOR(j, i + 1, n)
                f[i][j] = 0x3f3f3f3f;
        FOR(len, 2, n)
        {
            for (int i = 1, j = i + len - 1; j <= n; ++i, ++j)
            {
                for (int k = i; k <= j; ++k)
                    f[i][j] = min(f[i][j], (k - i) * D[i] + f[i + 1][k] + f[k + 1][j] + s(k + 1, j) * (k - i + 1));
            }
        }
        printf("Case #%d: %d\n", kase, f[1][n]);
    }
    return 0;
}