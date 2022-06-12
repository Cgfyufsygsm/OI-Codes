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
const int maxn = 1e5 + 5;
map<ll, ll> f[maxn];
int n, m, k, fa[maxn], d[maxn], w[maxn], rt[maxn];

void merge(int &a, int b) {
    if (f[a].size() < f[b].size()) swap(a, b);
    for (auto it = f[b].begin(); it != f[b].end(); ++it)
        f[a][it->first] += it->second;
    return;
}

int main() {
    is >> n >> m >> k;
    FOR(i, 2, n) is >> fa[i];
    FOR(i, 1, n) rt[i] = i, d[i] = k + 1;
    FOR(i, 1, m) {
        int u; is >> u;
        is >> d[u] >> w[u];
    }
    DEC(i, n, 1) {
        if (d[i] <= k) {
            f[rt[i]][d[i]] += w[i];
            for (auto it = next(f[rt[i]].find(d[i])); it != f[rt[i]].end();) {
                if (it->second > w[i]) {
                    it->second -= w[i];
                    break;
                } else {
                    w[i] -= it->second;
                    auto tmp = it++;
                    f[rt[i]].erase(tmp);
                }
            }
        }
        merge(rt[fa[i]], rt[i]);
    }
    ll ans = 0;
    for (auto it = f[rt[1]].begin(); it != f[rt[1]].end(); ++it)
        ans += it->second;
    os << ans << '\n';
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}