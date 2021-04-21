#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (ll i = a; i <= b; ++i)
#define DEC(i, a, b) for (ll i = a; i >= b; --i)
#ifdef win32
#define AUTO "%I64d"
#else
#define AUTO "%lld"
#endif
#define int long long

typedef long long ll;
const int maxk = 65;

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

ll f[maxk], cnt, n, zero;

void insert(ll x)
{
    DEC(i, 62, 0)
    {
        if (!(x >> (ll)i)) continue;
        if (!f[i]) f[i] = x;
        x ^= f[i];
        if (!x) break;
    }
    if (!x) zero = 1;
    return;
}

ll kth(ll k)
{
    if (k >= (1ll << cnt)) return -1;
    ll ans = 0;
    DEC(i, 62, 0)
        if (k & (1ll << i))
            ans ^= f[i];
    return ans;
}

signed main()
{
    int T = read();
    FOR(i, 1, T)
    {
        memset(f, 0, sizeof f);
        n = read();
        zero = cnt = 0;
        FOR(i, 1, n) insert(read());
        DEC(i, 62, 0)
            DEC(j, i - 1, 0)
                if (f[i] & (1 << j))
                    f[i] ^= f[j];
        FOR(i, 0, 62)
            if (f[i]) f[cnt++] = f[i];
        int q = read();
        printf("Case #%d:\n", i);
        while (q--) printf(AUTO"\n", kth(read() - (cnt < n)));
    }
    return 0;
}