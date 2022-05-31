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
const int maxn = 1e5 + 5;
int n, m, Q, ans[maxn];
struct Edge {
    int x, y;
} e[maxn];

struct UnionFind {
    int fa[maxn], sz[maxn], stk[maxn], top;
    void init() {
        FOR(i, 1, n) fa[i] = i, sz[i] = 1;
        top = 0;
        return;
    }
    int find(int x) {return x == fa[x] ? x : find(fa[x]);}
    il bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return 0;
        if (sz[x] > sz[y]) swap(x, y);
        fa[x] = y, sz[y] += sz[x];
        stk[++top] = x;
        return 1;
    }
    il int query(int x, int y) {
        x = find(x), y = find(y);
        return x == y ? sz[x] : sz[x] + sz[y];
    }
    il void undo() {
        int x = stk[top--];
        sz[fa[x]] -= sz[x], fa[x] = x;
        return;
    }
} uf;

struct Query {
    int id, x, y, z;
} q[maxn], q1[maxn], q2[maxn];

void solve(int l, int r, int ql, int qr) {
    if (l == r) {
        FOR(i, ql, qr) ans[q[i].id] = l;
        uf.merge(e[l].x, e[l].y);
        return;
    }
    int cnt1 = 0, cnt2 = 0, mid = (l + r) >> 1, nowtop = uf.top;
    FOR(i, l, mid) uf.merge(e[i].x, e[i].y);
    FOR(i, ql, qr) {
        int res = uf.query(q[i].x, q[i].y);
        if (q[i].z <= res) q1[++cnt1] = q[i];
        else q2[++cnt2] = q[i];
    }
    while (uf.top > nowtop) uf.undo();
    FOR(i, 1, cnt1) q[ql + i - 1] = q1[i];
    FOR(i, 1, cnt2) q[ql + cnt1 + i - 1] = q2[i];
    solve(l, mid, ql, ql + cnt1 - 1);
    solve(mid + 1, r, ql + cnt1, qr);
    return;
}

int main() {
    is >> n >> m;
    FOR(i, 1, m)
        is >> e[i].x >> e[i].y;
    uf.init();
    is >> Q;
    FOR(i, 1, Q) {
        int x, y, z; is >> x >> y >> z;
        q[i] = {i, x, y, z};
    }
    solve(1, m, 1, Q);
    FOR(i, 1, Q) os << ans[i] << '\n';
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}