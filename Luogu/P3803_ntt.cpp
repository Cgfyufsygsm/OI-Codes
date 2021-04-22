#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

typedef long long ll;

const ll G = 3;
const ll mod = 998244353;
const int maxn = 3e6 + 5;

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

template<typename T> inline void myswap(T &a, T &b)
{
    T t = a;
    a = b;
    b = t;
    return;
}

ll pow(ll base, ll p = mod - 2)
{
    ll ret = 1;
    for (; p; p >>= 1)
    {
        if (p & 1)
            ret = ret * base % mod;
        base = base * base % mod;
    }
    return ret;
}

int rev[maxn];
ll f[maxn], g[maxn];
const ll invG = pow(G);

void NTT(ll *f, int lim, int type)
{
    FOR(i, 0, lim - 1)
        if (i < rev[i])
            myswap(f[i], f[rev[i]]);
    for (int p = 2; p <= lim; p <<= 1)
    {
        int len = p >> 1;
        ll tG = pow(type ? G : invG, (mod - 1) / p);
        for (int k = 0; k < lim; k += p)
        {
            ll buf = 1;
            for (int l = k; l < k + len; ++l, buf = buf * tG % mod)
            {
                ll tmp = buf * f[len + l] % mod;
                f[len + l] = f[l] - tmp;
                if (f[len + l] < 0) f[len + l] += mod;
                f[l] = f[l] + tmp;
                if (f[l] > mod) f[l] -= mod;
            }
        }
    }
    ll invlim = pow(lim);
    if (!type)
        FOR(i, 0, lim - 1)
            f[i] = (f[i] * invlim % mod);
    return;
}

int main()
{
    int n = read(), m = read();
    FOR(i, 0, n) f[i] = read();
    FOR(i, 0, m) g[i] = read();
    int lim = 1;
    while (lim <= n + m) lim <<= 1;
    FOR(i, 0, lim - 1)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
    NTT(f, lim, 1), NTT(g, lim, 1);
    FOR(i, 0, lim - 1)
        f[i] = f[i] * g[i] % mod;
    NTT(f, lim, 0);
    FOR(i, 0, n + m)
        printf("%d ", (int)f[i]);
    return 0;
}