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
    void readC(char &x) {
        char c = getchar();
        while (!isalpha(c)) c = getchar();
        x = c;
        return;
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

const int maxn = 8e4 + 5;
int n, m, q, tota;
int a[maxn], aa[maxn];
int bel[maxn], size[maxn], fa[maxn][18], dep[maxn];
int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;

void addEdge(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

il int find(int u) {return u == bel[u] ? u : bel[u] = find(bel[u]);}

struct node {
    int sum, ls, rs;
    node() {sum = ls = rs = 0;}
} t[maxn * 500];

int root[maxn], cnt;

#define ls(k) t[k].ls
#define rs(k) t[k].rs
#define M ((i + j) >> 1)

int clone(int k) {
    t[++cnt] = t[k];
    return cnt;
}

int insert(int k, int i, int j, int x) {
    k = clone(k);
    ++t[k].sum;
    //printf("k %d [%d, %d] = %d\n", k, i, j, t[k].sum);
    if (i == j) return k;
    if (x <= M) ls(k) = insert(ls(k), i, M, x);
    else rs(k) = insert(rs(k), M + 1, j, x);
    return k;
}

void dfs(int u, int f, int rt) {
    bel[u] = rt;
    fa[u][0] = f;
    ++size[rt], dep[u] = dep[f] + 1;
    FOR(j, 1, 17) fa[u][j] = fa[fa[u][j - 1]][j - 1];
    //printf("rt %d, now %d\n", rt, u);
    root[u] = insert(root[f], 1, tota, a[u]);
    GO(u) {
        if (v == f) continue;
        dfs(v, u, rt);
    }
    return;
}

int getLCA(int u, int v) {
    if (u == v) return u;
    if (dep[u] > dep[v]) std::swap(u, v);
    DEC(k, 17, 0)
        if (dep[fa[v][k]] >= dep[u]) v = fa[v][k];
    if (u == v) return u;
    DEC(k, 17, 0)
        if (fa[u][k] != fa[v][k]) u = fa[u][k], v = fa[v][k];
    return fa[u][0];
}

int query(int k, int u1, int u2, int k1, int k2, int i, int j) {
    if (i == j) return aa[i];
    int sum = t[ls(u1)].sum + t[ls(u2)].sum - t[ls(k1)].sum - t[ls(k2)].sum;
    if (sum < k) return query(k - sum, rs(u1), rs(u2), rs(k1), rs(k2), M + 1, j);
    else return query(k, ls(u1), ls(u2), ls(k1), ls(k2), i, M);
}

int main() {
    read(n);
    read(n), read(m), read(q);
    FOR(i, 1, n) read(a[i]), aa[i] = a[i];
    std::sort(aa + 1, aa + n + 1);
    tota = std::unique(aa + 1, aa + n + 1) - aa - 1;
    FOR(i, 1, n) a[i] = std::lower_bound(aa + 1, aa + n + 1, a[i]) - aa;

    FOR(i, 1, m) {
        int u, v; read(u), read(v);
        addEdge(u, v), addEdge(v, u);
    }

    FOR(i, 1, n) if (!bel[i]) dfs(i, 0, i);

    int last = 0;
    while (q--) {
        char c; readC(c);
        int u, v; read(u), read(v), u ^= last, v ^= last;
        if (c == 'Q') {
            int k; read(k), k ^= last;
            int lca = getLCA(u, v);
            print(last = query(k, root[u], root[v], root[lca], root[fa[lca][0]], 1, tota)), putchar('\n');
        } else {
            addEdge(u, v), addEdge(v, u);
            int ru = find(u), rv = find(v);
            if (size[ru] < size[rv]) std::swap(ru, rv), std::swap(u, v);
            dfs(v, u, ru);
        }
    }
    return output(), 0;
}