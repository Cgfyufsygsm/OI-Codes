#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

typedef long long ll;

void swap(ll &a, ll &b)
{
    ll t = a; a = b; b = t;
    return;
}

ll read()
{
    ll ret = 0; int rev = 0;
    char c = getchar();
    while (!isdigit(c))
        rev |= (c == '-'), c = getchar();
    while (isdigit(c))
        ret = 10 * ret + c - '0', c = getchar();
    return rev ? -ret : ret;
}

ll min(ll a, ll b) {return a < b ? a : b;}

const int maxn = 2e6 + 5;
const ll G = 3;
const ll mod = 998244353;

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

const ll invG = pow(G);
ll a[maxn], b[maxn];
ll suma, sumb, suma2, sumb2, n, m;
int rev[maxn];

void NTT(ll *f, int lim, int type)
{
    FOR(i, 0, lim - 1)
        if (i < rev[i])
            swap(f[i], f[rev[i]]);
    for (int p = 2; p <= lim; p <<= 1)
    {
        int len = p >> 1;
        ll Gp = pow(type ? G : invG, (mod - 1) / p);
        for (int k = 0; k < lim; k += p)
        {
            ll buf = 1;
            for (int l = k; l < k + len; ++l, buf = buf * Gp % mod)
            {
                ll tmp = buf * f[l + len] % mod;
                f[l + len] = f[l] - tmp;
                if (f[l + len] < 0) f[l + len] += mod;
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

int main()
{
    n = read(), m = read();
    FOR(i, 1, n)
        a[i] = a[i + n] = read(), suma += a[i], suma2 += a[i] * a[i];
    FOR(i, 1, n)
        b[n - i + 1] = read(), sumb += b[n - i + 1], sumb2 += b[n - i + 1] * b[n - i + 1];
    int lim = 1;
    while (lim <= 3 * n) lim <<= 1;
    FOR(i, 0, lim - 1)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
    NTT(a, lim, 1), NTT(b, lim, 1);
    FOR(i, 0, lim)
        a[i] = a[i] * b[i] % mod;
    NTT(a, lim, 0);
    ll ans = 1e18;
    FOR(i, 1, n)
        FOR(j, -m, m)
            ans = min(ans, suma2 + sumb2 + j * j * n + 2 * j * (suma - sumb) - 2 * a[i + n]);
    printf("%lld\n", ans);
    return 0;
}