#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
template<typename T> il T chkmax(T &a, const T &b) {return a = (b > a ? b : a);}
template<typename T> il T chkmin(T &a, const T &b) {return a = (b < a ? b : a);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}

using namespace YangTY::fastIO;
using ll = long long;
const int maxn = 2e5 + 5;
vector<int> G[maxn], node[maxn];
int n, dep[maxn], fa[maxn], maxd;
ll a[maxn], minv[maxn], maxv[maxn], f1[maxn], f2[maxn], f[maxn], ans;

void dfs(int u, int pre) {
    fa[u] = pre, dep[u] = dep[pre] + 1, node[dep[u]].push_back(u);
    chkmin(minv[dep[u]], a[u]), chkmax(maxv[dep[u]], a[u]);
    chkmax(maxd, dep[u]);
    for (auto &v : G[u]) if (v != pre) dfs(v, u);
    return;
}

int main() {
    int T; is >> T;
    while (T--) {
        is >> n, maxd = 0, ans = 0;
        FOR(i, 1, n) vector<int>().swap(G[i]), vector<int>().swap(node[i]), minv[i] = 1e9, maxv[i] = -1e9, f1[i] = -1e18, f2[i] = -1e18, f[i] = -1e18;
        FOR(i, 2, n) {
            int u; is >> u;
            G[u].push_back(i), G[i].push_back(u);
        }
        FOR(i, 2, n) is >> a[i];
        dfs(1, 0);
        f[1] = 0;
        FOR(d, 2, maxd) {
            for (auto &u : node[d]) chkmax(f1[d], f[fa[u]] + a[u]), chkmax(f2[d], f[fa[u]] - a[u]);
            for (auto &u : node[d]) {
                chkmax(f[u], f[fa[u]] + max(myabs(a[u] - maxv[d]), myabs(a[u] - minv[d])));
                chkmax(f[u], a[u] + f2[d]);
                chkmax(f[u], f1[d] - a[u]);
                if (d == maxd) chkmax(ans, f[u]);
            }
        }
        os << ans << '\n';
    }
    return 0;
}