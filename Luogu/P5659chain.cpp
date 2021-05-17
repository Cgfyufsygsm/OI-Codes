#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define GO(u) for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i])
#define clr(__x) memset(__x, 0, sizeof __x)

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
int p[maxn], tag[maxn];

void add(int u, int v)
{
    ++deg[v];
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void init()
{
    n = read(), cnte = 0;
    FOR(i, 1, n) p[i] = read(), head[i] = deg[i] = tag[i] = 0;
    FOR(i, 1, n - 1)
    {
        int u = read(), v = read();
        add(u, v), add(v, u);
    }
    return;
}

int pos[maxn], id[maxn], cnt;

void dfs(int u, int fa)
{
    id[++cnt] = u, pos[u] = cnt;
    GO(u) if (v != fa) dfs(v, u);
    return;
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
        int root = 0;
        FOR(i, 1, n) if (deg[i] == 1) root = i;
        cnt = 0;
        dfs(root, 0);
        FOR(i, 1, n)
        {
            int x = p[i], b = pos[x];
            int to = n + 1;
            if (tag[b] != 1)
            {
                FOR(j, b + 1, n)
                {
                    if (tag[j] != 1) to = min(to, id[j]);
                    if (tag[j] == 2) break;
                }
            }
            if (tag[b] != 2)
            {
                DEC(j, b - 1, 1)
                {
                    if (tag[j] != 2) to = min(to, id[j]);
                    if (tag[j] == 1) break;
                }
            }
            if (pos[to] > b)
            {
                FOR(j, b + 1, pos[to] - 1) tag[j] = 1;
                tag[b] = tag[pos[to]] = 2;
            }
            else
            {
                FOR(j, pos[to] + 1, b - 1) tag[j] = 2;
                tag[b] = tag[pos[to]] = 1;
            }
            tag[1] = tag[n] = 0;
            printf("%d ", to);
        }
        puts("");
    }
    return 0;
}