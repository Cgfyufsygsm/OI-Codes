#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

const int maxn = 3e5 + 5;
int n, m, p, fact[maxn];

int qpow(int base, int p, int mod)
{
    int ret = 1;
    for (; p; p >>= 1, base = 1ll * base * base % mod)
        if (p & 1) ret = 1ll * ret * base % mod;
    return ret;
}

int C(int n, int m)
{
    if (m > n) return 0;
    return 1ll * fact[n] * qpow(1ll * fact[m] * fact[n - m] % p, p - 2, p) % p;
}

int lucas(int n, int m)
{
    if (!m) return 1;
    return 1ll * lucas(n / p, m / p) * C(n % p, m % p) % p;
}

int main()
{
    int T = read();
    while (T--)
    {
        m = read(), n = read() + m, p = read();
        fact[0] = 1;
        FOR(i, 1, 3e5) fact[i] = 1ll * i * fact[i - 1] % p;
        printf("%d\n", lucas(n, m));
    }
    return 0;
}