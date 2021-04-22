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

int f[maxn << 1], g[maxn << 1];
int ans[maxn << 1];

int n, m, k, lim = 1;
char s[maxn << 1], t[maxn << 1];

void proc(char c)
{
    clr(f, lim), clr(g, lim);
    for (int i = 1, lst = -1e9; i <= n; ++i)
    {
        if (s[i] == c)
            lst = i;
        if (i - lst <= k)
            f[i] = 1;
    }
    for (int i = n, lst = 1e9; i; --i)
    {
        if (s[i] == c)
            lst = i;
        if (lst - i <= k)
            f[i] = 1;
    }
    FOR(i, 1, m)
        g[i] = (t[m - i + 1] == c);
    NTT(f, lim, 1), NTT(g, lim, 1);
    FOR(i, 0, lim - 1)
        f[i] = 1ll * f[i] * g[i] % mod;
    NTT(f, lim, 0);
    FOR(i, 1, n)
        ans[i] += f[i + m];
}

int main()
{
    n = readInt(), m = readInt(), k = readInt();
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    while (lim <= n + m) lim <<= 1;
    FOR(i, 0, 3) proc("ATCG"[i]);
    int cnt = 0;
    FOR(i, 1, n)
        cnt += (ans[i] == m);
    printf("%d\n", cnt);
    return 0;
}