#include <cstdio>
#define FOR(i, a, b) for (ll i = a; i <= b; ++i)

typedef long long ll;

ll P, n, m, w[6];

void exgcd(ll a, ll b, ll &x, ll &y)
{
    if (!b)
    {
        x = 1, y = 0;
        return;
    }
    exgcd(b, a % b, y, x);
    y -= a / b * x;
    return;
}

ll inv(ll a, ll p)
{
    ll x, y;
    exgcd(a, p, x, y);
    return (x + p) % p;
}

ll qpow(ll a, ll b, ll p)
{
    ll ret = 1;
    for (; b; b >>= 1, a = a * a % p)
        if (b & 1) ret = ret * a % p;
    return ret;
}

ll CRT(int n, ll *a, ll *m)
{
    ll M = 1, ret = 0;
    FOR(i, 1, n) M *= m[i];
    FOR(i, 1, n)
    {
        ll w = M / m[i];
        ret = (ret + a[i] * w % P * inv(w, m[i]) % P) % P;
    }
    return (ret + P) % P;
}

ll calc(ll n, ll q, ll qk)
{
    if (!n) return 1;
    ll ret = 1;
    FOR(i, 1, qk)
        if (i % q) ret = ret * i % qk;
    ret = qpow(ret, n / qk, qk);
    FOR(i, n / qk * qk + 1, n)
        if (i % q) ret = ret * (i % qk) % qk;
    return ret * calc(n / q, q, qk) % qk;
}

ll multiLucas(ll n, ll m, ll q, ll qk)
{
    ll cnt = 0;
    for (ll i = n; i; i /= q) cnt += i / q;
    for (ll i = m; i; i /= q) cnt -= i / q;
    for (ll i = n - m; i; i /= q) cnt -= i / q;
    return qpow(q, cnt, qk) * calc(n, q, qk) % qk * inv(calc(m, q, qk), qk) % qk * inv(calc(n - m, q, qk), qk) % qk;
}

ll exLucas(ll n, ll m, ll p)
{
    int cnt = 0;
    ll qk[20], a[20];
    for (ll i = 2; i * i <= p; ++i)
    {
        if (p % i) continue;
        qk[++cnt] = 1;
        while (p % i == 0)
            qk[cnt] *= i, p /= i;
        a[cnt] = multiLucas(n, m, i, qk[cnt]);
    }
    if (p > 1) qk[++cnt] = p, a[cnt] = multiLucas(n, m, p, p);
    return CRT(cnt, a, qk);
}

int main()
{
    scanf("%lld", &P);
    scanf("%lld %lld", &n, &m);
    ll W = 0;
    FOR(i, 1, m) scanf("%lld", w + i), W += w[i];
    if (W > n)
    {
        puts("Impossible");
        return 0;
    }
    ll ans = 1;
    FOR(i, 1, m)
    {
        ans = ans * exLucas(n, w[i], P) % P;
        n -= w[i];
    }
    printf("%lld\n", ans);
    return 0;
}