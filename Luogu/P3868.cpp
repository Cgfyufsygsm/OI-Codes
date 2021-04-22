#include <cstdio>
#include <cctype>
#define il inline

typedef long long ll;

inline ll read()
{
    char c = getchar();
    ll s = 0;
    bool x = 0;
    while (!isdigit(c))
        x = x | (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (!b)
    {
        x = 1, y = 0;
        return a;
    }
    ll tmp = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return tmp;
}

ll mul(ll a, ll b, ll mod)
{
    b = (b + mod) % mod, a = (a + mod) % mod;
    ll ans = 0, x = a;
    for (; b; b >>= 1ll)
    {
        if (b & 1ll)
            ans = (ans + x) % mod;
        x = (x << 1) % mod;
    }
    return ans;
}

il ll inv(ll n, ll mod)
{
    ll x, y;
    exgcd(n, mod, x, y);
    return (x + mod) % mod;
}

ll a[11], b[11], M = 1, m[11];

int main()
{
    ll k = read();
    for (int i = 1; i <= k; ++i)
        a[i] = read();
    for (int i = 1; i <= k; ++i)
        b[i] = read(), M *= b[i];
    ll ans = 0;
    for (int i = 1; i <= k; ++i)
    {
        a[i] = (a[i] + b[i]) % b[i];
        m[i] = M / b[i];
        ans = (ans + mul(a[i], mul(m[i], inv(m[i], b[i]), M), M) + M) % M;
    }
    printf("%lld\n", ans % M);
}