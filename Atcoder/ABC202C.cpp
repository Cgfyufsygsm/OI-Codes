#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 1e5 + 5;

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

int a[maxn], b[maxn], c[maxn], n;
int visa[maxn], visc[maxn];

int main()
{
    n = read();
    FOR(i, 1, n) ++visa[a[i] = read()];
    FOR(i, 1, n) b[i] = read();
    FOR(i, 1, n) ++visc[c[i] = read()];
    long long ans = 0;
    FOR(i, 1, n)
        ans += 1ll * visa[b[i]] * visc[i];
    printf("%lld\n", ans);
    return 0;
}