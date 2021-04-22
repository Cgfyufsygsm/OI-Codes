#include <cstdio>
#include <cctype>
#define L (k << 1)
#define R (L | 1)
#define M (i + j >> 1)
#define reg register
#define il inline
#define FOR(i, a, b) for (reg int i = a; i <= b; ++i)

inline int read()
{
    char c = getchar();
    int s = 0;
    bool x = 0;
    while (!isdigit(c))
        x = x | (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

struct Matrix
{
    int r, c;
    int a[4][4];
    void clear()
    {
        FOR(i, 1, r)
            FOR(j, 1, c)
                a[i][j] = 0;
    }
    Matrix() {}
    Matrix(int _r ,int _c)
    {
        r = _r, c = _c;
        clear();
    }
    void init(int _r ,int _c)
    {
        r = _r, c = _c;
        clear();
    }
} one;

Matrix operator*(const Matrix &a, const Matrix &b)
{
    int r = a.r, c = b.c, p = a.c;
    Matrix ret(r, c);
    FOR(i, 1, r)
        FOR(j, 1, c)
            FOR(k, 1, p)
                ret.a[i][j] += a.a[i][k] * b.a[k][j];
    return ret;
}

Matrix operator+(const Matrix &a, const Matrix &b)
{
    int r = a.r, c = a.c;
    Matrix ret(r, c);
    FOR(i, 1, r)
        FOR(j, 1, c)
            ret.a[i][j] = a.a[i][j] + b.a[i][j];
    return ret;
}

const int maxn = 1e6 + 5;
int head[maxn], to[maxn << 1], nxt[maxn << 1], cntedge;
int n, m;
int fa[maxn], dep[maxn], son[maxn], size[maxn], dfn[maxn], top[maxn], cnt;

struct Segment
{
    Matrix val;
    Matrix tag;
    bool marked;
} f[maxn << 2];

void pushup(int i, int j, int k)
{
    f[k].val = f[L].val + f[R].val;
    return;
}

void pushdown(int i, int j, int k)
{
    f[L].val = f[L].val * f[k].tag;
    f[R].val = f[R].val * f[k].tag;
    f[L].tag = f[L].tag * f[k].tag;
    f[R].tag = f[R].tag * f[k].tag;
    f[L].marked |= 1, f[R].marked |= 1;
    f[k].marked = 0;
    f[k].tag = one;
    return;
}

void build(int i, int j, int k)
{
    f[k].tag = one;
    f[k].val.init(1, 3);
    f[k].val.a[1][3] = 1;
    if (i == j)
        return;
    build(i, M, L);
    build(M + 1, j, R);
    return;
}

int query(int i, int j, int k, int x)
{
    if (i == j)
        return f[k].val.a[1][2];
    if (f[k].marked)
        pushdown(i, j, k);
    if (x <= M)
        return query(i, M, L, x);
    else return query(M + 1, j, R, x);
}

void modify(int i, int j, int k, int x, int y, int d, int opt)
{
    if (x <= i && y >= j)
    {
        Matrix A = one;
        if (opt == 1)
            A.a[3][1] = d;
        else
            A.a[1][2] = d;
        f[k].tag = f[k].tag * A;
        f[k].marked = 1;
        f[k].val = f[k].val * A;
        return;
    }
    if (f[k].marked)
        pushdown(i, j, k);
    if (x <= M)
        modify(i, M, L, x, y, d, opt);
    if (y > M)
        modify(M + 1, j, R, x, y, d, opt);
    pushup(i, j, k);
    return;
}

il int query(int x)
{
    return query(1, n, 1, dfn[x]);
}

void modify(int x, int d, int opt)
{
    while (top[x] != 1)
    {
        modify(1, n, 1, dfn[top[x]], dfn[x], d, opt);
        x = fa[top[x]];
    }
    modify(1, n, 1, 1, dfn[x], d, opt);
    return;
}

void add(int u, int v)
{
    to[++cntedge] = v;
    nxt[cntedge] = head[u];
    head[u] = cntedge;
    return;
}

void dfs1(int u, int father, int depth)
{
    size[u] = 1;
    dep[u] = depth;
    fa[u] = father;
    int maxson = -1;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == father)
            continue;
        dfs1(v, u, depth + 1);
        size[u] += size[v];
        if (size[v] > maxson)
            maxson = size[v], son[u] = v;
    }
    return;
}

void dfs2(int u, int topf)
{
    dfn[u] = ++cnt;
    top[u] = topf;
    if (!son[u])
        return;
    dfs2(son[u], topf);
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa[u] || v == son[u])
            continue;
        dfs2(v, v);
    }
    return;
}

int main()
{
    one.init(3, 3);
    FOR(i, 1, 3)
        one.a[i][i] = 1;
    n = read();
    reg int u, v, opt, x;
    FOR(i, 1, n - 1)
    {
        u = read(), v = read();
        add(u, v);
        add(v, u);
    }
    dfs1(1, 0, 1);
    dfs2(1, 1);
    build(1, n, 1);
    m = read();
    FOR(i, 1, m)
    {
        opt = read(), x = read();
        if (opt < 3)
            modify(x, read(), opt);
        else if (opt == 3)
            printf("%d\n", query(x));
    }
    return 0;
}