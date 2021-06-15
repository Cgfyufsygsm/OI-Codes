#include <cstdio>
#include <cctype>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 5e5 + 5;

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

int n, m, Q, h[maxn], h1[maxn], toth, ans[maxn];

struct edge
{
    int a, b, c;
    il bool operator<(const edge &b) const {return c < b.c;}
} e[maxn];

struct Quest
{
    int v, x, k, id;
    il bool operator<(const Quest &b) const {return x < b.x;}
} q[maxn];

struct node
{
    int ls, rs, sum;
} t[maxn * 20];

#define L(k) t[k].ls
#define R(k) t[k].rs
#define M ((i + j) >> 1)

int stk[maxn * 30], top, cnt;

int root[maxn];

void insert(int &k, int i, int j, int pos)
{
    if (!k) k = ++cnt;
    ++t[k].sum;
    if (i == j) return;
    if (pos <= M) insert(L(k), i, M, pos);
    else insert(R(k), M + 1, j, pos);
    return;
}

int merge(int k1, int k2, int i, int j)
{
    if (!k1 || !k2) return k1 + k2;
    L(k1) = merge(L(k1), L(k2), i, M);
    R(k1) = merge(R(k1), R(k2), M + 1, j);
    t[k1].sum += t[k2].sum;
    return k1;
}

int fa[maxn], size[maxn];

il int find(int u) {return u == fa[u] ? u : fa[u] = find(fa[u]);}

void merge(int u, int v)
{
    int fu = find(u), fv = find(v);
    if (fu == fv) return;
    fa[fv] = fu;
    size[fu] += size[fv];
    root[fu] = merge(root[fu], root[fv], 1, toth);
    return;
}

int query(int k, int i, int j, int kth)
{
    if (i >= j) return i;
    if (kth <= t[R(k)].sum) return query(R(k), M + 1, j, kth);
    return query(L(k), i, M, kth - t[R(k)].sum);
}

int main()
{
    n = read(), m = read(), Q = read();
    FOR(i, 1, n) h[i] = h1[i] = read(), fa[i] = i;
    FOR(i, 1, m) e[i].a = read(), e[i].b = read(), e[i].c = read();
    FOR(i, 1, Q) q[i].id = i, q[i].v = read(), q[i].x = read(), q[i].k = read();
    std::sort(q + 1, q + Q + 1);
    std::sort(e + 1, e + m + 1);
    std::sort(h1 + 1, h1 + n + 1);
    toth = std::unique(h1 + 1, h1 + n + 1) - h1 - 1;
    FOR(i, 1, n) insert(root[i], 1, toth, std::lower_bound(h1 + 1, h1 + toth + 1, h[i]) - h1), size[i] = 1;
    int tmp = 1;
    FOR(i, 1, Q)
    {
        while (tmp <= m && e[tmp].c <= q[i].x) merge(e[tmp].a, e[tmp].b), ++tmp;
        int x = find(q[i].v);
        ans[q[i].id] = (q[i].k <= size[x] ? query(root[x], 1, toth, q[i].k) : 0);
    }
    h1[0] = -1;
    FOR(i, 1, Q) printf("%d\n", h1[ans[i]]);
    return 0;
}