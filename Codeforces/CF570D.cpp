#include <cstdio>
#include <cctype>
#include <vector>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 5e5 + 5;

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

char s[maxn];
int n, m;
int head[maxn], to[maxn], nxt[maxn], tot;
int size[maxn], dep[maxn], fa[maxn], son[maxn];
bool ans[maxn];

struct node
{
    int i, dep;
    node() {}
    node(int id, int k) {i = id, dep = k;}
};

std::vector<node> query[maxn];

inline void add(int u, int v)
{
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
    return;
}

void dfs1(int u)
{
    size[u] = 1, dep[u] = dep[fa[u]] + 1;
    int maxson = -1;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        dfs1(v);
        size[u] += size[v];
        if (size[v] > maxson)
            maxson = size[v], son[u] = v;
    }
    return;
}

int flag, cnt[maxn][26];

void calc(int u, int val)
{
    cnt[dep[u]][s[u] - 'a'] += val;
    for (int i = head[u]; i; i = nxt[i])
        if (to[i] != flag)
            calc(to[i], val);
    return;
}

bool check(int dep)
{
    int ret = 0;
    FOR(i, 0, 25)
    {
        ret += (cnt[dep][i] & 1);
        if (ret > 1) return 0;
    }
    return 1;
}

void dfs2(int u, int keep)
{
    for (int i = head[u]; i; i = nxt[i])
        if (to[i] != son[u])
            dfs2(to[i], 0);
    if (son[u]) dfs2(son[u], 1), flag = son[u];
    calc(u, 1);
    flag = 0;
    for (int i = 0; i < query[u].size(); ++i)
        ans[query[u][i].i] = check(query[u][i].dep);
    if (!keep) calc(u, -1);
    return;
}

int main()
{
    n = read(), m = read();
    FOR(i, 2, n)
        add(fa[i] = read(), i);
    scanf("%s", s + 1);
    FOR(i, 1, m)
    {
        int u = read(), k = read();
        query[u].push_back(node(i, k));
    }
    dfs1(1);
    dfs2(1, 1);
    FOR(i, 1, m)
        printf("%s\n", ans[i] ? "Yes" : "No");
    return 0;
}