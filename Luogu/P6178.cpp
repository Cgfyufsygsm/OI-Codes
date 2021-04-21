#include <cstdio>
#include <cctype>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 305, mod = 1e9 + 7;
using std::swap;

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

int n, m, t;
int a[maxn][maxn];

int main()
{
    n = read(), m = read(), t = read();
    --n;
    while (m--)
    {
        int u = read() - 1, v = read() - 1, w = read();
        if (!t)
        {
            a[u][v] = (a[u][v] - w + mod) % mod;
            a[v][u] = (a[v][u] - w + mod) % mod;
            a[u][u] = (a[u][u] + w) % mod, a[v][v] = (a[v][v] + w) % mod;
        }
        else
        {
            a[u][v] = (a[u][v] - w + mod) % mod;
            a[v][v] = (a[v][v] + w) % mod;
        }
    }
    int ans = 1, rev = 1;
    FOR(i, 1, n)
        FOR(j, i + 1, n)
        {
            while (a[i][i])
            {
                int div = a[j][i] / a[i][i];
                FOR(k, i, n)
                    a[j][k] = (a[j][k] - 1ll * div * a[i][k] % mod + mod) % mod;
                swap(a[i], a[j]), rev = -rev;
            }
            swap(a[i], a[j]), rev = -rev;
        }
    FOR(i, 1, n)
        ans = 1ll * ans * a[i][i] % mod;
    printf("%d\n", (rev * ans + mod) % mod);
    return 0;
}