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
using ll = long long;
const int maxn = 20005, maxm = 2e5 + 5, LG = 62;
ll val[maxn], ans[maxm];
int n, m;
vector<pair<int, int>> q[maxn]; // 第一位存点，第二位存编号
vector<int> G[maxn];

struct LinearBasis {
    ll a[64];
    void clear() {memset(a, 0, sizeof a); return;}
    void insert(ll x) {
        DEC(j, LG, 0) if ((x >> j) & 1) {
            if (!a[j]) a[j] = x;
            x ^= a[j];
        }
        return;
    }
    void merge(const LinearBasis &b) {
        FOR(i, 0, LG) if (b.a[i]) insert(b.a[i]);
        return;
    }
    ll query() {
        ll ans = 0;
        DEC(j, LG, 0) if ((ans ^ a[j]) > ans) ans ^= a[j];
        return ans;
    }
} basis[maxn];

ll query(const LinearBasis &a, const LinearBasis &b) {
    LinearBasis tmp = a;
    tmp.merge(b);
    return tmp.query();
}

int size[maxn], maxp[maxn], vis[maxn], root, tot;
int vis2[maxn];

void getRt(int u, int fa) {
    size[u] = 1, maxp[u] = 0;
    for (auto &v : G[u]) {
        if (vis[v] || v == fa) continue;
        getRt(v, u);
        size[u] += size[v];
        chkmax(maxp[u], size[v]);
    }
    chkmax(maxp[u], tot - size[u]);
    if (maxp[u] < maxp[root]) root = u;
    return;
}

void dfs(int u, int fa, vector<int> &vec) {
    basis[u].insert(val[u]);
    vec.push_back(u);
    for (auto &p : q[u])
        if (vis2[p.first]) chkmax(ans[p.second], query(basis[p.first], basis[u]));
    for (auto &v : G[u]) {
        if (vis[v] || v == fa) continue;
        basis[v] = basis[u];
        dfs(v, u, vec);
    }
    return;
}

void mark(int u, int fa) {
    vis2[u] = 1;
    for (auto &v : G[u]) if (!vis[v] && v != fa) mark(v, u);
    return;
}

void calc(int u) {
    basis[u].clear(), basis[u].insert(val[u]);
    vector<int> vec;
    vec.push_back(u), vis2[u] = 1;
    for (auto &v : G[u]) {
        if (vis[v]) continue;
        basis[v] = basis[u];
        dfs(v, u, vec);
        mark(v, u);
    }
    for (auto &x : vec) vis2[x] = 0;
    return;
}

void divide(int u) {
    vis[u] = 1;
    calc(u);
    for (auto &v : G[u]) {
        if (vis[v]) continue;
        maxp[root = 0] = n, tot = size[v];
        getRt(v, 0), getRt(root, 0);
        divide(root);
    }
    return;
}

int main() {
    is >> n >> m;
    FOR(i, 1, n) is >> val[i];
    FOR(i, 2, n) {
        int x, y; is >> x >> y;
        G[x].push_back(y), G[y].push_back(x);
    }
    FOR(i, 1, m) {
        int x, y; is >> x >> y;
        if (x == y) ans[i] = val[x];
        else {
            q[x].push_back({y, i});
            q[y].push_back({x, i});
        }
    }
    maxp[root = 0] = tot = n;
    getRt(1, 0);
    getRt(root, 0);
    divide(root);
    FOR(i, 1, m) os << ans[i] << '\n';
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}