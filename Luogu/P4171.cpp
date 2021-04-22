#include <iostream>
#include <cstring>
#include <string>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

using namespace std;

const int maxn = 505, maxm = 10005;

int head[maxn], to[maxm], nxt[maxm], cnt;
int dfn[maxn], low[maxn], dfnClock, cntSCC, bel[maxn];
int n, m;

void add(int u, int v)
{
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    return;
}

int stk[maxn], top;

void tarjan(int u)
{
    stk[++top] = u;
    dfn[u] = low[u] = ++dfnClock;
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
        bel[u] = ++cntSCC;
        while (stk[top] != u)
            bel[stk[top--]] = cntSCC;
        --top;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n >> m;
        memset(head, 0, sizeof head);
        memset(dfn, 0, sizeof dfn);
        memset(low, 0, sizeof low);
        memset(bel, 0, sizeof bel);
        dfnClock = cnt = 0;
        while (m--)
        {
            char cx, cy;
            int x, y, xx, yy;
            cin >> cx >> x >> cy >> y;
            xx = (cx == 'm'), yy = (cy == 'm');
            add(x + n * (xx ^ 1), y + n * yy);
            add(y + n * (yy ^ 1), x + n * xx);
        }
        FOR(i, 1, n << 1)
            if (!dfn[i])
                tarjan(i);
        bool flag = 1;
        FOR(i, 1, n)
            if (bel[i] == bel[i + n])
            {
                flag = 0;
                break;
            }
        if (flag) cout << "GOOD\n";
        else cout << "BAD\n";
    }
    return 0;
}