#include <cstdio>
#include <cctype>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define GO(u) for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i])

const int maxn = 1e5 + 5;

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

int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;

il void add(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

typedef long long ll;

const ll INF = 1e15;

il ll max(ll a, ll b) {return a > b ? a : b;}

template<int row, int col>
struct Matrix
{
    ll ele[row][col];
    Matrix() {}
};

template<int m, int n, int p> Matrix<m, p> operator*(Matrix<m, n> m1, Matrix<n, p> m2)
{
    Matrix<m, p> ret;
#define RET ret.ele
#define M1 m1.ele
#define M2 m2.ele
    memset(ret.ele, 0xcf, sizeof ret.ele);
    FOR(i, 0, m - 1)
        FOR(k, 0, n - 1)
            FOR(j, 0, p - 1)
                RET[i][j] = max(RET[i][j], M1[i][k] + M2[k][j]);
    return ret;
#undef RET
#undef m1
#undef m2
}

Matrix<2, 2> ID, g[maxn];

int n, m;
ll p[maxn], sump;

int dep[maxn], fa[maxn], size[maxn], son[maxn]; 

void dfs1(int u, int f)
{
    dep[u] = dep[f] + 1, fa[u] = f, size[u] = 1;
    GO(u)
    {
        if (v == f) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
    return;
}

int top[maxn], end[maxn], dfn[maxn], nfd[maxn], dfnClock;
ll f[maxn][2];

void dfs2(int u, int topf)
{
    top[u] = topf, dfn[u] = ++dfnClock, nfd[dfnClock] = u;//记录nfd是方便下面的线段树操作
    if (!son[u])//叶子节点
    {
        f[u][1] = p[u];//f值很容易得到
        g[u] = ID;//g矩阵赋为单位矩阵
        end[u] = u;//记录链底部
        return;
    }
#define G g[u].ele
    G[1][0] = p[u], G[1][1] = -INF;//初始化g矩阵
    dfs2(son[u], topf);
    end[u] = end[son[u]];//更新链底
    GO(u)
    {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
        G[0][0] = G[0][1] += max(f[v][0], f[v][1]);//更新g
        G[1][0] += f[v][0];//更新g
    }
    f[u][0] = G[0][0] + max(f[son[u]][0], f[son[u]][1]);//利用g更新f，以计算父亲的g和f
    f[u][1] = G[1][0] + f[son[u]][0];
    return;
#undef G
}

struct node
{
    int l, r;
    Matrix<2, 2> val;
} tree[maxn << 2];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

il void pushup(int k)
{
    tree[k].val = tree[L].val * tree[R].val;
    return;
}

void build(int i, int j, int k)
{
    tree[k].l = i, tree[k].r = j;
    if (i == j)
    {
        tree[k].val = g[nfd[i]];
        return;
    }
    build(i, M, L);
    build(M + 1, j, R);
    pushup(k);
    return;
}

Matrix<2, 2> query(int k, int x, int y)
{
    int i = tree[k].l, j = tree[k].r;
    if (x <= i && y >= j) return tree[k].val;
    Matrix<2, 2> ret = ID;
    if (x <= M) ret = query(L, x, y);
    if (y > M) ret = ret * query(R, x, y);
    return ret;
}

void modify(int k, int x, int p)
{
    int i = tree[k].l, j = tree[k].r;
    if (i == j)
    {
        tree[k].val = g[p];
        return;
    }
    if (x <= M) modify(L, x, p);
    else modify(R, x, p);
    pushup(k);
    return;
}

Matrix<2, 1> query(int x)
{
    Matrix<2, 1> ret;
#define RET ret.ele
    RET[0][0] = 0, RET[1][0] = p[end[x]];
    return query(1, dfn[x], dfn[end[x]]) * ret;
#undef RET
}

void modify(int x, ll y)
{
    Matrix<2, 1> f0, f1;
#define G g[x].ele
#define F0 f0.ele
#define F1 f1.ele
    G[1][0] += y - p[x];
    f0 = query(top[x]);
    p[x] = y;
    while (x)
    {
        modify(1, dfn[x], x);
        f1 = query(top[x]);
        x = fa[top[x]];
        G[0][0] = G[0][1] += max(F1[0][0], F1[1][0]) - max(F0[0][0], F0[1][0]);
        G[1][0] += F1[0][0] - F0[0][0];
        f0 = query(top[x]);
    }
    return;
#undef G
#undef F0
#undef F1
}

int main()
{
    ID.ele[1][0] = ID.ele[0][1] = -INF;
    n = read(), m = read(), read();
    FOR(i, 1, n) p[i] = read(), sump += p[i];
    FOR(i, 1, n - 1)
    {
        int u = read(), v = read();
        add(u, v), add(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, n, 1);
    FOR(i, 1, m)
    {
        int a = read(), x = read(), b = read(), y = read();
        if (!x && !y && (fa[a] == b || fa[b] == a))
        {
            puts("-1");
            continue;
        }
        ll a0 = p[a], b0 = p[b], tmp = 0;
        if (!x) modify(a, INF), tmp += INF - a0; else modify(a, -INF);
        if (!y) modify(b, INF), tmp += INF - b0; else modify(b, -INF);
        Matrix<2, 1> ans = query(1);
#define ANS ans.ele
        printf("%lld\n", sump - max(ANS[0][0], ANS[1][0]) + tmp);
        modify(a, a0), modify(b, b0);
#undef ANS
    }
    return 0;
}