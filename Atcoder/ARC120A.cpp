#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 2e5 + 5;

typedef long long ll;

ll read()
{
    ll s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

ll n, a[maxn], s[maxn];

inline ll max(ll a, ll b) {return a > b ? a : b;}

int main()
{
    n = read();
    FOR(i, 1, n) a[i] = read();
    int maxa = 0;
    FOR(i, 1, n)
        s[i] = s[i - 1] + a[i];
    FOR(i, 1, n)
        s[i] = s[i - 1] + s[i];
    FOR(i, 1, n)
    {
        maxa = max(a[i], maxa);
        printf("%lld\n", s[i] + 1ll * i * maxa);
    }
    return 0;
}