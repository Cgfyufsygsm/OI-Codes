#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

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

inline int min(int a, int b) {return a < b ? a : b;}

const int maxn = 1e4 + 5, Maxn = 1e6 + 5;
int n;

struct point
{
    int id, pos;
    bool operator<(const point &b)const
    {
        return pos < b.pos;
    }
    point(int pos = 0): pos(pos) {}
} a[Maxn];

int head[Maxn], to[Maxn], nxt[Maxn], cnte;
int id[Maxn], cntv;

inline int op(int x)//快速的找到对应点
{
    return (x > n) ? x - n : x + n;
}

inline void add(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

#define L (k << 1)
#define R (L | 1)
#define M ((l + r) >> 1)

void build(int k, int l, int r)//线段树建树
{
    id[k] = ++cntv;
    if (l == r)
    {
        add(id[k], op(a[l].id));//从叶子虚点向对应点连边
        return;
    }
    build(L, l, M);
    build(R, M + 1, r);
    add(id[k], id[L]);
    add(id[k], id[R]);
    return;
}

void link(int k, int l, int r, int x, int y, int p)//从 p 向 [x, y] 连边，当前在线段树上是 [l, r]
{
    if (x > y || l > r) return;
    if (l >= x && r <= y)
    {
        add(p, id[k]);
        return;
    }
    if (x <= M)
        link(L, l, M, x, y, p);
    if (y > M)
        link(R, M + 1, r, x, y, p);
    return;
}


int dfn[Maxn], low[Maxn], vis[Maxn], bel[Maxn], dfnClock, sccCnt;
int stk[Maxn], top;

void tarjan(int u)//强连通分量
{
    vis[u] = 1;
    dfn[u] = low[u] = ++dfnClock;
    stk[++top] = u;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (vis[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        ++sccCnt;
        int v;
        do
        {
            bel[v = stk[top--]] = sccCnt;
            vis[v] = 0;
        } while (v != u);
    }
    return;
}

bool check(int d)
{
    cntv = n << 1;
    memset(head, 0, sizeof head);
    cnte = 0;
    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    memset(bel, 0, sizeof bel);
    dfnClock = sccCnt = top = 0;
    //以上是清空部分，一定记得清完
    build(1, 1, n << 1);
    FOR(i, 1, n << 1)
    {
        int l = std::upper_bound(a + 1, a + (n << 1) + 1, point(a[i].pos - d)) - a;//找到左边界
        int r = std::upper_bound(a + 1, a + (n << 1) + 1, point(a[i].pos + d - 1)) - a - 1;//找右边界
        link(1, 1, n << 1, l, i - 1, a[i].id);
        link(1, 1, n << 1, i + 1, r, a[i].id);
    }
    FOR(i, 1, n << 1)
        if (!dfn[i])
            tarjan(i);
    FOR(i, 1, n)
        if (bel[i] == bel[i + n])
            return 0;
    return 1;
}

int main()
{
    n = read();
    FOR(i, 1, n)
        a[i].id = i, a[i].pos = read(), a[i + n].id = i + n, a[i + n].pos = read();
    std::sort(a + 1, a + (n << 1) + 1);//排序
    int l = 0, r = 1e9, mid, ans;
    while (l < r)//开始二分答案
    {
        mid = l + r >> 1;
        if (check(mid))
            ans = mid, l = mid + 1;
        else r = mid;
    }
    printf("%d\n", ans);
    return 0;
}