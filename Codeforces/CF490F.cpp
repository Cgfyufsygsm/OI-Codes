#include <cstdio>
#include <cctype>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 6005;

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

il int max(int a, int b) {return a > b ? a : b;}

int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;

il void add(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

int n, maxa, a0[maxn], a[maxn];

struct node
{
    int ls, rs, lis, lds;
} t[maxn * 50];

int root[maxn], cnt;
int ans = 0;

#define L(k) t[k].ls
#define R(k) t[k].rs
#define M ((i + j) >> 1)

il void pushup(int k)
{
    t[k].lis = max(t[L(k)].lis, t[R(k)].lis);
    t[k].lds = max(t[L(k)].lds, t[R(k)].lds);
    return;
}

void modify(int &k, int i, int j, int pos, int lis, int lds)
{
    if (!k) k = ++cnt;
    if (i == j)
    {
        t[k].lis = max(t[k].lis, lis);
        t[k].lds = max(t[k].lds, lds);
        return;
    }
    if (pos <= M) modify(L(k), i, M, pos, lis, lds);
    else modify(R(k), M + 1, j, pos, lis, lds);
    pushup(k);
    return;
}

void query(int k, int i, int j, int x, int y, int &lis, int &lds)//查询结尾数字在 [x, y] 的 LIS/LDS
{
    if (!k) return;
    if (x <= i && y >= j)
    {
        lis = max(lis, t[k].lis), lds = max(lds, t[k].lds);
        return;
    }
    if (x <= M) query(L(k), i, M, x, y, lis, lds);
    if (y > M) query(R(k), M + 1, j, x, y, lis, lds);
    return;
}

void merge(int &x, int y)
{
    if (!x || !y)
    {
        x |= y;
        return;
    }
    t[x].lds = max(t[x].lds, t[y].lds);
    t[x].lis = max(t[x].lis, t[y].lis);
    ans = max(ans, max(t[L(x)].lis + t[R(y)].lds, t[R(x)].lds + t[L(y)].lis));//合并的时候统计答案
    merge(L(x), L(y)), merge(R(x), R(y));
    return;
}

void dfs(int u, int fa)
{
    int mlis = 0, mlds = 0;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa) continue;
        dfs(v, u);

        int vlis = 0, vlds = 0, tmp;
        query(root[v], 1, maxa, 1, a[u] - 1, vlis, tmp);
        query(root[v], 1, maxa, a[u] + 1, maxa, tmp, vlds);

        ans = max(ans, mlis + vlds + 1);
        ans = max(ans, mlds + vlis + 1);//统计经过 u 点的路径的答案
        mlis = max(mlis, vlis), mlds = max(mlds, vlds);

        merge(root[u], root[v]);
    }
    modify(root[u], 1, maxa, a[u], mlis + 1, mlds + 1);//当然要更新一下，插入答案
    return;
}

int main()
{
    n = read();
    FOR(i, 1, n) a0[i] = a[i] = read();
    std::sort(a0 + 1, a0 + n + 1);
    maxa = std::unique(a0 + 1, a0 + n + 1) - a0 - 1;
    FOR(i, 1, n) a[i] = std::lower_bound(a0 + 1, a0 + maxa + 1, a[i]) - a0;
    FOR(i, 1, n - 1)
    {
        int u = read(), v = read();
        add(u, v), add(v, u);
    }
    FOR(i, 1, n) modify(root[i], 1, maxa, a[i], 1, 1);
    dfs(1, 0);
    printf("%d\n", ans);
    return 0;
}