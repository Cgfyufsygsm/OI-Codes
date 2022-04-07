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

using ll = long long;
const int maxn = 2e5 + 5;
int n;
ll k, x, a[maxn], ans;

int main() {
    cin >> n >> k >> x;
    FOR(i, 1, n) cin >> a[i], ans += a[i];
    sort(a + 1, a + n + 1, greater<int>());
    FOR(i, 1, n) {
        ll c = a[i] / x;
        chkmin(c, k);
        ans -= min(a[i], c * x);
        k -= c, a[i] -= min(a[i], c * x);
    }
    sort(a + 1, a + n + 1, greater<int>());
    FOR(i, 1, n) {
        ll c = (a[i] + x - 1) / x;
        chkmin(c, k);
        ans -= min(a[i], c * x);
        k -= c, a[i] -= min(a[i], c * x);
    }
    cout << ans << endl;
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}