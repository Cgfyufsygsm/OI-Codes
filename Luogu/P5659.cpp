#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define GO(u) for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i])

const int maxn = 2e3 + 5;

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

inline int min(int a, int b) {return a < b ? a : b;}

int n, head[maxn], to[maxn << 1], nxt[maxn << 1], cnte, deg[maxn];
int p[maxn];

void add(int u, int v)
{
    ++deg[v];
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

struct node
{
    int fi, la;
    int pre[maxn], suf[maxn], anc[maxn];
    void clear()
    {
        fi = la = 0;
        FOR(i, 1, n) pre[i] = suf[i] = anc[i] = 0, anc[i] = i;
    }
    int find(int u) {return anc[u] == u ? u : anc[u] = find(anc[u]);}
    bool ask(int u, int v) {return find(u) == find(v);}
    void uni(int u, int v) {if (!ask(u, v)) anc[find(v)] = find(u);}
} t[maxn];

void init()
{
    n = read();
    FOR(i, 1, n) p[i] = read(), head[i] = deg[i] = 0, t[i].clear();
    cnte = 1;
    FOR(i, 1, n - 1)
    {
        int u = read(), v = read();
        add(u, v), add(v, u);
    }
}

int dfs(int u, int fa)
{
    int res = n + 1;
    if (fa != n + 1 && !t[u].la && !t[u].suf[fa] && !(t[u].fi && deg[u] > 1 && t[u].ask(fa, t[u].fi))) res = u;
    //判断作为结束点。首先结束边不能确定过，而且 fa 不能有后继边
    //后面一句是判断提前自闭的情况，因为如果确定它为结束边，且它与起始边相连，则可能中间会有没有考虑到的边
    GO(u)
    {
        if (v == fa) continue;
        if (fa == n + 1)//u 为起始点
        {
            if (!t[u].fi)//首先初始边不能已经指定过
            {
                if (t[u].pre[v]) continue;//v边也不能有前驱
                if (t[u].la && deg[u] > 1 && t[u].ask(v, t[u].la)) continue;//提前自闭的情况
                res = min(res, dfs(v, u));
            }
            else continue;
        }
        else
        {
            if (t[u].fi == v || t[u].la == fa || t[u].ask(v, fa)) continue;//初始边肯定不能接在结束边后，而且这两条边不能已经连起来
            if (t[u].pre[v] || t[u].suf[fa]) continue;//如果不能接起来
            if (t[u].fi && t[u].la && deg[u] > 2 && t[u].ask(t[u].fi, fa) && t[u].ask(t[u].la, v)) continue;//两者接起来之后不能提前自闭
            res = min(res, dfs(v, u));
        }
    }
    return res;
}

bool update(int u, int fa, int dest)
{
    if (u == dest)
    {
        t[u].la = fa;
        return true;
    }
    GO(u)
    {
        if (v == fa) continue;
        if (update(v, u, dest))
        {
            if (fa == n + 1)
                t[u].fi = v;
            else
                t[u].uni(fa, v), t[u].suf[fa] = v, t[u].pre[v] = fa, --deg[u];
            return true;
        }
    }
    return false;
}

int main()
{
    int T = read();
    while (T--)
    {
        init();
        if (n == 1)
        {
            printf("1\n");
            continue;
        }
        FOR(i, 1, n)
        {
            int ans = dfs(p[i], n + 1);
            update(p[i], n + 1, ans);
            printf("%d ", ans);
        }
        puts("");
    }
    return 0;
}