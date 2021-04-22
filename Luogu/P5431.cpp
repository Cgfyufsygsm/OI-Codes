#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

int read()
{
    int s = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

typedef long long ll;
const int maxn = 5e6 + 5;
ll mod, n, k, a[maxn], pre[maxn], suf[maxn];

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
    n = read(), mod = read(), k = read();
    FOR(i, 1, n) a[i] = read();
    pre[0] = 1;
    FOR(i, 1, n) pre[i] = pre[i - 1] * a[i] % mod;
    suf[n + 1] = 1;
    DEC(i, n, 1) suf[i] = suf[i + 1] * a[i] % mod;
    ll tmp = qpow(pre[n]), ans = 0, ki = 1;
    FOR(i, 1, n)
    {
        ki = ki * k % mod;
        ans = (ans + tmp * ki % mod * pre[i - 1] % mod * suf[i + 1] % mod) % mod;
    }
    printf("%lld\n", ans);
    return 0;
}