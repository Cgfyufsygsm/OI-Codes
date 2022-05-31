#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define fileIn(s) freopen(s, "r", stdin);
#define fileOut(s) freopen(s, "w", stdout);

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
const int maxn = 2e5 + 5, maxm = 4e5 + 5;
int head[maxn], cnte;
int n, m, q, vis[maxn];
ll mind[maxn << 1];

struct Edge {
    int from, to, nxt, a; ll l;
} e[maxm << 1];

void add(int u, int v, ll l, int a) {
    e[++cnte] = {u, v, head[u], a, l};
    head[u] = cnte;
    return;
}

void dijkstra() {
    memset(mind, 0x3f, sizeof mind);
    memset(vis, 0, sizeof vis);
    using tmp = pair<ll, int>;
    priority_queue<tmp, vector<tmp>, greater<tmp>> q;
    mind[1] = 0, q.push({0, 1});
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u]; i; i = e[i].nxt) {
            int &v = e[i].to;
            if (mind[u] + e[i].l < mind[v]) {
                mind[v] = mind[u] + e[i].l;
                q.push({mind[v], v});
            }
        }
    }
    return;
}

int tot, fa[maxn << 1][20], val[maxn << 1];
int ufs[maxn << 1], son[maxn << 1][2];

int find(int x) {return ufs[x] == x ? x : ufs[x] = find(ufs[x]);}

void dfs(int u, int pre) {
    fa[u][0] = pre;
    FOR(j, 1, 19) fa[u][j] = fa[fa[u][j - 1]][j - 1];
    if (!son[u][0]) return;
    dfs(son[u][0], u), dfs(son[u][1], u);
    mind[u] = min(mind[son[u][0]], mind[son[u][1]]);
    return;
}

int main() {
    int T; is >> T;
    while (T--) {
        memset(head, 0, sizeof head), cnte = 0;
        is >> n >> m;
        FOR(i, 1, m) {
            int u, v, l, a; is >> u >> v >> l >> a;
            add(u, v, l, a), add(v, u, l, a);
        }
        dijkstra();
        sort(e + 1, e + cnte + 1, [](const Edge &a, const Edge &b) {return a.a > b.a;});
        FOR(i, 1, n) ufs[i] = i;
        memset(son, 0, sizeof son);
        tot = n;
        FOR(i, 1, cnte) {
            int x = find(e[i].from), y = find(e[i].to);
            if (x == y) continue;
            int z = ++tot;
            ufs[x] = ufs[y] = ufs[z] = z;
            son[z][0] = x, son[z][1] = y;
            val[z] = e[i].a;
        }
        dfs(tot, 0);
        ll lastAns = 0;
        int k, s;
        is >> q >> k >> s;
        while (q--) {
            int v, p; is >> v >> p;
            v = (v + k * lastAns - 1) % n + 1;
            p = (p + k * lastAns) % (s + 1);
            DEC(j, 19, 0)
                if (fa[v][j] && val[fa[v][j]] > p)
                    v = fa[v][j];
            os << (lastAns = mind[v]) << '\n';
        }
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}