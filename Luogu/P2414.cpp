#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

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

struct node
{
    int ch[26], fail, fa;
    std::vector<int> end;
    std::vector<int> edge;
    node() {memset(ch, 0, sizeof ch);}
} t[maxn];

int pos[maxn], n, m, top, tot;
char s[maxn];

int head[maxn], to[maxn], nxt[maxn], cnte;
#define GO(u) for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i])

inline void add(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void build()
{
    static int q[maxn], head = 1, tail = 0;
    FOR(i, 0, 25)
        if (t[0].ch[i]) q[++tail] = t[0].ch[i], add(0, t[0].ch[i]);
    while (head <= tail)
    {
        int u = q[head++];
        FOR(c, 0, 25)
        {
            if (t[u].ch[c])
            {
                t[t[u].ch[c]].fail = t[t[u].fail].ch[c];
                q[++tail] = t[u].ch[c];
                add(t[t[u].ch[c]].fail, t[u].ch[c]);
            }
            else t[u].ch[c] = t[t[u].fail].ch[c];
        }
    }
    return;
}

struct req
{
    int x, id;
    req(int _x = 0, int _id = 0) : x(_x), id(_id) {}
};

std::vector<req> q[maxn];
int ans[maxn];

void init()
{
    scanf("%s", s + 1);
    int len = strlen(s + 1);
    int u = 0;
    for (int i = 1; i <= len; ++i)
    {
        if (s[i] == 'B') u = t[u].fa;
        else if (s[i] == 'P') pos[++n] = u, t[u].end.push_back(n);
        else
        {
            int c = s[i] - 'a';
            if (!t[u].ch[c]) t[u].ch[c] = ++tot, t[t[u].ch[c]].fa = u, t[u].edge.push_back(t[u].ch[c]);
            u = t[u].ch[c];
        }
    }
    m = read();
    FOR(i, 1, m)
    {
        int x = read(), y = read();
        q[y].push_back(req(x, i));
    }
    return;
}

int dfn[maxn], low[maxn], cntdfn;

struct bit
{
    int t[maxn];
#define lowbit(x) (x & -x)
    void add(int x, int v)
    {
        for (; x <= tot + 1; x += lowbit(x))
            t[x] += v;
        return;
    }
    int query(int x)
    {
        int ret = 0;
        for (; x; x -= lowbit(x))
            ret += t[x];
        return ret;
    }
    int query(int x, int y) {return query(y) - query(x - 1);}
} tree;

void getDfn(int u, int fa)
{
    dfn[u] = ++cntdfn;
    GO(u)
        getDfn(v, u);
    low[u] = cntdfn;
    return;
}

void calc(int y)
{
    FOR(i, 0, int(q[y].size()) - 1)
    {
        int x = q[y][i].x, id = q[y][i].id;
        int u = pos[x];
        ans[id] = tree.query(dfn[u], low[u]);
    }
    return;
}

void dfsTrie(int u)
{
    tree.add(dfn[u], 1);
    FOR(i, 0, int(t[u].end.size()) - 1) calc(t[u].end[i]);
    for (int i = 0; i < int(t[u].edge.size()); ++i)
        dfsTrie(t[u].edge[i]);
    tree.add(dfn[u], -1);
    return;
}

int main()
{
    init();
    build();
    getDfn(0, -1);
    dfsTrie(0);
    FOR(i, 1, m) printf("%d\n", ans[i]);
    return 0;
}