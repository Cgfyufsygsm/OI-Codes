#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define GO(u) for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i])
#define clr(x) memset(x, 0, sizeof x)

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

inline int max(int a, int b) {return a > b ? a : b;}

struct node
{
    int id, k;
};

const int maxn = 1e5 + 5;
int n, m, head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;
int qhead[maxn], qk[maxn], qi[maxn], qnxt[maxn], cntq;

inline void add(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

int size[maxn], maxp[maxn], root, tot, vis[maxn];
int ans[maxn];
int dis[maxn];

void getrt(int u, int fa)
{
    size[u] = 1, maxp[u] = 0;
    GO(u)
    {
        if (vis[v] || v == fa) continue;
        getrt(v, u);
        size[u] += size[v];
        maxp[u] = max(maxp[u], size[v]);
    }
    maxp[u] = max(maxp[u], tot - size[u]);
    if (maxp[u] < maxp[root]) root = u;
    return;
}

int proc[maxn], rem[maxn], judge[maxn], judge1[maxn];

void getdis(int u, int fa)
{
    if (qhead[u]) proc[++proc[0]] = u;
    rem[++rem[0]] = dis[u];
    ++judge1[dis[u]];
    GO(u)
    {
        if (v == fa || vis[v]) continue;
        dis[v] = dis[u] + 1;
        getdis(v, u);
    }
    return;
}

int q[maxn];

void calc(int u)
{
    proc[0] = 0;
    int p = 0;
    GO(u)
    {
        if (vis[v]) continue;
        dis[v] = 1;
        rem[0] = 0;
        int proc0 = proc[0];
        getdis(v, u);
        int proc1 = proc[0];
        FOR(j, proc0 + 1, proc1)
        {
            int cur = proc[j];
            for (int ii = qhead[cur]; ii; ii = qnxt[ii])
            {
                int k = qk[ii];
                if (k >= dis[cur])
                    ans[qi[ii]] += judge[k - dis[cur]];
            }
        }
        FOR(j, 1, proc0)
        {
            int cur = proc[j];
            for (int ii = qhead[cur]; ii; ii = qnxt[ii])
            {
                int k = qk[ii];
                if (k >= dis[cur])
                    ans[qi[ii]] += judge1[k - dis[cur]];
            }
        }
        FOR(j, 1, rem[0])
            --judge1[rem[j]], ++judge[rem[j]], q[++p] = rem[j];
    }
    for (int i = qhead[u]; i; i = qnxt[i])
        ans[qi[i]] += judge[qk[i]];
    FOR(i, 1, p)
        --judge[q[i]];
    return;
}

void divide(int u)
{
    vis[u] = 1;
    judge[0] = 1;
    calc(u);
    GO(u)
    {
        if (vis[v]) continue;
        maxp[0] = n, tot = size[v], root = 0;
        getrt(v, u);
        divide(root);
    }
    return;
}

int main()
{
    int T = read();
    while (T--)
    {
        n = read(), m = read();
        clr(head), clr(vis), clr(qhead);
        cnte = 0, cntq = 0;
        FOR(i, 1, n - 1)
        {
            int u = read(), v = read();
            add(u, v), add(v, u);
        }
        FOR(i, 1, m)
        {
            int u = read(), k = read();
            ans[i] = 0;
            if (k)
            {
                qk[++cntq] = k;
                qi[cntq] = i;
                qnxt[cntq] = qhead[u];
                qhead[u] = cntq;
            }
            else ans[i] = 1;
        }
        tot = maxp[root = 0] = n;
        getrt(1, 0);
        divide(root);
        FOR(i, 1, m)
            printf("%d\n", ans[i]);
    }
    return 0;
}