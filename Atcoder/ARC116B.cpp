#include <cstdio>
#include <cctype>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

typedef long long ll;

ll read()
{
    ll s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

const ll mod = 998244353;
const int maxn = 2e5 + 5;

int n;
ll a[maxn], pow2[maxn], s[maxn];

ll inv(ll a)
{
    ll b = mod - 2, ret = 1;
    for (; b; b >>= 1, a = a * a % mod)
        if (b & 1) ret = ret * a % mod;
    return ret;
}

int main()
{
    n = read();
    pow2[0] = 1;
    FOR(i, 1, n) a[i] = read(), pow2[i] = pow2[i - 1] * 2 % mod;
    std::sort(a + 1, a + n + 1);
    DEC(i, n, 1) s[i] = (s[i + 1] + pow2[i - 1] * a[i] % mod) % mod;
    ll ans = 0;
    FOR(i, 1, n - 1)
        ans = (ans + inv(pow2[i]) * a[i] % mod * s[i + 1] % mod) % mod;
    FOR(i, 1, n) ans = (ans + a[i] * a[i] % mod) % mod;
    printf("%lld\n", ans);
    return 0;
}