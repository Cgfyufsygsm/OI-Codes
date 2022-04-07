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
ll n, ans = 2e18, N = 1e6;

int main() {
    cin >> n;
    for (ll a = 0; a <= N; ++a) {
        ll l = 0, r = N + 1;
        while (l < r) {
            ll mid = (l + r) >> 1;
            if ((a + mid) * (a * a + mid * mid) >= n) chkmin(ans, (a + mid) * (a * a + mid * mid)), r = mid;
            else l = mid + 1;
        }
    }
    cout << ans << endl;
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}