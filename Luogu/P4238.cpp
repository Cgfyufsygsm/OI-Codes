#include <cstdio>
#include <cctype>
#include <cstring>
#define ll long long
#define ull unsigned ll
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define clr(f, n) memset(f, 0, (sizeof(int)) * (n))
#define cpy(f, g, n) memcpy(f, g, (sizeof(int)) * (n))

const ll G = 3, mod = 998244353;
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
    for (int len = 2; len <= n; len <<= 1)//len 代表当前的界
    {
        FOR(i, 0, (len >> 1) - 1)
            r[i] = (w[i] << 1) % mod;//处理 2G'(x)
        cpy(sav, f, len);
        NTT(w, len << 1, 1);
        FOR(i, 0, (len << 1) - 1)
            w[i] = 1ll * w[i] * w[i] % mod;
        NTT(sav, len << 1, 1);
        FOR(i, 0, (len << 1) - 1)
            w[i] = 1ll * w[i] * sav[i] % mod;
        NTT(w, len << 1, 0);
        clr(w + len, len);
        FOR(i, 0, len - 1)
            w[i] = (r[i] - w[i] + mod) % mod;
    }
    cpy(f, w, m);//把答案还回到 f 数组里面
    clr(sav, n << 1);//清零
    clr(w, n << 1);//清零
    clr(r, n << 1);//清零
    return;
}

int f[maxn << 1];

int n, m;

int main()
{
    n = readInt();
    FOR(i, 0, n - 1) f[i] = readInt();
    invpoly(f, n);
    FOR(i, 0, n - 1) printf("%d ", f[i]);
    return 0;
}