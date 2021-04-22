#include <cstdio>
#include <cctype>
#include <cstring>
#define ll long long
#define ull unsigned ll
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define clr(f, n) memset(f, 0, (sizeof(int)) * (n))
#define cpy(f, g, n) memcpy(f, g, (sizeof(int)) * (n))

const ll G = 3, mod = 1004535809;
const int maxn = ((1 << 21) + 500);

inline ll max(ll a, ll b) {return a > b ? a : b;}

ll readInt()
{
    ll s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

ll qpow(ll base, ll p = mod - 2)
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

const ll invG = qpow(G);

int rev[maxn << 1], revlim;

void get_rev(int lim)
{
    if (lim == revlim) return;
    revlim = lim;
    FOR(i, 0, lim - 1)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
    return;
}

void NTT(int *g, int n, int type)
{
    get_rev(n);
    static ull f[maxn << 1], w[maxn];
    w[0] = 1;
    FOR(i, 0, n - 1)
        f[i] = (((long long)mod << 5ll) + g[rev[i]]) % mod;
    for (int l = 1; l < n; l <<= 1)
    {
        ull tmp = qpow(type ? G : invG, (mod - 1) / (l << 1));
        FOR(i, 1, l - 1) w[i] = w[i - 1] * tmp % mod;
        for (int i = 0; i < n; i += (l << 1))
        {
            for (int j = 0; j < l; ++j)
            {
                ll tt = w[j] * f[i + j + l] % mod;
                f[i + j + l] = f[i + j] + mod - tt;
                f[i + j] += tt;
            }
        }
        if (l == (1 << 10))
            FOR(i, 0, n - 1) f[i] %= mod;
    }
    if (!type)
    {
        ull invn  = qpow(n);
        FOR(i, 0, n - 1)
            g[i] = f[i] % mod * invn % mod;
    }
    else FOR(i, 0, n - 1)
        g[i] = f[i] % mod;
    return;
}

void invpoly(int *f, int m)
{
    int n;
    for (n = 1; n < m; n <<= 1);
    static int w[maxn << 1], r[maxn << 1], sav[maxn << 1];
    w[0] = qpow(f[0]);
    for (int len = 2; len <= n; len <<= 1)
    {
        FOR(i, 0, (len >> 1) - 1)
            r[i] = w[i];
        cpy(sav, f, len), NTT(sav, len, 1), NTT(r, len, 1);
        FOR(i, 0, len - 1)
            r[i] = 1ll * r[i] * sav[i] % mod;
        NTT(r, len, 0), clr(r, len >> 1);
        cpy(sav, w, len), NTT(sav, len, 1), NTT(r, len, 1);
        FOR(i, 0, len - 1)
            r[i] = 1ll * r[i] * sav[i] % mod;
        NTT(r, len, 0);
        for (int i = len >> 1; i < len; ++i)
            w[i] = (w[i] * 2ll - r[i] + mod) % mod;
    }
    cpy(f, w, m);
    clr(sav, n);
    clr(w, n);
    clr(r, n);
    return;
}

void derivate(int *f, int m)
{
    FOR(i, 1, m - 1)
        f[i - 1] = 1ll * f[i] * i % mod;
    f[m - 1] = 0;
    return;
}

int inv[maxn];

void initinv(int lim)
{
    inv[1] = 1;
    FOR(i, 2, lim)
        inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
    return;
}

void intergrate(int *f, int m)
{
    DEC(i, m, 1)
        f[i] = 1ll * f[i - 1] * inv[i] % mod;
    f[0] = 0;
}

void polyln(int *f, int m)
{
    static int invf[maxn << 1];
    int lim = 1;
    while (lim < m << 1) lim <<= 1;
    initinv(lim);
    cpy(invf, f, m);
    invpoly(invf, m);
    derivate(f, m);
    NTT(f, lim, 1), NTT(invf, lim, 1);
    FOR(i, 0, lim - 1)
        f[i] = 1ll * f[i] * invf[i] % mod;
    NTT(f, lim, 0);
    intergrate(f, m);
    clr(invf, lim);
}

int f[maxn << 1], invf[maxn << 1];
int fact[maxn << 1];

int n;

int main()
{
    n = readInt();
    fact[0] = 1, f[0] = 1;
    FOR(i, 1, n)
        fact[i] = 1ll * fact[i - 1] * i % mod,
        f[i] = 1ll * qpow(2, 1ll * i * (i - 1ll) >> 1) % mod * qpow(fact[i]) % mod;
    polyln(f, n + 1);
    printf("%d\n", 1ll * f[n] * fact[n] % mod);
    return 0;
}