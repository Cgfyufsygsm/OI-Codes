#include <iostream>
#include <cstdio>
#include <cctype>
#include <vector>
#include <string>
#include <map>
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

struct node
{
    int id, k;
};

std::vector<node> query[maxn];
int n, fa[maxn], nametot, c[maxn];
std::map<std::string, int> nameid;
int head[maxn], to[maxn], nxt[maxn], tot;
int size[maxn], son[maxn], dep[maxn], hson[maxn], h[maxn];
int ans[maxn], flag, tmp[maxn];
std::map<int, int> cnt[maxn];

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
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        dfs1(v);
        size[u] += size[v];
        if (size[v] > size[son[u]])
            son[u] = v;
        if (h[v] > h[hson[u]])
            hson[u] = v;
    }
    h[u] = h[hson[u]] + 1;
    return;
}

void calc(int u, int val)
{
    if (!cnt[dep[u]][c[u]])
        ++tmp[dep[u]];
    cnt[dep[u]][c[u]] += val;
    if (!cnt[dep[u]][c[u]])
        --tmp[dep[u]];
    for (int i = head[u], v; i; i = nxt[i])
        if ((v = to[i]) != flag)
            calc(v, val);
    return;
}

void dfs2(int u, int keep)
{
    for (int i = head[u], v; i; i = nxt[i])
        if ((v = to[i]) != son[u])
            dfs2(v, 0);
    if (son[u]) dfs2(son[u], 1);
    flag = son[u];
    calc(u, 1);
    FOR(i, 0, (int)query[u].size() - 1)
        if (query[u][i].k < h[u])
            ans[query[u][i].id] = tmp[dep[u] + query[u][i].k];
    flag = 0;
    if (!keep)
        calc(u, -1);
    return;
}

int main()
{
    n = read();
    FOR(i, 1, n)
    {
        std::string s;
        std::cin >> s >> fa[i];
        if (!nameid.count(s))
            nameid[s] = ++nametot;
        c[i] = nameid[s];
        if (fa[i]) add(fa[i], i);
    }
    int m = read();
    FOR(i, 1, m)
    {
        int u = read(), k = read();
        query[u].push_back((node){i, k});
    }
    FOR(u, 1, n)
        if (!fa[u])
            dfs1(u), dfs2(u, 0);
    FOR(i, 1, m)
        printf("%d\n", ans[i]);
    return 0;
}