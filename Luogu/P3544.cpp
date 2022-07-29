#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using namespace YangTY::fastIO;
using ll = long long;
const int maxn = 5e5 + 5, maxm = 3e6 + 5;
const ll INF = 1e18;

int n, m;
int head[maxn], cnte;
ll p[maxn];
struct Edge {
    int to, nxt;
    ll w;
} e[maxm << 1];

void add(int u, int v, ll w) {
    e[++cnte] = {v, head[u], w}, head[u] = cnte;
    return;
}

struct Interval {
    ll l, r;
    Interval(ll _l = 0, ll _r = 0) : l(_l), r(_r) {}
    il friend Interval operator&(const Interval &x, const Interval &y) {
        return Interval(max(x.l, y.l), min(x.r, y.r));
    }
};

struct Node {
    ll k, b;
    Node(ll _k = 0, ll _b = 0) : k(_k), b(_b) {}
    il ll get(ll x) const {return k * x + b;}
    il Interval solve(ll x) const {
        if (k > 0) return Interval(-b / k, (x - b) / k);
        else return Interval((x - b) / k, -b / k);
    }
    il friend Node operator+(const Node &a, const Node &b) {return Node(a.k + b.k, a.b + b.b);}
    il friend Node operator-(const Node &a, const Node &b) {return Node(a.k - b.k, a.b - b.b);}
} w[maxn];
int vis[maxn];

il ll cmp(const Node &x, const Node &y) {
    if (x.k == y.k) return (x.b == y.b) ? INF : -INF;
    if ((y.b - x.b) % (x.k - y.k)) return -INF;
    else return (y.b - x.b) / (x.k - y.k);
}

pair<ll, ll> bfs(int s) {
    ll z = INF;
    w[s] = Node(1, 0);
    queue<int> q;
    vector<int> vec;
    q.push(s), vec.push_back(s);
    vis[s] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = e[i].nxt) {
            int &v = e[i].to;
            if (!vis[v]) {
                w[v] = Node(0, e[i].w) - w[u];
                vis[v] = 1;
                vec.push_back(v);
                q.push(v);
            } else {
                ll tmp = cmp(w[v], Node(0, e[i].w) - w[u]);
                if (tmp == -INF) return {-INF, -INF};
                else if (tmp != INF) {
                    if (z != INF && tmp != z) return {-INF, -INF};
                    z = tmp;
                }
            }
        }
    }
    if (z != INF) {
        ll ans = 0;
        for (auto &x : vec) {
            ll tmp = w[x].get(z);
            if (tmp < 0 || tmp > p[x]) return {-INF, -INF};
            ans += tmp;
        }
        return {ans, ans};
    } else {
        Interval ans(-INF, INF);
        Node tmp(0, 0);
        for (auto &x : vec) ans = ans & w[x].solve(p[x]), tmp = tmp + w[x];
        if (ans.l > ans.r) return {-INF, -INF};
        ll ans1 = tmp.get(ans.l), ans2 = tmp.get(ans.r);
        if (ans1 > ans2) swap(ans1, ans2);
        return {ans1, ans2};
    }
}

int main() {
    is >> n >> m;
    FOR(i, 1, n) is >> p[i];
    FOR(i, 1, m) {
        int u, v, w; is >> u >> v >> w;
        w = p[u] + p[v] - w;
        add(u, v, w), add(v, u, w);
    }
    ll ans1 = 0, ans2 = 0;
    FOR(i, 1, n) if (!vis[i]) {
        auto tmp = bfs(i);
        if (tmp.first == -INF) return puts("NIE"), 0;
        ans1 += tmp.first, ans2 += tmp.second;
    }
    os << ans1 << ' ' << ans2 << '\n';
    return 0;
}