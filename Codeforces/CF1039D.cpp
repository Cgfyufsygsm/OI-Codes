#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
using namespace YangTY::fastIO;
const int maxn = 1e5 + 5;
int n, fa[maxn], id[maxn], dfn[maxn], dfnTot;
vector<int> G[maxn];
int f[maxn], ans[maxn];

template<typename T> il T chkmax(T &a, const T &b) {return a = (b > a ? b : a);}

void dfs0(int u, int pre) {
    fa[u] = pre, dfn[u] = ++dfnTot;
    for (const auto &v : G[u]) if (v != pre) dfs0(v, u);
    return;
}

int dp(int k) {
    if (~ans[k]) return ans[k];
    int ret = 0;
    fill(f + 1, f + n + 1, 1);
    DEC(i, n, 1) {
        int &u = id[i];
        if (fa[u] && (~f[fa[u]] && ~f[u])) {
            if (f[u] + f[fa[u]] >= k) ++ret, f[fa[u]] = -1;
            else chkmax(f[fa[u]], f[u] + 1);
        }
    }
    return ans[k] = ret;
}

int main() {
    is >> n;
    FOR(i, 2, n) {
        int u, v; is >> u >> v;
        G[u].emplace_back(v), G[v].emplace_back(u);
    }
    dfs0(1, 0);
    FOR(i, 1, n) id[i] = i;
    sort(id + 1, id + n + 1, [](const int &a, const int &b) {return dfn[a] < dfn[b];});
    int B = sqrt(n * log2(n));
    memset(ans, -1, sizeof ans);
    ans[1] = n;
    FOR(k, 2, B) ans[k] = dp(k);
    int now = B + 1;
    DEC(cur, ans[B], 0) {
        if (now > n) break;
        int l = now, r = n, ret = now - 1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (dp(mid) >= cur) ret = mid, l = mid + 1;
            else r = mid - 1;
        }
        FOR(i, now, ret) ans[i] = cur;
        now = ret + 1;
    }
    FOR(i, 1, n) os << ans[i] << '\n';
    return 0;
}