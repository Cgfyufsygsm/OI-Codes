#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define GO(u) for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i])

namespace fastIO {
    const int maxc = 1e7 + 5;
    char buf[maxc], *p1 = buf, *p2 = buf;
    il char getchar() {return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, maxc, stdin), p1 == p2) ? EOF : *p1++;}
    int read() {
        int s = 0, x = 0;
        char c = getchar();
        while (!isdigit(c))
            x |= (c == '-'), c = getchar();
        while (isdigit(c))
            s = s * 10 + c - '0', c = getchar();
        return x ? -s : s;
    }
}

using namespace fastIO;

typedef long long ll;
const int maxn = 150000 + 5;
int n, head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;
ll a[maxn], ans;

il ll max(ll a, ll b) {return a > b ? a : b;}

void add(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

int size[maxn], maxp[maxn], vis[maxn], tot, root;

void getrt(int u, int fa) {
    size[u] = 1;
    maxp[u] = 0;
    GO(u) {
        if (vis[v] || v == fa) continue;
        getrt(v, u);
        size[u] += size[v];
        maxp[u] = max(maxp[u], size[v]);
    }
    maxp[u] = max(maxp[u], tot - size[u]);
    if (maxp[u] < maxp[root]) root = u;
    return;
}

struct LiChaoTree {
#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)
    struct node {
        ll a, b;
    } t[maxn << 2];

    void modify(int i, int j, int k, ll a, ll b) {
        ll resu = a * M + b, resv = t[k].a * M + t[k].b;
        if (i == j) {
            if (resu > resv) t[k].a = a, t[k].b = b;
            return;
        }
        if (a > t[k].a) {
            if (resu > resv)
                modify(i, M, L, t[k].a, t[k].b), t[k].a = a, t[k].b = b;
            else modify(M + 1, j, R, a, b);
        } else if (a < t[k].a) {
            if (resu > resv)
                modify(M + 1, j, R, t[k].a, t[k].b), t[k].a = a, t[k].b = b;
            else modify(i, M, L, a, b);
        } else if (resu > resv) t[k].a = a, t[k].b = b;
        return;
    }

    ll query(int i, int j, int k, ll X) {
        if (X <= 0) return 0;
        ll ret = t[k].a * X + t[k].b;
        if (i >= j) return ret;
        if (X <= M) return max(ret, query(i, M, L, X));
        else return max(ret, query(M + 1, j, R, X));
    }

    void build(int i, int j, int k) {
        t[k].a = t[k].b = 0;
        if (i >= j) return;
        build(i, M, L);
        build(M + 1, j, R);
        return;
    }
} t;

struct node {
    ll v1, v2, s, m;
    int from;
} x[maxn];

int top, dep[maxn], maxd;

void dfs(int u, int fa, int from, ll v1, ll v2, ll s) {
    if (u != root && !from) from = u;
    dep[u] = dep[fa] + 1;
    maxd = max(dep[u], maxd);
    size[u] = 1;
    bool son = 0;
    GO(u) {
        if (v == fa || vis[v]) continue;
        son = 1;
        dfs(v, u, from, v1 + a[v] + s, v2 + dep[u] * a[v], s + a[v]);
        size[u] += size[v];
    }
    if (!son) {
        x[++top].from = from;
        x[top].v1 = v1, x[top].v2 = v2, x[top].m = dep[u], x[top].s = s - a[root];
    }
    return;
}

void calc(int u) {
    top = 0, dep[u] = 0;
    maxd = 0;
    dfs(u, 0, 0, a[u], 0, a[u]);
    x[++top].from = 0, x[top].v1 = a[u], x[top].v2 = x[top].s = 0, x[top].m = 1;
    x[top + 1].from = x[0].from = -1;
    t.build(1, maxd, 1);
    for (int i = 1; i <= top;) {
        int j = i;
        for (; x[j].from == x[i].from; ++j)
            ans = max(ans, t.query(1, maxd, 1, x[j].m) + x[j].v1);
        for (j = i; x[j].from == x[i].from; ++j)
            t.modify(1, maxd, 1, x[j].s, x[j].v2);
        i = j;
    }
    t.build(1, maxd, 1);
    for (int i = top; i >= 1;) {
        int j = i;
        for (; x[j].from == x[i].from; --j)
            ans = max(ans, t.query(1, maxd, 1, x[j].m) + x[j].v1);
        for (j = i; x[j].from == x[i].from; --j)
            t.modify(1, maxd, 1, x[j].s, x[j].v2);
        i = j;
    }
    return;
}

void solve(int u) {
    vis[u] = 1;
    calc(u);
    GO(u) {
        if (vis[v]) continue;
        maxp[0] = n, tot = size[v], root = 0;
        getrt(v, u);
        solve(root);
    }
    return;
}

int main() {
    n = read();
    FOR(i, 1, n - 1) {
        int u = read(), v = read();
        add(u, v), add(v, u);
    }
    FOR(i, 1, n) a[i] = read();
    maxp[root = 0] = tot = n;
    getrt(1, 0);
    solve(root);
    printf("%lld\n", ans);
    return 0;
}