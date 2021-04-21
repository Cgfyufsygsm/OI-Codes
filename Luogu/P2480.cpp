#include <cstdio>
#define FOR(i, a, b) for (ll i = a; i <= b; ++i)

typedef long long ll;

const ll mod[5] = {999911659, 2, 3, 4679, 35617};

const int maxp = 40005;
ll fact[maxp];

ll qpow(ll base, ll p, ll mod)
{
    ll ret = 1;
    for (; p; p >>= 1, base = base * base % mod)
        if (p & 1) ret = ret * base % mod;
    return ret;
}

void init(ll p)
{
    fact[0] = 1;
    FOR(i, 1, p)
        fact[i] = fact[i - 1] * i % p;
    return;
}

ll C(int n, int m, ll p)
{
    if (n < m) return 0;
    return fact[n] * qpow(fact[m], p - 2, p) % p * qpow(fact[n - m], p - 2, p) % p;
}

ll Lucas(ll n, ll m, ll p)
{
    if (n < m) return 0;
    if (!n || !m) return 1;
    return Lucas(n / p, m / p, p) * C(n % p, m % p, p) % p;
}

ll a[5];

int main()
{
    ll n, g;
    scanf("%lld %lld", &n, &g);
    if (g % mod[0] == 0)
    {
        printf("0\n");
        return 0;
    }
    FOR(k, 1, 4)
    {
        init(mod[k]);
        for (ll i = 1; i * i <= n; ++i)
        {
            if (n % i) continue;
            a[k] = (a[k] + Lucas(n, i, mod[k])) % mod[k];
            if (i * i != n)
                a[k] = (a[k] + Lucas(n, n / i, mod[k])) % mod[k];
        }
    }
    ll M = mod[0] - 1, ans = 0;
    FOR(i, 1, 4)
    {
        int w = M / mod[i];
        ans = (ans + a[i] * w % M * qpow(w, mod[i] - 2, mod[i]) % M) % M;
    }
    printf("%lld\n", qpow(g, ans, mod[0]));
    return 0;
}