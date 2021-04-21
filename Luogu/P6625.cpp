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

typedef long long ll;
const int maxn = 1e5 + 5;
int n;
ll a[maxn];

int main()
{
    n = read();
    FOR(i, 1, n) a[i] = read();
    ll ans = 0, cur = 0;
    int chose = 0;
    FOR(i, 1, n)
    {
        cur += a[i], ++chose;
        if (cur >= 0 && chose >= 2)
            ans += cur, chose = 1;
    }
    printf("%lld\n", ans);
    return 0;
}