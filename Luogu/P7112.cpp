#include <cstdio>
#include <cctype>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

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

const int maxn = 605;

int a[maxn][maxn], n, mod;

int main()
{
    n = read(), mod = read();
    FOR(i, 1, n)
        FOR(j, 1, n)
            a[i][j] = read();
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
    FOR(i, 1, n) ans = 1ll * ans * a[i][i] % mod;
    ans *= rev;
    printf("%d\n", (ans + mod) % mod);
    return 0;
}