#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

const int maxn = 2e5 + 5;

int n, head[maxn], to[maxn << 1], nxt[maxn << 1], cnt;

void add(int u, int v)
{
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    return;
}

int maxdist = 0, d1, d2;
int dis[2][maxn];

void dfs1(int u, int fa, int dist, int &d, int tag)
{
    if (dist > maxdist)
        d = u, maxdist = dist;
    if (tag > -1)
        dis[tag][u] = dist;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa) continue;
        dfs1(v, u, dist + 1, d, tag);
    }
    return;
}

int diameter[maxn], tot = 0;
long long ret = 0;

struct node
{
    int a, b, c;
    node(){}
    node(int u, int v, int w) {a = u, b = v, c = w;}
} ans[maxn];

bool dfs2(int u, int fa)
{
    bool flag = 0;
    if (u == d2)
        return diameter[++cnt] = u, 1;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa) continue;
        if (dfs2(v, u))
            diameter[++cnt] = u, flag = 1;
    }
    if (!flag)
        if (dis[0][u] > dis[1][u])
            ans[++tot] = node(u, d1, u), ret += dis[0][u];
        else
            ans[++tot] = node(u, d2, u), ret += dis[1][u];
    return flag;
}

int main()
{
    n = read();
    FOR(i, 1, n - 1)
    {
        int u = read(), v = read();
        add(u, v); add(v, u);
    }
    dfs1(1, 0, 0, d1, -1);
    maxdist = 0;
    dfs1(d1, 0, 0, d2, 0);
    dfs1(d2, 0, 0, d1, 1);
    cnt = 0;
    dfs2(d1, 0);
    FOR(i, 1, cnt - 1)
        ans[++tot] = node(diameter[i], d1, diameter[i]), ret += dis[0][diameter[i]];
    printf("%lld\n", ret);
    FOR(i, 1, tot)
        printf("%d %d %d\n", ans[i].a, ans[i].b, ans[i].c);
    return 0;
}