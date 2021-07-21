#include <cstdio>
#include <cctype>
#include <cmath>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
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

const int maxn = 4e4 + 5, maxm = 1e5 + 5;
int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte, block;
int a[maxn], aa[maxn], n, m, st[maxn], ed[maxn], nfd[maxn << 1], clock;

il void addEdge(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

int fa[maxn], size[maxn], son[maxn], dep[maxn], top[maxn];

void dfs1(int u, int f) {
    st[u] = ++clock, nfd[clock] = u, dep[u] = dep[f] + 1;
    fa[u] = f, size[u] = 1;
    GO(u) {
        if (v == f) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
    ed[u] = ++clock, nfd[clock] = u;
    return;
}

void dfs2(int u, int topf) {
    top[u] = topf;
    if (son[u]) dfs2(son[u], topf);
    GO(u) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
    return;
}

int getLCA(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

struct node {
    int l, r, lca, id;
    il bool operator<(const node &b) const {return ((l / block) ^ (b.l / block)) ? l < b.l : (((l / block) & 1) ? r < b.r : r > b.r);}
} q[maxm];

int cnt[maxn], used[maxn], nowAns, ans[maxm];

il void add(int x) {nowAns += !cnt[a[x]]++;}

il void del(int x) {nowAns -= !--cnt[a[x]];}

il void Add(int x) {
    used[x] ? del(x) : add(x);
    used[x] ^= 1;
    return;
}

int main() {
    read(n), read(m), block = 2 * n / sqrt(2 * m / 3);

    FOR(i, 1, n) read(aa[i]), a[i] = aa[i];
    std::sort(aa + 1, aa + n + 1);
    int tota = std::unique(aa + 1, aa + n + 1) - aa - 1;
    FOR(i, 1, n) a[i] = std::lower_bound(aa + 1, aa + tota + 1, a[i]) - aa;

    FOR(i, 1, n - 1) {
        int u, v; read(u), read(v);
        addEdge(u, v), addEdge(v, u);
    }

    dfs1(1, 0), dfs2(1, 1);

    FOR(i, 1, m) {
        int u, v; read(u), read(v);
        q[i].id = i;
        if (st[u] > st[v]) std::swap(u, v);
        int _lca = getLCA(u, v);
        if (_lca == u) q[i].l = st[u], q[i].r = st[v];
        else q[i].l = ed[u], q[i].r = st[v], q[i].lca = _lca;
    }
    std::sort(q + 1, q + m + 1);

    int l = 1, r = 0;
    FOR(i, 1, m) {
        while (l > q[i].l) Add(nfd[--l]);
        while (r < q[i].r) Add(nfd[++r]);
        while (l < q[i].l) Add(nfd[l++]);
        while (r > q[i].r) Add(nfd[r--]);

        if (q[i].lca) Add(q[i].lca);
        ans[q[i].id] = nowAns;
        if (q[i].lca) Add(q[i].lca);
    }
    FOR(i, 1, m) print(ans[i]), putchar('\n');
    return output(), 0;
}