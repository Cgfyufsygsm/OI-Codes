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

int f[maxn << 1], g[maxn << 1], f2[maxn << 1], g2[maxn << 1], f3[maxn << 1], g3[maxn << 1];
int ans[maxn << 1], vec[maxn << 1], tot;

int n, m;
char a[maxn], b[maxn];

int main()
{
    m = readInt(), n = readInt();
    scanf("%s", a + 1);
    scanf("%s", b + 1);
    FOR(i, 1, m)
    {
        g[i] = (a[m - i + 1] == '*') ? 0 : a[m - i + 1] - 'a' + 1;
        g2[i] = g[i] * g[i], g3[i] = g2[i] * g[i];
    }
    FOR(i, 1, n)
    {
        f[i] = (b[i] == '*') ? 0 : b[i] - 'a' + 1;
        f2[i] = f[i] * f[i], f3[i] = f2[i] * f[i];
    }
    int lim = 1;
    while (lim <= n + m) lim <<= 1;
    NTT(f, lim, 1), NTT(f2, lim, 1), NTT(f3, lim, 1);
    NTT(g, lim, 1), NTT(g2, lim, 1), NTT(g3, lim, 1);
    FOR(i, 0, lim - 1)
        ans[i] = (1ll * f3[i] * g[i] % mod + 1ll * f[i] * g3[i] % mod - 2ll * f2[i] * g2[i] % mod) % mod;
    NTT(ans, lim, 0);
    int cnt = 0;
    FOR(i, 1, n - m + 1)
        if (ans[i + m] == 0)
            ++cnt, vec[++tot] = i;
    printf("%d\n", cnt);
    FOR(i, 1, tot) printf("%d ", vec[i]);
    return 0;
}