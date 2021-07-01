#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 55;

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

typedef long long ll;

il ll max(ll a, ll b) {return a > b ? a : b;}
il ll min(ll a, ll b) {return a < b ? a : b;}

int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;

void add(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

int n, X, D;

struct node
{
    int id, v;
    ll w;
} a[maxn];

il bool operator<(const node &a, const node &b)
{
    return a.v * b.w > b.v * a.w;
}

void dfs(int u)
{
    a[u].v = 1, a[u].id = u;
    for (int i = head[u]; i; i = nxt[i])
        dfs(to[i]), a[u].v += a[to[i]].v, a[u].w += a[to[i]].w;
    return;
}

ll dp[maxn * maxn * maxn];

int main()
{
    n = read(), X = read(), D = read();
    a[1].w = read();
    FOR(i, 2, n)
        a[i].w = read(), add(read(), i);
    dfs(1);
    memset(dp, 0x3f, sizeof dp);
    dp[0] = 0;
    int mx = n * n * n, L = min(n, D);

    FOR(i, 1, n)
    {
        int x = L;
        for (int j = 0; 1 << j <= x; ++j)
        {
            int v = a[i].v * (1 << j); ll w = a[i].w * (1 << j);
            DEC(k, mx, v) dp[k] = min(dp[k], dp[k - v] + w);
            x -= (1 << j);
        }
        if (x)
        {
            int v = a[i].v * x; ll w = a[i].w * x;
            DEC(k, mx, v) dp[k] = min(dp[k], dp[k - v] + w);
        }
    }
    
    std::sort(a + 1, a + n + 1);
    while (a[n].id != 1) --n;
    ll ans = 0;
    FOR(i, 0, mx)
    {
        if (dp[i] > X) continue;
        ll v = i, w = dp[i];
        FOR(j, 1, n - 1)
        {
            ll c = min((ll)D - L, (X - w) / a[j].w);
            v += c * a[j].v, w += c * a[j].w;
        }
        ll c = (X - w) / a[n].w;
        w += c * a[n].w, v += c * a[n].v;
        ans = max(v, ans);
    }
    printf("%lld\n", ans);
    return 0;
}