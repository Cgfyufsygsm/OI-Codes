#include <cstdio>
#include <cctype>
#define int long long
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

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

inline int min(int a, int b) {return a < b ? a : b;}

const int p = 2333;
int C[p + 5][p + 5], f[p + 5][p + 5];

int lucas(int n, int m)
{
    if (!m) return 1;
    return C[n % p][m % p] * lucas(n / p, m / p) % p;
}

int F(int n, int k)
{
    if (k < 0) return 0;
    if (!k || !n) return 1;
    if (n < p && k < p) return f[n][k];
    return (lucas(n / p, k / p) * f[n % p][k % p] % p + f[n % p][p - 1] * F(n / p, k / p - 1) % p) % p;
}

signed main()
{
    int t = read();
    C[0][0] = 1;
    FOR(i, 1, p)
    {
        C[i][0] = C[i][i] = 1;
        FOR(j, 1, i - 1)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % p;
    }
    f[0][0] = 1;
    FOR(i, 1, p)
        f[i][0] = 1;
    FOR(i, 0, p)
        FOR(j, 1, p)
            f[i][j] = (C[i][j] + f[i][j - 1]) % p;
    while (t--)
    {
        int n = read(), k = read();
        printf("%lld\n", F(n, k));
    }
    return 0;
}