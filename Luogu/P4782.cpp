#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 1e6 + 5;

il int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

il int min(int a, int b) {return a < b ? a : b;}

int n, m;
int head[maxn << 1], to[maxn << 2], nxt[maxn << 2], cnte;
int dfn[maxn << 1], dfnClock, bel[maxn << 1], low[maxn << 1], cntSCC;
int stk[maxn << 1], top;

void tarjan(int u)
{
    dfn[u] = low[u] = ++dfnClock, stk[++top] = u;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (!bel[v]) low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u])
    {
        bel[u] = ++cntSCC;
        while (stk[top] != u)
            bel[stk[top--]] = cntSCC;
        --top;
    }
    return;
}

void add(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

int main()
{
    n = read(), m = read();
    while (m--)
    {
        int i = read(), a = read(), j = read(), b = read();
        add(i + (n * a), j + n * (b ^ 1));
        add(j + (n * b), i + n * (a ^ 1));
    }
    FOR(i, 1, n << 1)
        if (!dfn[i])
            tarjan(i);
    FOR(i, 1, n)
        if (bel[i] == bel[i + n])
        {
            printf("IMPOSSIBLE\n");
            return 0;
        }
    printf("POSSIBLE\n");
    FOR(i, 1, n)
        printf("%d ", bel[i] < bel[i + n]);
    return 0;
}