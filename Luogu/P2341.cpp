#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 1e4 + 5, maxm = 5e4 + 5;

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

int head[maxn], to[maxm], nxt[maxm], cnt;
int dfn[maxn], dfnClock, low[maxn], bel[maxn], cntSCC, sccSize[maxn], oud[maxn];
int n, m;

il void add(int u, int v)
{
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    return;
}

int stk[maxn], top;

void tarjan(int u)
{
    dfn[u] = low[u] = ++dfnClock, stk[++top] = u;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (!dfn[v])
            tarjan(v), low[u] = min(low[u], low[v]);
        else if (!bel[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u])
    {
        sccSize[bel[u] = ++cntSCC] = 1;
        while (stk[top] != u)
            bel[stk[top--]] = cntSCC, ++sccSize[cntSCC];
        top--;
    }
    return;
}

int main()
{
    n = read(), m = read();
    while (m--)
    {
        int u = read(), v = read();
        add(u, v);
    }
    FOR(i, 1, n)
        if (!dfn[i])
            tarjan(i);
    FOR(u, 1, n)
    {
        for (int i = head[u]; i; i = nxt[i])
        {
            int v = to[i];
            if (bel[u] != bel[v])
                ++oud[bel[u]];
        }
    }
    int tmpcnt = 0, ans;
    FOR(i, 1, cntSCC)
        if (!oud[i])
            ++tmpcnt, ans = i;
    printf("%d\n", tmpcnt == 1 ? sccSize[ans] : 0);
    return 0;
}