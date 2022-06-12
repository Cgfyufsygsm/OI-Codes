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
const int maxn = 2e5 + 5;
int n, a[maxn];
ll m;
using pll = pair<ll, ll>;

il ll f(ll x, ll k) {
    return (x % (k + 1)) * ((x + k) / (k + 1)) * ((x + k) / (k + 1)) + (k + 1 - (x % (k + 1))) * (x / (k + 1)) * (x / (k + 1));
}

pll calc(ll x, ll d) {
    ll l = 1, r = x - 1, ret = 0;
    while (l <= r) {
        auto mid = (l + r) >> 1;
        if (f(x, mid - 1) - f(x, mid) >= d)
            ret = mid, l = mid + 1;
        else r = mid - 1;
    }
    return {f(x, ret), ret};
}

pll check(ll mid) {
    pll res;
    FOR(i, 1, n) {
        auto now = calc(a[i], mid);
        res.first += now.first, res.second += now.second;
    }
    return res;
}

int main() {
    is >> n;
    FOR(i, 1, n) is >> a[i];
    DEC(i, n, 1) a[i] -= a[i - 1];
    is >> m;
    ll l = 0, r = 1e18, d;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        if (check(mid).first <= m) l = mid + 1, d = mid;
        else r = mid - 1;
    }
    auto res = check(d + 1);
    cout << res.second + (res.first - m + d - 1) / d;
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}