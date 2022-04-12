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

const int maxn = 1e5 + 5;
vector<int> G[maxn];
int a[maxn], f[maxn], n;

void dfs(int u, int fa) {
    int t = 0;
    for (auto &v : G[u]) {
        if (v == fa) continue;
        dfs(v, u);
        t |= (f[u] & f[v]);
        f[u] |= f[v];
    }
    int k = t ? 32 - __builtin_clz(unsigned(t)) : 0;
    a[u] = __builtin_ctz(unsigned((f[u] | ((1 << k) - 1)) + 1));
    f[u] = ((f[u] >> a[u]) | 1) << a[u];
    return;
}

int main() {
    cin >> n;
    FOR(i, 2, n) {
        int u, v; cin >> u >> v;
        G[u].push_back(v), G[v].push_back(u);
    }
    dfs(1, 0);
    int ans = 0;
    FOR(i, 1, n) chkmax(ans, a[i]);
    cout << ans << endl;
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}