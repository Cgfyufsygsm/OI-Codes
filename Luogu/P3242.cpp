#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define szof(a) ((int) (a).size())
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define fileIn(s) freopen(s, "r", stdin)
#define fileOut(s) freopen(s, "w", stdout)
#define clr(f, n) memset(f, 0, (sizeof(int)) * (n))
#define cpy(f, g, n) memcpy(f, g, (sizeof(int)) * (n))

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
const int maxn = 4e4 + 5;
int n, p, m, tot;
vector<int> G[maxn];
int fa[maxn], son[maxn], top[maxn], size[maxn], st[maxn], ed[maxn], dep[maxn], dfnClock;
int org[maxn], ans[maxn];

struct Query {
    int type, t, x, y, k, sgn, id; // 种类，时间戳，[x, y]，加 k
} q[maxn * 7], q1[maxn * 7], q2[maxn * 7];

void dfs1(int u, int pre) {
    fa[u] = pre, dep[u] = dep[pre] + 1, size[u] = 1;
    for (auto &v : G[u]) if (v != pre) {
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
    return;
}

void dfs2(int u, int topf) {
    top[u] = topf, st[u] = ++dfnClock;
    if (son[u]) dfs2(son[u], topf);
    for (auto &v : G[u]) if (v != son[u] && v != fa[u]) dfs2(v, v);
    ed[u] = dfnClock;
    return;
}

int getLCA(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

int getSon(int rt, int x) {
    while (top[rt] != top[x]) {
        if (fa[top[x]] == rt) return top[x];
        x = fa[top[x]];
    }
    return son[rt];
}

struct BIT {
    int t[maxn];
    #define lowbit(x) (x & -x)
    void add(int x, int c) {
        for (; x <= n; x += lowbit(x)) t[x] += c;
        return;
    }
    void modify(int x, int y, int c) {return add(x, c), add(y + 1, -c);}
    int query(int x) {
        int ret = 0;
        for (; x; x -= lowbit(x)) ret += t[x];
        return ret;
    }
} tree;

void solve(int l, int r, int ql, int qr) {
    if (l > r || ql > qr) return;
    if (l == r) {
        FOR(i, ql, qr) if (q[i].type == 2) ans[q[i].id] = l;
        return;
    }
    int mid = (l + r) >> 1, cnt1 = 0, cnt2 = 0;
    FOR(i, ql, qr) {
        if (q[i].type == 1) {
            if (q[i].k <= mid) {
                tree.modify(q[i].x, q[i].y, q[i].sgn);
                q1[++cnt1] = q[i];
            } else q2[++cnt2] = q[i];
        } else {
            int res = tree.query(q[i].x);
            if (q[i].k <= res) q1[++cnt1] = q[i];
            else {
                q[i].k -= res;
                q2[++cnt2] = q[i];
            }
        }
    }
    FOR(i, 1, cnt1) if (q1[i].type == 1) tree.modify(q1[i].x, q1[i].y, -q1[i].sgn);
    FOR(i, 1, cnt1) q[ql + i - 1] = q1[i];
    FOR(i, 1, cnt2) q[ql + cnt1 + i - 1] = q2[i];
    return solve(l, mid, ql, ql + cnt1 - 1), solve(mid + 1, r, ql + cnt1, qr);
}

int main() {
    is >> n >> p >> m;
    FOR(i, 2, n) {
        int u, v; is >> u >> v;
        G[u].push_back(v), G[v].push_back(u);
    }
    dfs1(1, 0), dfs2(1, 1);
    auto addRectangle = [](int l1, int r1, int l2, int r2, int c) {
        q[++tot] = {1, l1, r1, r2, c, 1, 0};
        q[++tot] = {1, l2 + 1, r1, r2, c, -1, 0};
    };
    FOR(i, 1, p) {
        int x, y; is >> x >> y >> org[i];
        if (st[x] > st[y]) swap(x, y);
        int lca = getLCA(x, y);
        if (lca == x) {
            int z = getSon(x, y);
            if (st[z] > 1) addRectangle(1, st[y], st[z] - 1, ed[y], org[i]);
            if (ed[z] < n) addRectangle(st[y], ed[z] + 1, ed[y], n, org[i]);
        } else addRectangle(st[x], st[y], ed[x], ed[y], org[i]);
    }
    sort(org + 1, org + p + 1);
    int totk = unique(org + 1, org + p + 1) - org - 1;
    FOR(i, 1, tot) q[i].k = lower_bound(org + 1, org + totk + 1, q[i].k) - org;
    FOR(i, 1, m) {
        int x, y, k; is >> x >> y >> k;
        if (st[x] > st[y]) swap(x, y);
        q[++tot] = {2, st[x], st[y], 0, k, 0, i};
    }
    sort(q + 1, q + tot + 1, [](const Query &a, const Query &b) {return a.t == b.t ? a.type < b.type : a.t < b.t;});
    solve(1, p, 1, tot);
    FOR(i, 1, m) os << org[ans[i]] << '\n';
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}