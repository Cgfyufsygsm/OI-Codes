#include <cstdio>
#include <cctype>
#include <unordered_map>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

inline int read()
{
    char c = getchar();
    int s = 0;
    bool x = 0;
    while (!isdigit(c))
        x = x | (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x?-s:s;
}

typedef unsigned long long ll;

const int maxn = 1e7 + 15;
std::unordered_map<int, ll> Mu, Phi;
ll mu[maxn], phi[maxn];
int vis[maxn], p[maxn], tot;

void init()
{
    mu[1] = 1, phi[1] = 1;
    FOR(i, 2, maxn - 5)
    {
        if (!vis[i])
            p[++tot] = i, mu[i] = -1, phi[i] = i - 1;
        for (int j = 1; j <= tot && i * p[j] <= maxn - 5; ++j)
        {
            vis[i * p[j]] = 1;
            if (i % p[j] == 0)
            {
                phi[i * p[j]] = phi[i] * p[j];
                break;
            }
            mu[i * p[j]] = -mu[i];
            phi[i * p[j]] = phi[i] * (p[j] - 1);
        }
    }
    FOR(i, 2, maxn - 5)
        phi[i] += phi[i - 1], mu[i] += mu[i - 1];
    return;
}

ll getSumPhi(ll n)
{
    if (n <= maxn)
        return phi[n];
    if (Phi[n])
        return Phi[n];
    ll ans = (ll)(n + 1ll) * (ll)n / 2ll;
    for (ll l = 2, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        ans -= (r - l + 1LL) * getSumPhi(n / l);
    }
    return Phi[n] = ans;
}

ll getSumMu(ll n)
{
    if (n <= maxn)
        return mu[n];
    if (Mu[n])
        return Mu[n];
    ll ans = 1;
    for (ll l = 2, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        ans -= (r - l + 1LL) * getSumMu(n / l);
    }
    return Mu[n] = ans;
}

int main()
{
    init();
    int T = read();
    while (T--)
    {
        int n = read();
        printf("%lld %lld\n", getSumPhi(n), getSumMu(n));
    }
    return 0;
}