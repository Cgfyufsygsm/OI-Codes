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

const int maxn = 2e5 + 5;
int a[maxn], n, f[maxn];
vector<int> G[maxn];

void dfs(int u, int fa, int mid) {
    f[u] = 0;
    for (auto &v : G[u]) {
        if (v == fa) continue;
        dfs(v, u, mid);
        f[u] += f[v];
    }
    f[u] = max(f[u] - 1, 0) + (a[u] >= mid);
    return;
}

int main() {
    cin >> n;
    FOR(i, 2, n) cin >> a[i];
    FOR(i, 2, n) {
        int u, v; cin >> u >> v;
        G[u].push_back(v), G[v].push_back(u);
    }
    int l = 0, r = (int)1e9 + 1, ans = 0;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        dfs(1, 0, mid);
        if (f[1]) ans = mid, l = mid;
        else r = mid;
    }
    cout << ans << endl;
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}