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

const ll maxn = 2e3 + 5, mod = 998244353;
ll x[maxn], y[maxn];

ll pow(ll base, ll p)
{
    ll ans = 1;
    base = (base + mod) % mod;
    for (; p; p >>= 1)
    {
        if (p & 1)
            ans = ans * base % mod;
        base = base * base % mod;
    }
    return ans;
}

il ll inv(ll n)
{
    return pow(n, mod - 2);
}

int main()
{
    ll n = read(), k = read();
    for (int i = 1 ; i <= n; ++i)
        x[i] = read(), y[i] = read();
    ll ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        ll prod1 = 1, prod2 = 1;
        for (int j = 1; j <= n; ++j)
        {
            if (i == j)
                continue;
            prod1 = prod1 * (k - x[j]) % mod;
            prod2 = prod2 * (x[i] - x[j]) % mod;
        }
        ans = (ans + prod1 * y[i] % mod * inv(prod2) % mod + mod) % mod;
    }
    printf("%lld\n", ans);
    return 0;
}