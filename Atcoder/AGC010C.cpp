#include <cstdio>
#include <cctype>
#include <cstdlib>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define GO(u) for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i])

const int maxn = 1e5 + 5;

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
inline int min(int a, int b) {return a < b ? a : b;}

int n, head[maxn], to[maxn << 1], nxt[maxn << 1], cnte, deg[maxn];
int a[maxn], f[maxn], root;

void add(int u, int v)
{
    ++deg[v];
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void dfs(int u, int fa)
{
    if (deg[u] == 1)
    {
        f[u] = a[u];
        return;
    }
    int s = 0, y, maxf = 0;
    GO(u)
    {
        if (v == fa) continue;
        dfs(v, u);
        s += f[v];
        maxf = max(f[v], maxf);
    }
    y = s - a[u];
    f[u] = s - 2 * y;
    if (f[u] < 0 || f[u] > a[u]) puts("NO"), exit(0);
    if (y > min(s - maxf, s / 2)) puts("NO"), exit(0);
}

int main()
{
    n = read();
    FOR(i, 1, n) a[i] = read();
    if (n == 2)
        printf("%s\n", a[1] == a[2] ? "YES" : "NO"), exit(0);
    FOR(i, 1, n - 1)
    {
        int u = read(), v = read();
        add(u, v), add(v, u);
    }
    FOR(i, 1, n)
        if (deg[root = i] > 1) break;
    dfs(root, 0);
    if (f[root] != 0) puts("NO"), exit(0);
    puts("YES");
    return 0;
}