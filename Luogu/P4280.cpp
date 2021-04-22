#include <cstdio>
#include <cctype>
#include <cstring>
#define lowbit(x) (x & -x)
#define il inline

typedef long long ll;

inline ll read()
{
    char c = getchar();
    ll s = 0;
    bool x = 0;
    while (!isdigit(c))
        x = x | (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

inline ll min(ll a, ll b) {return a < b ? a : b;}

const ll maxn = 10000 + 5, maxk = 105, inf = 1e18;
ll n, k, a[maxn], f[maxn][maxk], g[maxn][maxk];//f[i][j]：当前 i 最后一个填进去 j 的最小逆序对数
ll t[maxn][maxk], sum[maxn];//树状数组

void ins(int i, ll val)
{
    for (; val <= maxk; val += lowbit(val))
        ++t[i][val];
    return;
}

ll query(int i, ll val)//查询 [1,i] 有多少小于等于 val 的数
{
    if (!i)
        return 0;
    ll ret = 0;
    for (; val; val -= lowbit(val))
        ret += t[i][val];
    return ret;
}

il int greater(int l, int r, int val)
{
    if (l > r) return 0;
    return r - l + 1 - (query(r, val) - query(l - 1, val)) - (sum[r] - sum[l - 1]);
}

il int less(int l, int r, int val)
{
    if (l > r) return 0;
    return query(r, val - 1) - query(l - 1, val - 1);
}

int main()
{
    n = read(), k = read();
    for (int i = 1; i <= n; ++i)
    {
        a[i] = read();
        if (a[i] != -1) ins(i, a[i]);
        for (int k = 1; k <= 100; ++k)
            t[i][k] += t[i-1][k];
        sum[i] = sum[i-1] + (a[i] == -1);
    }
    memset(f, 0x3f, sizeof f);
    memset(g, 0x3f, sizeof g);
    f[0][0] = 0;
    for (int k = 0; k <= 100; ++k)
        g[0][k] = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (a[i] != -1)
        {
            for (int k = 0; k <= 100; ++k)
            {
                f[i][k] = f[i - 1][k] + greater(1, i - 1, a[i]);
                g[i][k] = min(g[i][k - 1], f[i][k]);
            }
        }
        else
        {
            f[i][0] = inf;
            for (int k = 1; k <= 100; ++k)
            {
                f[i][k] = g[i - 1][k] + greater(1, i - 1, k) + less(i + 1, n, k);
                g[i][k] = min(g[i][k - 1], f[i][k]);
            }
        }
    }
    ll ans = inf;
    for (int k = 0; k <= 100; ++k)
        ans = min(ans, f[n][k]);
    printf("%lld\n", ans);
    return 0;
}