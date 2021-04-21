#include <cstdio>
#include <cctype>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 255, mod = 1e4 + 7;
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

int n;
int a[maxn][maxn];

int main()
{
    n = read();
    int m = read();
    while (m--)
    {
        int u = read(), v = read();
        ++a[u][u];
        a[v][u] = (a[v][u] - 1 + mod) % mod;
    }
    int ans = 1, rev = 1;
    FOR(i, 2, n)
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
    FOR(i, 2, n) ans = 1ll * ans * a[i][i] % mod;
    ans *= rev;
    printf("%d\n", (ans + mod) % mod);
    return 0;
}