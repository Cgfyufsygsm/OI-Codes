#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define debug(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

namespace YangTY {

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T, typename...Args> il T max(const T &a, const Args&... args) {
    T res = max(args...);
    return max(a, res);
}
template<typename T, typename...Args> il T min(const T &a, const Args&... args) {
    T res = min(args...);
    return min(a, res);
}
template<typename T> il T chkmax(T &a, const T &b) {return a = (b > a ? b : a);}
template<typename T> il T chkmin(T &a, const T &b) {return a = (b < a ? b : a);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

using fastIO::is;
using fastIO::os;
const int maxn = 80005;
int n, m;
int dfn[maxn], nfd[maxn], size[maxn], son[maxn], top[maxn], fa[maxn], dep[maxn], dfnTot;
int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;

void add(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void dfs1(int u, int pre) {
    fa[u] = pre, dep[u] = dep[pre] + 1, size[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int &v = to[i];
        if (v == fa[u]) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
    return;
}

void dfs2(int u, int topf) {
    top[u] = topf, dfn[u] = ++dfnTot, nfd[dfnTot] = u;
    if (son[u]) dfs2(son[u], topf);
    for (int i = head[u]; i; i = nxt[i]) {
        int &v = to[i];
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
    return;
}

int t[maxn << 2];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void modify(int i, int j, int k, int x, int v) {
    t[k] += v;
    if (i == j) return;
    if (x <= M) modify(i, M, L, x, v);
    else modify(M + 1, j, R, x, v);
    return;
}

int query(int i, int j, int k, int x, int y) {
    if (x > y) return 0;
    if (x <= i && y >= j) return t[k];
    int ret = 0;
    if (x <= M) ret += query(i, M, L, x, y);
    if (y > M) ret += query(M + 1, j, R, x, y);
    return ret;
}

int query(int x, int y) {
    int ret = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        ret += query(1, n, 1, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    ret += query(1, n, 1, dfn[x], dfn[y]);
    return ret;
}

int getLCA(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}

int a[maxn], totq, ans[maxn];

struct Query {
    int type, id, x, y, k;
} q[maxn << 1], q1[maxn << 1], q2[maxn << 1];

void solve(int l, int r, int ql, int qr) {
    if (l > r || ql > qr) return;
    if (l == r) {
        FOR(i, ql, qr) if (!q[i].type) ans[q[i].id] = l;
        return;
    }
    int cnt1 = 0, cnt2 = 0, mid = (l + r) >> 1;
    FOR(i, ql, qr) {
        if (!q[i].type) {
            int res = query(q[i].x, q[i].y);
            if (q[i].k <= res) q2[++cnt2] = q[i];
            else {
                q[i].k -= res;
                q1[++cnt1] = q[i];
            }
        } else {
            if (q[i].k > mid) {
                modify(1, n, 1, dfn[q[i].x], q[i].type);
                q2[++cnt2] = q[i];
            } else q1[++cnt1] = q[i];
        }
    }
    FOR(i, 1, cnt2) if (q2[i].type != 0) modify(1, n, 1, dfn[q2[i].x], -q2[i].type);
    FOR(i, 1, cnt1) q[ql + i - 1] = q1[i];
    FOR(i, 1, cnt2) q[ql + cnt1 + i - 1] = q2[i];
    solve(l, mid, ql, ql + cnt1 - 1);
    solve(mid + 1, r, ql + cnt1, qr);
    return;
}

int main() {
    is >> n >> m;
    FOR(i, 1, n) is >> a[i], q[++totq] = {1, -1, i, -1, a[i]};
    FOR(i, 1, n - 1) {
        int x, y; is >> x >> y;
        add(x, y), add(y, x);
    }
    dfs1(1, 0), dfs2(1, 1);
    memset(ans, -1, sizeof ans);
    FOR(i, 1, m) {
        int k, x, y; is >> k >> x >> y;
        if (!k) {
            q[++totq] = {-1, -1, x, -1, a[x]};
            q[++totq] = {1, -1, x, -1, a[x] = y};
        } else {
            int len = dep[x] + dep[y] - 2 * dep[getLCA(x, y)] + 1;
            if (k > len) ans[i] = -2;
            else q[++totq] = {0, i, x, y, k};
        }
    }
    solve(0, 1e8, 1, totq);
    FOR(i, 1, m) if (ans[i] != -1) {
        if (ans[i] == -2) os << "invalid request!\n";
        else os << ans[i] << '\n';
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}