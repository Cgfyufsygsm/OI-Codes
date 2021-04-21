#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 1000 + 5;

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

inline int max(int a, int b) {return a > b ? a : b;}

int r, c, n;

int f[maxn][maxn];
int match[maxn], to[maxn], idx, vis[maxn];
int s[maxn], t[maxn];

int dfs(int u)
{
    FOR(i, 1, c)
        if (f[u][i] && vis[i] != idx)
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

void dfs2(int u)
{
    if (s[u]) return;
    s[u] = 1;
    FOR(i, 1, c)
        if (f[u][i] && !t[i])
            t[i] = 1, dfs2(match[i]);
    return;           
}

int main()
{
    //freopen("uva.out", "w", stdout);
    r = read(), c = read(), n = read();
    while (r && c && n)
    {
        memset(f, 0, sizeof f);
        memset(match, 0, sizeof match);
        memset(to, 0, sizeof to);
        memset(s, 0, sizeof s);
        memset(t, 0, sizeof t);
        memset(vis, 0, sizeof vis);
        while (n--)
            f[read()][read()] = 1;
        int ans = 0, tot = 0;
        FOR(i, 1, r)
            ++idx, ans += dfs(i);
        printf("%d ", ans);
        FOR(i, 1, r)
            if (!to[i]) dfs2(i);
        FOR(i, 1, max(r, c))
        {
            if (!s[i] && i <= r)
            {
                printf("r%d", i);
                if (++tot < ans) putchar(' ');
            }
            if (t[i] && i <= c)
            {
                printf("c%d", i);
                if (++tot < ans) putchar(' ');
            }
        }
        puts("");
        r = read(), c = read(), n = read();
    }
    return 0;
}