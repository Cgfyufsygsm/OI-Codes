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
const int LG = 63, maxn = 5e4 + 5, maxm = 2e5 + 5;
int head[maxn], cnte, n, m, vis[maxn];
ll a[LG + 5], dis[maxn];

struct Edge {
    int to, nxt; ll w;
} e[maxm];

il void add(int u, int v, ll w) {
    e[++cnte] = {v, head[u], w};
    head[u] = cnte;
    return;
}

void insert(ll x) {
    DEC(i, LG, 0) if ((x >> i) & 1) {
        if (!a[i]) a[i] = x;
        x ^= a[i];
    }
    return;
}

void dfs(int u) {
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt) {
        int &v = e[i].to;
        if (vis[v]) insert(dis[v] ^ dis[u] ^ e[i].w);
        else dis[v] = dis[u] ^ e[i].w, dfs(v);
    }
}

int main() {
    cin >> n >> m;
    FOR(i, 1, m) {
        int u, v; ll w;
        cin >> u >> v >> w;
        add(u, v, w), add(v, u, w);
    }
    dfs(1);
    ll ans = dis[n];
    DEC(i, LG, 0) if ((ans ^ a[i]) > ans) ans ^= a[i];
    cout << ans << endl;
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}