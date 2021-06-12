#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 1e6 + 5;

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

template<typename T> inline void swap(T &a, T &b)
{
    T t = a;
    a = b, b = t;
    return;
}

char s[maxn];
int fail[maxn], n;

int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;

#define GO(u) for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i])

void add(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

int fa[maxn], son[maxn], size[maxn], dep[maxn], top[maxn];

void dfs1(int u, int f)
{
    dep[u] = dep[f] + 1, size[u] = 1, fa[u] = f;
    int tmp = -1;
    GO(u)
    {
        if (v == f) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > tmp) son[u] = v, tmp = size[v];
    }
    return;
}

void dfs2(int u, int topf)
{
    top[u] = topf;
    if (son[u]) dfs2(son[u], topf);
    GO(u)
    {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
    return;
}

int lca(int u, int v)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

int main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    add(0, 1), add(1, 0), fail[1] = 0;
    for (int i = 2, j = 0; i <= n; ++i)
    {
        while (j && s[j + 1] != s[i]) j = fail[j];
        if (s[j + 1] == s[i]) ++j;
        fail[i] = j;
        add(fail[i], i), add(i, fail[i]);
    }
    dfs1(0, -1);
    dfs2(0, 0);
    int m = read();
    while (m--)
    {
        int p = read(), q = read();
        int tmp = lca(p, q);
        if (tmp == p || tmp == q) tmp = fa[tmp];
        printf("%d\n", tmp);
    }
    return 0;
}