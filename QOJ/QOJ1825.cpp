#include <bits/stdc++.h>
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

using ll = long long;
const int maxn = 1505, maxm = 3e5 + 5;
int S, T;

class MCMF {
  private:
    int head[maxn], cur[maxn], cnte = 1;
    struct Edge {
        int to, nxt, w;
        ll cost;
    } e[maxm];
    ll dis[maxn], maxCost;
    int pre[maxn], inq[maxn], flow[maxn], maxFlow;

    bool SPFA() {
        memset(dis, 0x80, sizeof dis);
        memset(inq, 0, sizeof inq);
        queue<int> q;
        q.push(S);
        inq[S] = 1, dis[S] = 0, flow[S] = numeric_limits<int>::max();
        while (!q.empty()) {
            int u = q.front(); q.pop();
            inq[u] = 0;
            for (int i = head[u]; i; i = e[i].nxt) {
                int &v = e[i].to;
                if (e[i].w && dis[v] < dis[u] + e[i].cost) {
                    dis[v] = dis[u] + e[i].cost;
                    flow[v] = min(flow[u], e[i].w);
                    pre[v] = i;
                    if (!inq[v]) q.push(v), inq[v] = 1;
                }
            }
        }
        return dis[T] > static_cast<int>(0x80808080);
    }

    void update() {
        int u = T;
        while (u != S) {
            int i = pre[u];
            e[i].w -= flow[T], e[i ^ 1].w += flow[T];
            u = e[i ^ 1].to;
        }
        maxCost += flow[T] * dis[T];
        maxFlow += flow[T];
        return;
    }
  public:
    il void addEdge(int u, int v, int w, int c) {
        e[++cnte] = {v, head[u], w, c}, head[u] = cnte;
        e[++cnte] = {u, head[v], 0, -c}, head[v] = cnte;
        return;
    }

    pair<int, ll> work() {
        while (SPFA()) update();
        return {maxFlow, maxCost};
    }

} flow;

class UnionFind {
  private:
    int fa[maxn];
    int find(int u) {return u == fa[u] ? u : fa[u] = find(fa[u]);}
  public:
    il bool query(int u, int v) {return find(u) == find(v);}
    il bool uni(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        fa[u] = v;
        return true;
    }
    UnionFind() {
        FOR(i, 1, maxn - 5) fa[i] = i;
        return;
    }
} ufs;

struct Edge {
    int u, v, w;
    il bool operator<(const Edge &rhs) const {return w < rhs.w;}
} e[maxm];

vector<pair<int, int>> tree[maxn];
int fap[maxn], fa[maxn], n, m, k, vis[maxn];
ll totw;

void dfs(int u, int pre) {
    if (pre == -1) fap[u] = 1e7;
    vis[u] = true, fa[u] = pre;
    for (auto &p : tree[u]) {
        int &v = p.first;
        if (vis[v]) continue;
        fap[v] = p.second, dfs(v, u);
    }
    return;
}

int main() {
    cin >> n >> m >> k;
    FOR(i, 1, m) cin >> e[i].u >> e[i].v >> e[i].w;
    sort(e + 1, e + m + 1);
    FOR(i, 1, m) if (ufs.uni(e[i].u, e[i].v)) {
        totw += e[i].w;
        tree[e[i].u].push_back({e[i].v, e[i].w});
        tree[e[i].v].push_back({e[i].u, e[i].w});
    }

    S = 2 * n + k + 1, T = S + 1;
    FOR(i, 1, n) flow.addEdge(i, n + i, 1, 0);
    FOR(i, 1, k) {
        flow.addEdge(S, 2 * n + i, 1, 0);
        int s; cin >> s;
        while (s--) {
            int v; cin >> v;
            flow.addEdge(2 * n + i, v, 1, 0);
        }
    }

    FOR(i, 1, n) if (!vis[i]) dfs(i, -1), totw += 1e7;

    FOR(i, 1, n) {
        flow.addEdge(n + i, T, 1, fap[i]);
        if (~fa[i]) flow.addEdge(n + i, fa[i], 1, 0);
    }

    auto ret = flow.work();
    ll ans = totw - ret.second;
    cout << ((ans >= 1e7 || ret.first < k) ? -1 : ans);

    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}