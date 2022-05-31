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

const int maxn = 1e6 + 5;
int a[maxn], vis[maxn * 3], n, w;

int main() {
    freopen("data.in", "r", stdin);
    cin >> n >> w;
    FOR(i, 1, n) cin >> a[i];
    FOR(i, 1, n) vis[a[i]] = 1;
    FOR(i, 1, n) FOR(j, i + 1, n) vis[a[i] + a[j]] = 1;
    FOR(i, 1, n) FOR(j, i + 1, n) FOR(k, j + 1, n) vis[a[i] + a[j] + a[k]] = 1;
    int ans = 0;
    FOR(i, 1, w) ans += vis[i];
    cout << ans << endl;
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}