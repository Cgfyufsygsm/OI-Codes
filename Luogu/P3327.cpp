#include <cstdio>
#include <cctype>

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

typedef long long ll;

inline int min(int a, int b) {return a < b ? a : b;}

const int maxn = 50005;

int mu[maxn], p[maxn], vis[maxn], tot;
ll f[maxn];

void get_mu()
{
    mu[1] = 1;
    for (int i = 2; i <= maxn - 5; ++i)
    {
        if (!vis[i])
        {
            mu[i] = -1;
            p[++tot] = i;
        }
        for (int j = 1; j <= tot && i * p[j] <= maxn - 5; ++j)
        {
            vis[i * p[j]] = 1;
            if (i % p[j] == 0)
            {
                mu[i * p[j]] = 0;
                break;
            }
            mu[i * p[j]] = -mu[i];
        }
    }
    for (int i = 2; i <= maxn - 5; ++i)
        mu[i] += mu[i - 1];
    return;
}

void get_f()
{
    for (int n = 1; n <= maxn - 5; ++n)
        for (int l = 1, r; l <= n; l = r + 1)
        {
            r = n / (n / l);
            f[n] += (r - l + 1ll) * (n / l);
        }
    return;
}

ll solve(int n, int m)
{
    ll ret = 0;
    int up = min(n, m);
    for (int l = 1, r; l <= up; l = r + 1)
    {
        r = min(n / (n / l), m / (m / l));
        ret += (ll)(mu[r] - mu[l - 1]) * f[n / l] * f[m / l];
    }
    return ret;
}

signed main()
{
    get_mu();
    get_f();
    int T = read();
    while (T--)
    {
        int n = read(), m = read();
        printf("%lld\n", solve(n, m));
    }
    return 0;
}