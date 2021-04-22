#include <cstdio>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

typedef long long ll;
const ll mod = 1e9 + 7;
const int maxn = 1e6 + 5;

ll n, k;

ll fac[maxn], pre[maxn], suf[maxn];

ll qpow(ll base, ll p = mod - 2)
{
    ll ret = 1;
    for (; p; p >>= 1, base = base * base % mod)
        if (p & 1)
            ret = ret * base % mod;
    return ret;
}

int main()
{
    scanf("%lld %lld", &n, &k);
    if (!k)
    {
        printf("%lld\n", n);
        return 0;
    }
    ll ans = 0, y = 0;
    pre[0] = 1, fac[0] = 1;
    FOR(i, 1, k + 2)
        pre[i] = pre[i - 1] * (n - i) % mod, fac[i] = fac[i - 1] * i % mod;
    suf[k + 3] = 1;
    DEC(i, k + 2, 0)
        suf[i] = suf[i + 1] * (n - i) % mod;
    FOR(i, 1, k + 2)
    {
        y = (y + qpow(i, k)) % mod;
        ll tmp = y * pre[i - 1] % mod * suf[i + 1] % mod * (((k - i) & 1) ? -1 : 1) * qpow(fac[i - 1] * fac[k + 2 - i] % mod) % mod;
        ans = (ans + tmp + mod) % mod;
    }
    printf("%lld\n", ans);
    return 0;
}