#include <cstdio>
#include <cstring>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define il inline
#define lowbit(x) (x & -x)

template<typename T> il void swap(T &a, T &b)
{
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 2e6 + 5;
int n, q, tot, pos[maxn];
char s[maxn];

struct node
{
    int ch[26], end, fail;
} t[maxn];

void insert(char *s, int id)
{
    int u = 0, len = strlen(s + 1);
    FOR(i, 1, len)
    {
        int c = s[i] - 'a';
        if (!t[u].ch[c]) t[u].ch[c] = ++tot;
        u = t[u].ch[c];
    }
    pos[id] = u;
    return;
}

int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;
#define GO(u) for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i])

void addEdge(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void buildAC()
{
    static int q[maxn], head = 1, tail = 0;
    FOR(c, 0, 25)
        if (t[0].ch[c])
            q[++tail] = t[0].ch[c], addEdge(0, t[0].ch[c]);
    while (head <= tail)
    {
        int u = q[head++];
        FOR(c, 0, 25)
            if (t[u].ch[c])
                t[t[u].ch[c]].fail = t[t[u].fail].ch[c], addEdge(t[t[u].ch[c]].fail, t[u].ch[c]), q[++tail] = t[u].ch[c];
            else t[u].ch[c] = t[t[u].fail].ch[c];
    }
    return;
}

int fa[maxn], dep[maxn], size[maxn], son[maxn];
int top[maxn], dfn[maxn], low[maxn], cntdfn;

void dfs1(int u, int f)
{
    size[u] = 1, dep[u] = dep[f] + 1, fa[u] = f;
    GO(u)
    {
        if (v == f) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (!son[u] || size[v] > size[son[u]]) son[u] = v;
    }
    return;
}

void dfs2(int u, int topf)
{
    top[u] = topf, dfn[u] = ++cntdfn;
    if (son[u]) dfs2(son[u], topf);
    GO(u)
    {
        if (v == son[u] || v == fa[u]) continue;
        dfs2(v, v);
    }
    low[u] = cntdfn;
    return;
}

int getLCA(int u, int v)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

struct BIT
{
    int f[maxn];
    void modify(int x, int d)
    {
        for (; x <= cntdfn + 3; x += lowbit(x))
            f[x] += d;
        return;
    }
    int query(int x)
    {
        int ret = 0;
        for (; x; x -= lowbit(x))
            ret += f[x];
        return ret;
    }
    il int query(int x, int y) {return query(y) - query(x - 1);}
} bit;

il bool cmp(int a, int b) {return dfn[a] < dfn[b];}

void solve(char *s)
{
    static int tmp[maxn];
    int u = 0, len = strlen(s + 1), cnt = 0;
    FOR(i, 1, len)
        u = t[u].ch[s[i] - 'a'], tmp[++cnt] = u;
    std::sort(tmp + 1, tmp + cnt + 1, cmp);
    cnt = std::unique(tmp + 1, tmp + cnt + 1) - tmp - 1;
    FOR(i, 1, cnt)
    {
        bit.modify(dfn[tmp[i]], 1);
        if (i > 1) bit.modify(dfn[getLCA(tmp[i], tmp[i - 1])], -1);
    }
    return;
}

int main()
{
    scanf("%d", &n);
    FOR(i, 1, n)
    {
        scanf("%s", s + 1);
        insert(s, i);
    }
    buildAC();
    dfs1(0, -1);
    dfs2(0, 0);
    scanf("%d", &q);
    while (q--)
    {
        int op;
        scanf("%d", &op);
        if (op == 1)
            scanf("%s", s + 1), solve(s);
        else
        {
            int x;
            scanf("%d", &x);
            printf("%d\n", bit.query(dfn[pos[x]], low[pos[x]]));
        }
    }
    return 0;
}