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
using ll = long long;
const int maxn = 1e5 + 5, maxm = 4e6 + 5;
int n, m, a[maxn], b[maxn], block, tot;
vector<int> G[maxn];
int fa[maxn], top[maxn], size[maxn], son[maxn], dfn[maxn], dfnClock, dep[maxn];

void dfs1(int u, int pre) {
    fa[u] = pre, size[u] = 1, dep[u] = dep[pre] + 1;
    for (auto &v : G[u]) if (v != pre) {
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
    return;
}

void dfs2(int u, int topf) {
    top[u] = topf, dfn[u] = ++dfnClock;
    if (son[u]) dfs2(son[u], topf);
    for (auto &v : G[u]) if (v != son[u] && v != fa[u]) dfs2(v, v);
}

int getSon(int rt, int x) {
    while (top[rt] != top[x]) {
        if (fa[top[x]] == rt) return top[x];
        x = fa[top[x]];
    }
    return son[rt];
}

il bool isSonOf(int u, int v) {
    return dfn[v] >= dfn[u] && dfn[v] < dfn[u] + size[u];
}

struct Query {
    int p1, p2, sgn, id;
} q[maxm];
ll ans[maxm], cnt1[maxn], cnt2[maxn], pre[maxn];

int main() {
    is >> n >> m;
    FOR(i, 1, n) is >> a[i], b[i] = a[i];
    FOR(i, 2, n) {
        int u, v; is >> u >> v;
        G[u].push_back(v), G[v].push_back(u);
    }
    dfs1(1, 0), dfs2(1, 1);
    sort(a + 1, a + n + 1);
    tot = unique(a + 1, a + n + 1) - a - 1;
    FOR(i, 1, n) b[i] = lower_bound(a + 1, a + tot + 1, b[i]) - a - 1;
    tot = 0;
    FOR(i, 1, n) ++cnt1[a[dfn[i]] = b[i]];
    FOR(i, 1, n) pre[i] = pre[i - 1] + cnt1[a[i]];
    int root = 1;
    auto addQuery = [](int l1, int r1, int l2, int r2, int sgn, int id) {
        q[++tot] = {r1, r2, sgn, id};
        q[++tot] = {r1, l2 - 1, -sgn, id};
        q[++tot] = {l1 - 1, r2, -sgn, id};
        q[++tot] = {l1 - 1, l2 - 1, sgn, id};
        return;
    };
    auto L = [](const int &u) {return dfn[u];};
    auto R = [](const int &u) {return dfn[u] + size[u] - 1;};
    FOR(i, 1, m) {
        int op, x, y;
        is >> op >> x;
        if (op == 1) root = x, ans[i] = -1;
        else {
            ans[i] = 0;
            is >> y;
            int tx = isSonOf(x, root); if (x == root) x = 1, tx = 0;
            int ty = isSonOf(y, root); if (y == root) y = 1, ty = 0;
            if (tx) x = getSon(x, root);
            if (ty) y = getSon(y, root);
            if (tx && ty) ans[i] = pre[n];
            if (tx) ans[i] += (pre[R(y)] - pre[L(y) - 1]) * (tx == ty ? -1 : 1);
            if (ty) ans[i] += (pre[R(x)] - pre[L(x) - 1]) * (tx == ty ? -1 : 1);
            addQuery(L(x), R(x), L(y), R(y), tx == ty ? 1 : -1, i);
        }
    }
    block = n / sqrt(tot) + 1;
    sort(q + 1, q + tot + 1, [](const Query &a, const Query &b) {return ((a.p1 / block) ^ (b.p1 / block)) ? a.p1 < b.p1 : (((a.p1 / block) & 1) ? a.p2 > b.p2 : a.p2 < b.p2);});
    ll tmp = 0; memset(cnt1, 0, sizeof cnt1);
    int p1 = 0, p2 = 0;
    FOR(i, 1, tot) {
        while (p1 < q[i].p1) tmp += cnt2[a[++p1]], ++cnt1[a[p1]];
        while (p1 > q[i].p1) --cnt1[a[p1]], tmp -= cnt2[a[p1--]];
        while (p2 < q[i].p2) tmp += cnt1[a[++p2]], ++cnt2[a[p2]];
        while (p2 > q[i].p2) --cnt2[a[p2]], tmp -= cnt1[a[p2--]];
        ans[q[i].id] += tmp * q[i].sgn;
    }
    FOR(i, 1, m) if (~ans[i]) os << ans[i] << '\n';
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}