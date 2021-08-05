#include <cstdio>
#include <cctype>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define GO(u) for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i])

namespace fastIO {
    const int maxc = 1 << 21;
    char ibuf[maxc], *__p1 = ibuf, *__p2 = ibuf;
    il char getchar() {return __p1 == __p2 && (__p2 = (__p1 = ibuf) + fread(ibuf, 1, maxc, stdin), __p1 == __p2) ? EOF : *__p1++;}
    template<typename T> void read(T &n) {
        int x = 0; n = 0;
        char c = getchar();
        while (!isdigit(c))
            x |= (c == '-'), c = getchar();
        while (isdigit(c))
            n = n * 10 + c - '0', c = getchar();
        n = x ? -n : n;
    }
    char obuf[maxc], *__pO = obuf;
    il void putchar(char c) {*__pO++ = c;}
    template<typename T> void print(T x) {
        if (x < 0) putchar('-'), print(-x);
        else {
            if (x > 9) print(x / 10);
            putchar(x % 10 + '0');
        }
        return;
    }
    void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
}

using namespace fastIO;

const int maxn = 1e5 + 5;
int n, m, tot;
int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;
int a[maxn], aa[maxn];

struct node {
    int sum, ls, rs;
    node() {sum = ls = rs = 0;}
} t[maxn * 40];

int root[maxn];

il int clone(int k) {
    static int cnt = 0;
    t[++cnt] = t[k];
    return cnt;
}

#define ls(k) (t[k].ls)
#define rs(k) (t[k].rs)
#define M ((i + j) >> 1)

int insert(int k, int i, int j, int x) {
    k = clone(k);
    ++t[k].sum;
    if (i == j) return k;
    if (x <= M) ls(k) = insert(ls(k), i, M, x);
    else rs(k) = insert(rs(k), M + 1, j, x);
    return k;
}

il void addEdge(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

int fa[maxn], dep[maxn], size[maxn], top[maxn], son[maxn];

void dfs1(int u, int f) {
    dep[u] = dep[f] + 1, fa[u] = f, size[u] = 1;
    root[u] = insert(root[f], 1, tot, a[u]);
    GO(u) {
        if (v == f) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
    return;
}

void dfs2(int u, int topf) {
    top[u] = topf;
    if (!son[u]) return;
    dfs2(son[u], topf);
    GO(u) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
    return;
}

int getLCA(int u, int v) {
    while (top[u] != top[v])
        dep[top[u]] > dep[top[v]] ? u = fa[top[u]] : v = fa[top[v]];
    return dep[u] < dep[v] ? u : v;
}

int query(int k, int u1, int u2, int k1, int k2, int i, int j) {
    if (i == j) return aa[i];
    int sum = t[ls(u1)].sum + t[ls(u2)].sum - t[ls(k1)].sum - t[ls(k2)].sum;
    if (sum < k) return query(k - sum, rs(u1), rs(u2), rs(k1), rs(k2), M + 1, j);
    else return query(k, ls(u1), ls(u2), ls(k1), ls(k2), i, M);
}

int main() {
    read(n), read(m);

    FOR(i, 1, n) read(a[i]), aa[i] = a[i];
    std::sort(aa + 1, aa + n + 1);
    tot = std::unique(aa + 1, aa + n + 1) - aa - 1;
    FOR(i, 1, n) a[i] = std::lower_bound(aa + 1, aa + tot + 1, a[i]) - aa;

    FOR(i, 1, n - 1) {
        int u, v; read(u), read(v);
        addEdge(u, v), addEdge(v, u);
    }

    dfs1(1, 0), dfs2(1, 1);

    int last = 0;
    while (m--) {
        int u, v, k; read(u), read(v), read(k), u ^= last;
        int lca = getLCA(u, v);
        print(last = query(k, root[u], root[v], root[lca], root[fa[lca]], 1, tot)), putchar('\n');
    }
    return output(), 0;
}