#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 1e6 + 5;

typedef long long ll;

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

int p[maxn], flg[maxn], cntp;
ll g[maxn];

int main()
{
    g[1] = 1;
    FOR(i, 2, maxn - 3)
    {
        if (!flg[i]) p[++cntp] = i, g[i] = 1ll * (i - 1) * i + 1;
        for (int j = 1; j <= cntp && i * p[j] <= maxn - 3; ++j)
        {
            flg[i * p[j]] = 1;
            if (i % p[j] == 0)
            {
                g[i * p[j]] = g[i] + (g[i] - g[i / p[j]]) * p[j] * p[j];
                break;
            }
            g[i * p[j]] = g[i] * g[p[j]];
        }
    }
    int T = read();
    while (T--)
    {
        int n = read();
        printf("%lld\n", (g[n] + 1) * n / 2);
    }
    return 0;
}