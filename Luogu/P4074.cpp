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
    template<typename T> il void swap(T &a, T &b) {
        T t = a;
        a = b, b = t;
        return;
    }
}

using namespace fastIO;



typedef long long ll;

const int maxn = 100000 + 5;
int n, m, Q, block, a[maxn];
int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;
ll v[maxn], w[maxn];

il void addEdge(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

int dep[maxn], fa[maxn], size[maxn], son[maxn];
int st[maxn], ed[maxn], dfnClock, top[maxn], nfd[maxn << 1], bel[maxn << 1];

void dfs1(int u, int f) {
    fa[u] = f, dep[u] = dep[f] + 1, size[u] = 1;
    GO(u) {
        if (v == f) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]])
            son[u] = v;
    }
    return;
}

void dfs2(int u, int topf) {
    top[u] = topf;
    st[u] = ++dfnClock, nfd[dfnClock] = u;
    if (son[u]) dfs2(son[u], topf);
    GO(u) {
        if (v == son[u] || v == fa[u]) continue;
        dfs2(v, v);
    }
    ed[u] = ++dfnClock, nfd[dfnClock] = u;
    return;
}

int getLCA(int u, int v) {
    while (top[u] ^ top[v])
        dep[top[u]] > dep[top[v]] ? u = fa[top[u]] : v = fa[top[v]];
    return dep[u] < dep[v] ? u : v;
}

struct node1 {
    int t, l, r, lca, id;
    il bool operator<(const node1 &b) const {
        return (bel[l]) ^ (bel[b.l]) ? bel[l] < bel[b.l] : ((bel[r] ^ bel[b.r]) ? bel[r] < bel[b.r] : t < b.t);
    }
} q[maxn];

struct node2 {
    int x, val;
} c[maxn];

int cntq, cntc;

bool vis[maxn << 1];
ll cnt[maxn], ans[maxn], nowAns;

il void Add(int x) {
    vis[x] ? nowAns -= w[cnt[a[x]]--] * v[a[x]] : nowAns += w[++cnt[a[x]]] * v[a[x]];
    vis[x] ^= 1;
    return;
}

il void modify(int t) {
    if (vis[c[t].x]) {
        Add(c[t].x);
        swap(c[t].val, a[c[t].x]);
        Add(c[t].x);
    } else swap(c[t].val, a[c[t].x]);
    return;
}

int main() {
    read(n), read(m), read(Q);
    FOR(i, 1, m) read(v[i]);
    FOR(i, 1, n) read(w[i]);
    FOR(i, 1, n - 1) {
        int u, v; read(u), read(v);
        addEdge(u, v), addEdge(v, u);
    }
    FOR(i, 1, n) read(a[i]);
    dfs1(1, 0), dfs2(1, 1);
    block = pow(dfnClock, 2.0 / 3.0);
    FOR(i, 1, dfnClock) bel[i] = (i - 1) / block + 1;
    FOR(i, 1, Q) {
        int op, x, y; read(op), read(x), read(y);
        if (op == 0) {
            ++cntc;
            c[cntc].x = x, c[cntc].val = y;
        } else {
            ++cntq;
            q[cntq].id = cntq, q[cntq].t = cntc;
            if (st[x] > st[y]) swap(x, y);
            int _lca = getLCA(x, y);
            if (_lca == x) q[cntq].l = st[x], q[cntq].r = st[y];
            else q[cntq].l = ed[x], q[cntq].r = st[y], q[cntq].lca = _lca;
        }
    }
    std::sort(q + 1, q + cntq + 1);
    int now = 0, l = 1, r = 0;
    FOR(i, 1, cntq) {
        while (l > q[i].l) Add(nfd[--l]);
        while (r < q[i].r) Add(nfd[++r]);
        while (l < q[i].l) Add(nfd[l++]);
        while (r > q[i].r) Add(nfd[r--]);

        while (now < q[i].t) modify(++now);
        while (now > q[i].t) modify(now--);

        if (q[i].lca) Add(q[i].lca);
        ans[q[i].id] = nowAns;
        if (q[i].lca) Add(q[i].lca);
    }
    FOR(i, 1, cntq) print(ans[i]), putchar('\n');
    return output(), 0;
}