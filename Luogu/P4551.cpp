#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

int read()
{
    int s = 0; int x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

inline int max(int a, int b) {return a > b ? a : b;}

const int maxn = 1e5 + 5;

int head[maxn], cnt;
struct edge
{
    int to, nxt, w;
} e[maxn << 1];

void add(int u, int v, int w)
{
    e[++cnt].to = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
    return;
}

int ch[maxn * 31 + 5][2], val[maxn * 31 + 5], tot, ans;

void insert(int x)
{
    int p = 0;
    DEC(i, 31, 0)
    {
        int now = ((x >> i) & 1);
        if (!ch[p][now])
            ch[p][now] = ++tot;
        p = ch[p][now];
    }
    val[p] = x;
    return;
}

int query(int x)
{
    int p = 0;
    DEC(i, 31, 0)
    {
        int now = (((x >> i) & 1) ^ 1);
        if (!ch[p][now])
            p = ch[p][now ^ 1];
        else p = ch[p][now];
    }
    return val[p] ^ x;
}
void dfs(int u, int fa, int dis)
{
    insert(dis);
    ans = max(ans, query(dis));
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v != fa)
            dfs(v, u, dis ^ e[i].w);
    }
    return;
}

int main()
{
    int n = read();
    FOR(i, 1, n - 1)
    {
        int u = read(), v = read(), w = read();
        add(u, v, w);
        add(v, u, w);
    }
    dfs(1, 0, 0);
    printf("%d\n", ans);
    return 0;
}