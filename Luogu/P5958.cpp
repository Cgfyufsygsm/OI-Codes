#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

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

const int maxn = 500000 + 5;
typedef double db;

inline db max(db a, db b) {return a > b ? a : b;}
inline db min(db a, db b) {return a < b ? a : b;}

db f[maxn], ans = 0;
int size[maxn], n, k;

int head[maxn], to[maxn], nxt[maxn], cnt;

void add(int u, int v)
{
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    return;
}

void dfs(int u)
{
    size[u] = 1;
    for (int i = head[u], v; i; i = nxt[i])
    {
        dfs(v = to[i]);
        size[u] += size[v];
    }
    if (size[u] == 1)
    {
        f[u] = 1;
        return;
    }
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        f[u] = max(f[u], min(f[v], (size[v] * 1.0) / (size[u] - 1.0)));
    }
    if (size[u] > k)
        ans = max(ans, f[u]);
    return;
}

int main()
{
    n = read(), k = read();
    FOR(v, 2, n)
        add(read(), v);
    dfs(1);
    printf("%.8lf\n", ans);
    return 0;
}