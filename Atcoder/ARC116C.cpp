#include <cstdio>
#include <cctype>
#include <vector>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 3e5 + 5, mod = 998244353;

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

typedef long long ll;

ll n, m;

ll qpow(ll a)
{
    ll b = mod - 2, ret = 1;
    for (; b; b >>= 1, a = 1ll * a * a % mod)
        if (b & 1) ret = 1ll * ret * a % mod;
    return ret;
}

ll fact[maxn], inv[maxn];

ll binom(int n, int k)
{
    return fact[n] * inv[k] % mod * inv[n - k] % mod;
}

void init()
{
    fact[0] = 1;
    FOR(i, 1, maxn - 1) fact[i] = i * fact[i - 1] % mod;
    inv[maxn - 1] = qpow(fact[maxn - 1]);
    DEC(i, maxn - 2, 0) inv[i] = (i + 1) * inv[i + 1] % mod;
    return;
}

int main()
{
    n = read(), m = read();
    init();
    ll ans = 0;
    FOR(i, 1, m)
    {
        int now = i;
        std::vector<int> tmp;
        for (int p = 2; p * p <= now && now != 1; ++p)
        {
            if (now % p) continue;
            int cnt = 0;
            while (now % p == 0)
                ++cnt, now /= p;
            tmp.push_back(cnt);
        }
        if (now != 1) tmp.push_back(1);
        ll t = 1;
        for (auto c : tmp)
            t = t * binom(n + c - 1, c) % mod;
        ans = (ans + t) % mod;
    }
    printf("%d\n", ans);
    return 0;
}