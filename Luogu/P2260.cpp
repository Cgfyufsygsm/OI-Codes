#include <cstdio>
#define il inline

typedef long long ll;

inline ll min(ll a, ll b){return a < b ? a : b;}

const ll mod = 19940417, inv2 = 9970209, inv6 = 3323403;

ll n, m, ans;

ll calc(ll n, ll k)
{
    ll ret = 0;
    n = min(n, k);
    for (ll l = 1, r = 1; l <= n; l = r + 1)
    {
        r = min(n, k / (k / l));
        ret += ((r - l + 1) * (k / l * l) % mod + (r - l + 1) * (r - l) % mod * (k / l) % mod * inv2 % mod) % mod;
        ret %= mod;
    }
    return ret;
}

il ll summod(ll n)
{
    return (n * n % mod - calc(n, n) + mod) % mod;
}

il ll sum(ll n)
{
    return n * (n + 1) % mod * (2 * n + 1) % mod * inv6 % mod;
}

ll calc2(ll n, ll m)
{
    ll top = min(n, m);
    ll ret = n * m % mod * top % mod;
    ret -= m * calc(top, n);
    ret = (ret + mod) % mod;
    ret -= n * calc(top, m);
    ret = (ret + mod) % mod;
    for (ll l = 1, r; l <= top; l = r + 1)
    {
        r = min(min(top, n / (n / l)), m / (m / l));
        ll sqri = sum(r) - sum(l - 1);
        ret = (ret + sqri * (n / l) % mod * (m / l) % mod) % mod;
    }
    return ret;
}

int main()
{
    scanf("%lld %lld", &n, &m);
    ans = summod(n) * summod(m) % mod;
    ans = (ans - calc2(n, m) + mod) % mod;
    printf("%lld\n", ans);
    return 0;
}