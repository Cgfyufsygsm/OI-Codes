#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

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

int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;
int dep[maxn];

inline void add(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void dfs(int u, int fa)
{
    dep[u] = dep[fa] + 1;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v != fa) dfs(v, u);
    }
    return;
}

int main()
{
    int n = read();
    FOR(i, 1, n - 1)
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }
    dfs(1, 0);
    double ans = 0;
    FOR(i, 1, n) ans += 1.0 / double(dep[i]);
    printf("%lf\n", ans);
    return 0;
}