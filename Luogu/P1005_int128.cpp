#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

int n, m;
__int128_t a[100][100], f[100][100];

template <typename T>
T max(T a, T b)
{
    return a > b ? a : b;
}

inline int read()
{
    char c = getchar();
    int s = 0;
    bool x = 0;
    while (!isdigit(c))
        x = x | (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

inline void print(__int128_t x)
{
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
    return;
}

int main()
{
    n = read(), m = read();
    FOR(i, 1, n)
        FOR(j, 1, m)
            a[i][j] = read();
    __int128_t ans = 0;
    FOR(k, 1, n)
    {
        memset(f, 0, sizeof f);
        DEC(len, m - 1, 1)
        {
            __int128_t cnt = m - len;
            for (int i = 1, j = i + len - 1; j <= m; ++i, ++j)
            {
                if (i > 1)
                    f[i][j] = max(f[i][j], f[i - 1][j] + (a[k][i - 1] << cnt));
                if (j < m)
                    f[i][j] = max(f[i][j], f[i][j + 1] + (a[k][j + 1] << cnt));
            }
        }
        __int128_t tmp = 0;
        FOR(i, 1, m)
            tmp = max(tmp, f[i][i] + (a[k][i] << m));
        ans += tmp;
    }
    print(ans);
    return 0;
}