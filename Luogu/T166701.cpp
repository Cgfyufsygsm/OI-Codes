// flip
#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

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

int pow(int base, int p)
{
    int ret = 1;
    for (; p; p >>= 1)
    {
        if (p & 1)
            ret = ret * base;
        base = base * base;
    }
    return ret;
}

const int maxn = 1e7 + 9;

int n, p;

int rev[maxn];

int main()
{
    n = read(), p = read();
    int lim = pow(p, n);
    rev[0] = 0;
    FOR(i, 1, lim - 1)
        rev[i] = (rev[i / p] / p) + (i % p) * (lim / p);
    FOR(i, 0, lim - 1) printf("%d ", rev[i]);
    return 0;
}