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
    ll ans = 0, x = a;
    b = (b + mod) % mod, a = (a + mod) % mod;
    for (; b; b >>= 1ll)
    {
        if (b & 1ll)
            ans = (ans + x) % mod;
        x = (x << 1) % mod;
    }
    return ans;
}

const int maxn = 1e5 + 5;
ll n, m[maxn], r[maxn];

int main()
{
    n = read();
    for (int i = 1; i <= n; ++i)
        m[i]= read(), r[i] = read();
    for (int i = 2; i <= n; ++i)
    {
        ll tmpx, tmpy;
        ll gcd = exgcd(m[i], m[i - 1], tmpx, tmpy);
        ll p1 = m[i - 1] / gcd, p2 = m[i] / gcd;
        exgcd(p1, p2, tmpx, tmpy);
        m[i] = m[i] / gcd * m[i - 1];
        r[i] = (r[i - 1] + mul(m[i - 1], mul((r[i] - r[i - 1]) / gcd, tmpx, m[i]), m[i])) % m[i];
    }
    printf("%lld\n", r[n] % m[n]);
    return 0;
}