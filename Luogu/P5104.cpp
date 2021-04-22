#include <cstdio>

typedef long long ll;

const ll mod = 1e9 + 7;

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
    long long w, n, k;
    scanf("%lld %lld %lld", &w, &n, &k);
    printf("%lld\n", w * qpow(qpow(2, k)) % mod);
    return 0;
}