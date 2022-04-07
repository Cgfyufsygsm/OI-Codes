#include <bits/stdc++.h>
#include <fastio.hpp>

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

using fastIO::is;
using fastIO::os;
const int maxn = 1e6 + 5;

int n, k[maxn], a[maxn], vis[maxn], cnt[maxn];
vector<int> p[maxn];

void solve() {
    is >> n;
    FOR(i, 1, n) {
        is >> k[i];
        vis[i] = cnt[i] = 0;
        vector<int>().swap(p[i]);
        FOR(j, 1, k[i]) {
            int x; is >> x;
            p[i].push_back(x);
        }
        a[i] = i;
    }
    sort(a + 1, a + n + 1, [](const int &x, const int &y) {return k[x] < k[y];});
    FOR(t, 1, n) {
        int i = a[t];
        if (!k[i]) continue;
        FOR(u, 0, k[i] - 1) ++cnt[vis[p[i][u]]];
        FOR(u, 0, k[i] - 1) {
            int g = vis[p[i][u]];
            if (g && cnt[g] < k[g] && cnt[g] < k[i]) {
                os << "YES\n";
                os << i << ' ' << g << '\n';
                return;
            }
        }
        FOR(u, 0, k[i] - 1) --cnt[vis[p[i][u]]], vis[p[i][u]] = i;
    }
    os << "NO\n";
    return;
}

int main() {
    int T; is >> T;
    while (T--) solve();
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}