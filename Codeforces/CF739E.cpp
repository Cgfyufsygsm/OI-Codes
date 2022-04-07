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

using db = double;
const int maxn = 2005;
int n, a, b;
db p[maxn], q[maxn];

struct DP {
    db dp;
    int cnt;
    DP(db _dp = 0, int _cnt = 0) : dp(_dp), cnt(_cnt) {}
    il bool operator>(const DP &rhs) const {
        return (myabs(dp - rhs.dp) < 1e-7) ? (cnt < rhs.cnt) : (dp > rhs.dp);
    }
    il DP operator+(const DP &rhs) const {
        return DP(dp + rhs.dp, cnt + rhs.cnt);
    }
} f[maxn][maxn];

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> a >> b;
    FOR(i, 1, n) cin >> p[i];
    FOR(i, 1, n) cin >> q[i];
    db l = 0, r = 1, ans = 0;
    for (int kase = 1; kase <= 30; ++kase) {
        db mid = (l + r) / 2;
        memset(f, 0, sizeof f);
        FOR(i, 1, n) FOR(j, 0, a) {
            chkmax(f[i][j], f[i - 1][j] + DP(0, 0));
            chkmax(f[i][j], f[i - 1][j] + DP(q[i] - mid, 1));
            if (j) {
                chkmax(f[i][j], f[i - 1][j - 1] + DP(p[i], 0));
                chkmax(f[i][j], f[i - 1][j - 1] + DP(p[i] + q[i] - p[i] * q[i] - mid, 1));
            }
        }
        DP mx;
        FOR(j, 0, a) chkmax(mx, f[n][j]);
        if (mx.cnt <= b) ans = mx.dp + mid * b, r = mid;
        else l = mid;
    }
    cout << ans << endl;
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}