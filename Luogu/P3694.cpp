#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 1e5 + 5, maxm = 21;

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

int a[maxn], sum[maxn][maxm], f[1 << maxm], num[maxm], n, m;

inline int min(int a, int b) {return a < b ? a : b;}

int main()
{
    n = read(), m = read();
    FOR(i, 1, n)
    {
        a[i] = read();
        FOR(j, 1, m) sum[i][j] = sum[i - 1][j];
        ++num[a[i]], ++sum[i][a[i]];
    }
    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    FOR(S, 1, (1 << m) - 1)
    {
        int len = 0;
        FOR(j, 1, m) if (S & (1 << (j - 1))) len += num[j];
        FOR(j, 1, m)
            if (S & (1 << (j - 1)))
                f[S] = min(f[S], f[S ^ (1 << (j - 1))] + num[j] - sum[len][j] + sum[len - num[j]][j]);
    }
    printf("%d\n", f[(1 << m) - 1]);
    return 0;
}