#include <cstdio>
#include <cctype>
#include <algorithm>
#include <functional>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

const int mod = 1e9 + 7, maxn = 1007;

int a[maxn], c[maxn][maxn], n, k;

int main()
{
    int T = read();
    FOR(i, 1, maxn - 4)
        c[i][0] = c[i][i] = 1;
    FOR(i, 2, maxn - 4)
        FOR(j, 1, i - 1)
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
    while (T--)
    {
        n = read(), k = read();
        FOR(i, 1, n)
            a[i] = read();
        std::sort(a + 1, a + n + 1, std::greater<int>());
        int nn = 0, mm = 0;
        for (int i = k; a[i] == a[k]; --i)
            ++nn, ++mm;
        for (int i = k + 1; a[i] == a[k] && i <= n; ++i)
            ++nn;
        printf("%d\n", c[nn][mm]);
    }
    return 0;
}