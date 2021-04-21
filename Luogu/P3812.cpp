#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxk = 55;
typedef long long ll;

ll read()
{
    ll s = 0; int x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

ll n, a[maxk];

void insert(ll x)
{
    DEC(i, 53, 0)
    {
        if (!(x >> (ll)i)) continue;
        if (!a[i]) a[i] = x;
        x ^= a[i];
    }
    return;
}

int main()
{
    n = read();
    FOR(i, 1, n) insert(read());
    ll ans = 0;
    DEC(i, 53, 0)
        if ((ans ^ a[i]) > ans) ans ^= a[i];
    printf("%lld\n", ans);
    return 0;
}