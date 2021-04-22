#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (register int i = a; i <= b; ++i)

const int maxn = 1e7 + 7;

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

inline int min(int a, int b) {return a < b ? a : b;}

typedef long long ll;

int mu[maxn], p[maxn], vis[maxn], tot;
ll sum[maxn];

void getmu()
{
    mu[1] = 1;
    FOR(i, 2, maxn - 5)
    {
        if (!vis[i])
        {
            p[++tot] = i;
            mu[i] = -1;
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
    FOR(j, 1, tot)
        for (int i = 1; i * p[j] <= maxn - 5; ++i)
            sum[i * p[j]] += mu[i];
    FOR(i, 1, maxn - 5)
        sum[i] += sum[i - 1];
    return;
}

signed main()
{
    getmu();
    int kase = read();
    while (kase--)
    {
        int n = read(), m = read();
        int top = min(n, m);
        ll ans = 0;
        for (int l = 1, r = 0; l <= top; l = r + 1)
        {
            r = min(top, min(n / (n / l), m / (m / l)));
            ans += (ll)(n / l) * (ll)(m / l) * (sum[r] - sum[l - 1]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}