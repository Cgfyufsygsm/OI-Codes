#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

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

const int maxn = 205;
int n, m;
int f[maxn][maxn], g[maxn][maxn], match[maxn], vis[maxn], idx, to[maxn];
int ban[maxn];
int s[maxn], t[maxn];

int dfs(int u)
{
    if (ban[u]) return 0;
    for (int i = 1; i <= n; ++i)
        if (f[u][i] && vis[i] != idx && !ban[i])
        {
            vis[i] = idx;
            if (!match[i] || dfs(match[i]))
            {
                to[u] = i, match[i] = u;
                return 1;
            }
        }
    return 0;
}

void calc(int u)//进行第二问求解，构造出最大独立集
{
    if (s[u]) return;
    s[u] = 1;
    FOR(i, 1, n)
        if (f[u][i] && !t[i])
            t[i] = 1, calc(match[i]);
    return;
}

int main()
{
    n = read(), m = read();
    FOR(i, 1, m)
        g[read()][read()] = 1;
    FOR(i, 1, n) FOR(j, 1, n) FOR(k, 1, n)
        g[j][k] |= (g[j][i] & g[i][k]);//求传递闭包
    int ans = n;
    memcpy(f, g, sizeof f);
    FOR(i, 1, n) ++idx, ans -= dfs(i);
    printf("%d\n", ans);
    FOR(i, 1, n) if (!to[i]) calc(i);//从未匹配点开始匹配
    FOR(i, 1, n) printf("%d", s[i] && !t[i]);
    puts("");
    FOR(nw, 1, n)
    {
        FOR(i, 1, n) match[i] = to[i] = 0;
        int ret = 0, nn = 0;
        memset(f, 0, sizeof f);
        memset(ban, 0, sizeof ban);
        FOR(i, 1, n)
            if (g[i][nw] || g[nw][i] || i == nw) ban[i] = 1;
            else ++nn;
        ret = nn;
        FOR(i, 1, n)
            FOR(j, 1, n)
                if (!ban[i] && !ban[j]) f[i][j] = g[i][j];
        FOR(i, 1, n) if (!ban[i]) ++idx, ret -= dfs(i);
        printf("%d", ret == ans - 1);
    }
    return 0;
}