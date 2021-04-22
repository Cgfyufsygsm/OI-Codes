#include <cstdio>
#include <cctype>
#include <utility>
#include <algorithm>
#define int long long
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define lowbit(x) ((x) & (-x))
#define Fi first
#define Se second
#define mk(a, b) std::make_pair(a, b)

const int maxn = 1e5 + 13;

struct queries
{
    int n, m, a, id;
} q[20000 + 5];

bool cmp(queries a, queries b) {return a.a < b.a;}

inline int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c =getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

inline int min(int a, int b) {return a < b ? a : b;}

int g[maxn], mu[maxn], vis[maxn], p[maxn], tot;
std::pair<int, int> f[maxn];
int tree[maxn], ans[maxn];

void modify(int x, int val)
{
    for (; x <= maxn - 5; x += lowbit(x))
        tree[x] += val;
    return;
}

int query(int x)
{
    int ret = 0;
    for (; x; x -= lowbit(x))
        ret += tree[x];
    return ret;
}

void pre()
{
    g[1] = mu[1] = 1;
    f[1] = mk(1, 1);
    FOR(i, 2, maxn - 5)
    {
        if (!vis[i])
        {
            vis[i] = 1;
            p[++tot] = i;
            mu[i] = -1;
            f[i] = mk(g[i] = i + 1, i);
        }
        for (int j = 1; j <= tot && i * p[j] <= maxn - 5; ++j)
        {
            vis[i * p[j]] = 1;
            if (i % p[j] == 0)
            {
                g[i * p[j]] = g[i] * p[j] + 1;
                f[i * p[j]] = mk(f[i].Fi / g[i] * g[i * p[j]], i * p[j]);
                mu[i * p[j]] = 0;
                break;
            }
            else
            {
                mu[i * p[j]] = -mu[i];
                f[i * p[j]] = mk(f[i].Fi * f[p[j]].Fi, i * p[j]);
                g[i * p[j]] = p[j] + 1;
            }
        }
    }
}

int solve(int n, int m)
{
    if (n > m) {int t = n; n = m; m = t;}
    int ret = 0;
    for (int l = 1, r; l <= n; l = r + 1)
    {
        r = min(n / (n / l), m / (m / l));
        ret += (query(r) - query(l - 1)) * (n / l) * (m / l);
    }
    return ret;
}

signed main()
{
    pre();
    std::sort(f + 1, f + maxn - 5);
    int Q = read();
    FOR(i, 1, Q)
        q[i].id = i, q[i].n = read(), q[i].m = read(), q[i].a = read();
    std::sort(q + 1, q + 1 + Q, cmp);
    for (int i = 1, j = 1; i <= Q; ++i)
    {
        for (; f[j].Fi <= q[i].a && j <= maxn - 5; ++j)
            for (int k = f[j].Se; k <= maxn - 5; k += f[j].Se)
                modify(k, f[j].Fi * mu[k / f[j].Se]);
        ans[q[i].id] = solve(q[i].n, q[i].m);
    }
    FOR(i, 1, Q) printf("%lld\n", ans[i] % (1LL << 31));
    return 0;
}