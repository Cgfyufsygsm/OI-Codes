#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

typedef long long ll;

const int maxn = 5e5 + 5;
const ll G = 3, mod = 2281701377;

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
            f[i] = f[i] * invlim % mod;
    return;
}

ll f1[maxn], f2[maxn], f3[maxn], ans[maxn];
ll g[maxn], t[maxn];

int main()
{
    int n = read();
    while (n--)
    {
        int tmp = read();
        ++f1[tmp], ++g[tmp], ++ans[tmp];
        ++f2[tmp << 1], ++f3[tmp * 3];
    }
    int lim = 1;
    while (lim <= (40000 * 3 + 5)) lim <<= 1;
    FOR(i, 0, lim - 1)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
    NTT(f1, lim, 1), NTT(g, lim, 1);
    FOR(i, 0, lim - 1)
        g[i] = f1[i] * g[i] % mod;
    NTT(g, lim, 0);
    FOR(i, 0, lim - 1)
        ans[i] += (g[i] - f2[i]) / 2;
    NTT(g, lim, 1);
    FOR(i, 0, lim - 1)
        g[i] = f1[i] * g[i] % mod;
    NTT(g, lim, 0);
    NTT(f2, lim, 1);
    FOR(i, 0, lim - 1)
        f2[i] = f2[i] * f1[i] % mod;
    NTT(f2, lim, 0);
    FOR(i, 0, lim - 1)
    {
        ans[i] += (g[i] - 3 * f2[i] + 2 * f3[i]) / 6;
        if (ans[i]) printf("%d %lld\n", i, ans[i]);
    }
    return 0;
}