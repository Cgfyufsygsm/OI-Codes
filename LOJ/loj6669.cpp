#include <cstdio>
#include <cctype>
#include <algorithm>
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

const int maxn = 3005;
int dep[maxn], n, id[maxn], fa[maxn];
int ch[maxn][2];
int size[maxn], son[maxn], bot[maxn];

int query(int u, int v)
{
    printf("? %d %d\n", u, v);
    fflush(stdout);
    return read();
}

void dfs(int u)
{
    if (ch[u][0]) dfs(ch[u][0]);
    if (ch[u][1]) dfs(ch[u][1]);
    size[u] = size[ch[u][0]] + size[ch[u][1]] + 1;
    if (ch[u][1])
        son[u] = (size[ch[u][0]] < size[ch[u][1]]);
    else son[u] = 0;
    if (ch[u][son[u]])
        bot[u] = bot[ch[u][son[u]]];
    else bot[u] = u;
}

void setfather(int u, int v)
{
    fa[v] = u;
    if (ch[u][0]) ch[u][1] = v;
    else ch[u][0] = v;
    return;
}

void solve(int u, int k)
{
    if (!ch[u][0])
    {
        setfather(u, k);
        return;
    }
    int d = query(k, bot[u]);
    int v = bot[u];
    while (dep[v] > (dep[k] + dep[bot[u]] - d) / 2) v = fa[v];
    int w = ch[v][son[v] ^ 1];
    if (w) solve(w, k);
    else setfather(v, k);
    return;
}

int main()
{
    n = read();
    FOR(i, 2, n)
    {
        dep[i] = query(1, i);
        id[i] = i;
    }
    std::sort(id + 2, id + n + 1, [](int x, int y) {return dep[x] < dep[y];});
    FOR(i, 2, n)
    {
        dfs(1);
        solve(1, id[i]);
    }
    printf("!");
    FOR(i, 2, n)
        printf(" %d", fa[i]);
    printf("\n"), fflush(stdout);
    return 0;
}