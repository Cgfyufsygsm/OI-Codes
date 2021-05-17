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
int p[maxn], pre[maxn], suf[maxn];

int anc[maxn];

inline int find(int u) {return u == anc[u] ? u : anc[u] = find(anc[u]);}

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
    FOR(i, 1, n) p[i] = read(), head[i] = deg[i] = 0;
    FOR(i, 1, n + 1) anc[i] = i, pre[i] = suf[i] = 0;
    FOR(i, 1, n - 1)
    {
        int u = read(), v = read();
        add(u, v), add(v, u);
    }
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
        int root;
        FOR(i, 1, n) if (deg[i] == n - 1) root = i;
        FOR(i, 1, n)
        {
            int from = p[i];
            FOR(to, 1, n)
            {
                bool ok = 1;
                if (from != root && to != root)
                {
                    if (pre[to] || suf[from]) ok = 0;
                    if (find(from) == find(to) && i < n) ok = 0;
                    if (ok) pre[to] = from, suf[from] = to, anc[find(from)] = find(to);
                }
                else if (from == root && to != root)
                {
                    if (pre[to] || suf[n + 1]) ok = 0;
                    if (find(to) == find(n + 1)) ok = 0;
                    if (ok) pre[to] = n + 1, suf[n + 1] = to, anc[find(to)] = find(n + 1);
                }
                else if (from != root && to == root)
                {
                    if (suf[from] || pre[n + 1]) ok = 0;
                    if (find(from) == find(n + 1)) ok = 0; 
                    if (ok) suf[from] = n + 1, pre[n + 1] = from, anc[find(from)] = find(n + 1);
                }
                else if (from == to && from == root) ok = 0;
                if (ok)
                {
                    printf("%d ", to);
                    break;
                }
            }
        }
        puts("");
    }
    return 0;
}