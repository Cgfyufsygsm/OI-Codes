#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

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

using db = double;
const int maxn = 5005, maxm = 2e5 + 5;

int head[maxn], cnte = 1, n, m, fa[maxn], seq[maxn], rt[maxn], tot;
bool vis[maxn];
db E, dis[maxn];
struct Edge {
    int to, nxt;
    db w;
} e[maxm << 1];

struct Node {
    int ch[2], fa;
    db val;
} t[maxm * 30];

#define ls(u) t[u].ch[0]
#define rs(u) t[u].ch[1]

int newNode(int fa, db val) {
    int u = ++tot;
    ls(u) = rs(u) = 0;
    t[u].fa = fa, t[u].val = val;
    return u;
}

int merge(int x, int y) {
    static mt19937 rnd(20041031);
    if (!x || !y) return x + y;
    if (t[x].val > t[y].val) swap(x, y);
    int u = ++tot;
    t[u] = t[x];
    rs(u) = merge(rs(u), y);
    if (rnd() & 1) swap(ls(u), rs(u));
    return u;
}

il void add(int u, int v, db w) {
    e[++cnte].to = v;
    e[cnte].w = w;
    e[cnte].nxt = head[u];
    head[u] = cnte;
    return;
}

void Dijkstra() {
    priority_queue<pair<db, int>, vector<pair<db, int> >, greater<pair<db, int> > > q;
    memset(dis, 127, sizeof dis);
    q.push({0, n}), dis[n] = 0;
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u]; i; i = e[i].nxt) {
            if (~i & 1) continue;
            int &v = e[i].to;
            if (vis[v]) continue;
            if (dis[v] > dis[u] + e[i].w) {
                dis[v] = dis[u] + e[i].w;
                fa[v] = i ^ 1;
                q.push({dis[v], v});
            }
        }
    }
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> E;
    FOR(i, 1, m) {
        int s, t; db w; cin >> s >> t >> w;
        if (s == n) {
            --i, --m;
            continue;
        }
        add(s, t, w), add(t, s, w);
    }
    Dijkstra();
    FOR(i, 1, n) seq[i] = i;
    sort(seq + 1, seq + n + 1, [](const int a, const int b) {return dis[a] < dis[b];});
    FOR(i, 1, n) {
        int u = seq[i];
        for (int i = head[u]; i; i = e[i].nxt) {
            if ((i & 1) || i == fa[u]) continue;
            int v = e[i].to;
            rt[u] = merge(rt[u], newNode(v, dis[v] - dis[u] + e[i].w));
        }
        rt[u] = merge(rt[u], rt[e[fa[u]].to]);
    }
    priority_queue<pair<db, int>, vector<pair<db, int> >, greater<pair<db, int> > > q;
    if (E < dis[1]) {
        cout << 0 << endl;
        return 0;
    }
    int ans = 1; E -= dis[1];
    if (rt[1]) q.push({t[rt[1]].val, rt[1]});
    while (!q.empty()) {
        auto u = q.top(); q.pop();
        if (E < (u.first + dis[1])) break;
        ++ans, E -= (u.first + dis[1]);
        int &x = u.second;
        if (ls(x)) q.push({u.first - t[x].val + t[ls(x)].val, ls(x)});
        if (rs(x)) q.push({u.first - t[x].val + t[rs(x)].val, rs(x)});
        if (rt[t[x].fa]) q.push({u.first + t[rt[t[x].fa]].val, rt[t[x].fa]});
    }
    cout << ans << endl;
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}