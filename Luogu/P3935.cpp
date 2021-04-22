#include <cstdio>

typedef unsigned long long ll;

const ll mod = 998244353;

ll calc(ll n)
{
    ll ret = 0;
    for (ll l = 1, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        ret += (r - l + 1) * (n / l);
        ret %= mod;
    }
    return ret;
}

int main()
{
    ll l, r;
    scanf("%lld %lld", &l, &r);
    printf("%lld\n", (calc(r) - calc(l - 1) + mod) % mod);
    return 0;
}