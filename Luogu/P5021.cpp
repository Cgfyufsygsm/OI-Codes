#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define GO(u) for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i])

const int maxn = 5e4 + 5;

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

int head[maxn], to[maxn << 1], nxt[maxn << 1], w[maxn << 1], cnte;

void add(int u, int v, int l)
{
    to[++cnte] = v;
    w[cnte] = l;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

int n, m, res, f[maxn];
int tmp[maxn], tot, vis[maxn << 1];

void dfs(int u, int fa, int lim)
{
    GO(u)
        if (v != fa) dfs(v, u, lim);
    tot = 0;
    GO(u)
        if (v != fa)
            tmp[++tot] = f[v] + w[i];
    std::sort(tmp + 1, tmp + tot + 1);
    DEC(i, tot, 1)
        if (tmp[i] < lim) break;
        else --tot, ++res;
    FOR(i, 1, tot)
    {
        if (vis[i] == u) continue;
        int l = i + 1, r = tot, pos = tot + 1;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (tmp[i] + tmp[mid] >= lim)
                pos = mid, r = mid - 1;
            else l = mid + 1;
        }
        while (vis[pos] == u && pos <= tot) ++pos;
        if (pos <= tot) vis[i] = vis[pos] = u, ++res;
    }
    f[u] = 0;
    DEC(i, tot, 1)
        if (vis[i] != u)
        {
            f[u] = tmp[i];
            break;
        }
    return;
}

bool check(int mid)
{
    res = 0;
    memset(vis, 0, sizeof vis);
    dfs(1, 0, mid);
    return res >= m;
}

int main()
{
    n = read(), m = read();
    int l = 1e9, r = 0;
    FOR(i, 1, n - 1)
    {
        int u = read(), v = read(), len = read();
        add(u, v, len);
        add(v, u, len);
        r += len, l = len < l ? len : l;
    }
    int ans;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid)) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}