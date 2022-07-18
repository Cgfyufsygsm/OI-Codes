#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}

using namespace std;
using ll = long long;
const int maxn = 55, maxm = 305;
int n, m;
struct Edge {
    int u, v; ll w;
} e[maxm];

struct UnionFind {
    int fa[maxn];
    void init() {
        FOR(i, 1, n) fa[i] = i;
    }
    int find(int u) {return fa[u] == u ? u : fa[u] = find(fa[u]);}
    int merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return 0;
        else return fa[u] = v, 1;
    }
} ufs;

pair<ll, int> kruskal(int x) {
    sort(e + 1, e + m + 1, [&x](const Edge &a, const Edge &b) {
        return myabs(a.w - x) == myabs(b.w - x) ? a.w > b.w : myabs(a.w - x) < myabs(b.w - x);
    });
    ufs.init();
    ll ans = 0; int cnt = 0;
    FOR(i, 1, m) if (ufs.merge(e[i].u, e[i].v)) ans += myabs(e[i].w - x), cnt += e[i].w > x;
    return {ans, cnt};
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    FOR(i, 1, m) cin >> e[i].u >> e[i].v >> e[i].w, e[i].w <<= 1;
    vector<int> ev(1, 0);
    FOR(i, 1, m) FOR(j, i, m) ev.push_back((e[i].w + e[j].w) >> 1);
    sort(ev.begin(), ev.end());
    ev.resize(unique(ev.begin(), ev.end()) - ev.begin());
    vector<pair<ll, int>> res;
    for (const int &x : ev) res.emplace_back(kruskal(x));
    int p, k, a, b, c, x = 0;
    cin >> p >> k >> a >> b >> c;
    ll ans = 0;
    FOR(i, 1, k) {
        if (i <= p) cin >> x;
        else x = (1ll * x * a + b) % c;
        int y = upper_bound(ev.begin(), ev.end(), x << 1) - ev.begin() - 1;
        ans ^= (res[y].first + (n - 1ll - 2 * res[y].second) * (2 * x - ev[y])) >> 1;
    }
    cout << ans << endl;
    return 0;
}