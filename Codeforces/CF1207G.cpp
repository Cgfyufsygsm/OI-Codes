#include <cstdio>
#include <vector>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define lowbit(x) (x & -x)
#define il inline

const int maxn = 1e6 + 5;
int n, pos[maxn], tot;

struct node
{
    int ch[26], edge[26], fail;
    std::vector<int> end;
} t[maxn];

int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;

void add(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void build()
{
    static int q[maxn], head = 1, tail = 0;
    FOR(c, 0, 25)
        if (t[0].ch[c]) q[++tail] = t[0].ch[c], add(0, t[0].ch[c]);
    while (head <= tail)
    {
        int u = q[head++];
        FOR(c, 0, 25)
            if (t[u].ch[c])
                t[t[u].ch[c]].fail = t[t[u].fail].ch[c], add(t[t[u].ch[c]].fail, t[u].ch[c]), q[++tail] = t[u].ch[c];
            else t[u].ch[c] = t[t[u].fail].ch[c];
    }
    return;
}

struct req
{
    int id, u;
    req(int _id = 0, int _u = 0)  : id(_id), u(_u) {}
};

std::vector<req> q[maxn];

int ans[maxn];
char s[maxn];

int dfn[maxn], cntdfn, low[maxn];

void getDfn(int u, int fa)
{
    dfn[u] = ++cntdfn;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v != fa) getDfn(v, u);
    }
    low[u] = cntdfn;
    return;
}

struct BIT
{
    int f[maxn];
    void add(int x, int d)
    {
        for (; x <= cntdfn; x += lowbit(x))
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

void calc(int y)
{
    FOR(i, 0, int(q[y].size()) - 1)
    {
        int x = q[y][i].u, id = q[y][i].id;
        if (x == -1) continue;
        ans[id] = bit.query(dfn[x], low[x]);
    }
    return;
}

void dfsTrie(int u)
{
    bit.add(dfn[u], 1);
    FOR(i, 0, int(t[u].end.size()) - 1) calc(t[u].end[i]);
    FOR(c, 0, 25)
        if (t[u].edge[c])
            dfsTrie(t[u].edge[c]);
    bit.add(dfn[u], -1);
    return;
}

int main()
{
    scanf("%d", &n);
    char c;
    FOR(i, 1, n)
    {
        int j;
        scanf("%d", &j);
        if (j == 1)
        {
            int u = 0;
            scanf("%s", &c), c -= 'a';
            if (!t[u].ch[c]) t[u].ch[c] = t[u].edge[c] = ++tot;
            u = t[u].ch[c];
            pos[i] = u, t[u].end.push_back(i);
        }
        else 
        {
            scanf("%d %s", &j, &c);
            int u = pos[j];
            c -= 'a';
            if (!t[u].ch[c]) t[u].ch[c] = t[u].edge[c] = ++tot;
            u = t[u].ch[c];
            pos[i] = u, t[u].end.push_back(i);
        }
    }
    int m;
    scanf("%d", &m);
    FOR(i, 1, m)
    {
        int j;
        scanf("%d %s", &j, s + 1);
        int u = 0, len = strlen(s + 1);
        FOR(k, 1, len)
        {
            int c = s[k] - 'a';
            if (!t[u].ch[c]) t[u].ch[c] = ++tot;
            u = t[u].ch[c];
        }
        q[j].push_back(req(i, u));
    }
    build();
    getDfn(0, -1);
    dfsTrie(0);
    FOR(i, 1, m) printf("%d\n", ans[i]);
    return 0;
}