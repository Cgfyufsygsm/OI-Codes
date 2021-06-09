#include <cstdio>
#include <cctype>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define GO(u) for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i])

const int maxn = 1e5 + 5, INF = 0x3f3f3f3f;

int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;

il void add(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

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

template<int row, int col>
struct Matrix
{
    int ele[row][col];
    il int &operator()(int a, int b) {return ele[a][b];}
};

template<int m, int n, int p> Matrix<m, p> operator*(Matrix<m, n> m1, Matrix<n, p> m2)
{
    Matrix<m, p> ret;
    memset(ret.ele, 0xcf, sizeof ret.ele);
    FOR(i, 0, m - 1)
        FOR(k, 0, n - 1)
            FOR(j, 0, p - 1)
                ret(i, j) = max(ret(i, j), m1(i, k) + m2(k, j));
    return ret;
}

Matrix<2, 2> ID, g[maxn];

int n, m, val[maxn];

int fa[maxn], dep[maxn], size[maxn], son[maxn];

void dfs1(int u, int f)
{
    fa[u] = f, size[u] = 1, dep[u] = dep[f] + 1;
    GO(u)
    {
        if (v == f) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
    return;
}

//正常的树剖dfs1

int dfnClock, dfn[maxn], nfd[maxn], top[maxn], end[maxn];
int f[maxn][2];

void dfs2(int u, int topf)
{
    top[u] = topf, dfn[u] = ++dfnClock, nfd[dfnClock] = u;//记录nfd是方便下面的线段树操作
    if (!son[u])//叶子节点
    {
        f[u][1] = val[u];//f值很容易得到
        g[u] = ID;//g矩阵赋为单位矩阵
        end[u] = u;//记录链底部
        return;
    }
    g[u](1, 0) = val[u], g[u](1, 1) = -INF;//初始化g矩阵
    dfs2(son[u], topf);
    end[u] = end[son[u]];//更新链底
    GO(u)
    {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
        g[u](0, 0) = g[u](0, 1) += max(f[v][0], f[v][1]);//更新g
        g[u](1, 0) += f[v][0];//更新g
    }
    f[u][0] = g[u](0, 0) + max(f[son[u]][0], f[son[u]][1]);//利用g更新f，以计算父亲的g和f
    f[u][1] = g[u](1, 0) + f[son[u]][0];
    return;
}

struct node
{
    int l, r;//不记录l和r的话对于查询区间为[0,0] 的情况会死循环
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
        tree[k].val = g[nfd[i]];//此处即为nfd的作用
        return;
    }
    build(i, M, L);
    build(M + 1, j, R);
    pushup(k);
    return;
}

Matrix<2, 2> query(int k, int x, int y)//查询操作，查询[x, y] 的矩阵连乘积
{
    int i = tree[k].l, j = tree[k].r;
    if (x <= i && y >= j) return tree[k].val;
    Matrix<2, 2> ret = ID;
    if (x <= M) ret = query(L, x, y);
    if (y > M) ret = ret * query(R, x, y);//注意乘的先后
    return ret;
}

void modify(int k, int x, int p)//把线段树 x 点上的值赋为 p 的矩阵
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

Matrix<2, 1> query(int x)//查询 x 点的 dp 值
{
    Matrix<2, 1> tmp;
    tmp(0, 0) = 0, tmp(1, 0) = val[end[x]];//最右边，初始化
    return query(1, dfn[x], dfn[end[x]]) * tmp;//连乘给上去
}

void modify(int x, int y)//将 x 的点权修改为 y
{
    Matrix<2, 1> F0, F1;
    g[x](1, 0) += y - val[x];
    F0 = query(top[x]);
    val[x] = y;
    while (x)
    {
        modify(1, dfn[x], x);//把线段树上修改了
        F1 = query(top[x]);
        x = fa[top[x]];
        g[x](0, 0) = g[x](0, 1) += max(F1(0, 0), F1(1, 0)) - max(F0(0, 0), F0(1, 0));
        g[x](1, 0) += F1(0, 0) - F0(0, 0);
        F0 = query(top[x]);
    }
    return;
}

int main()
{
    ID(1, 0) = ID(0, 1) = -INF;//单位矩阵
    n = read(), m = read();
    FOR(i, 1, n) val[i] = read();
    FOR(i, 1, n - 1)
    {
        int u = read(), v = read();
        add(u, v), add(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, n, 1);
    while (m--)
    {
        int x = read(), y = read();
        modify(x, y);
        Matrix<2, 1> ans = query(1);
        printf("%d\n", max(ans(0, 0), ans(0, 1)));
    }
    return 0;
}