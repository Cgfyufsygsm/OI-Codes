#include <bits/stdc++.h>
#define il inline
#define int long long
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

const int maxn = 4e6 + 6, N = 4e6;
int n, a[maxn], vis[maxn], pre[maxn], suf[maxn];

signed main() {
    cin >> n;
    FOR(i, 1, n) cin >> a[i], vis[a[i] - a[1]] = 1;
    pre[0] = -1, suf[N] = N;
    FOR(i, 1, N) if (vis[i]) pre[i] = i; else pre[i] = pre[i - 1];
    DEC(i, N - 1, 1) if (vis[i]) suf[i] = i; else suf[i] = suf[i + 1];
    FOR(i, 1, a[n]) {
        if (i * (i + 1) < a[1]) continue;
        int lb = 0, rb = i;
        if (a[1] > i * i) lb = a[1] - i * i;
        int l = 0, r = i;
        FOR(j, i, a[n]) {
            if (pre[r] >= l)
                chkmin(rb, r - pre[r]);
            l += 2 * j + 1;
            if (suf[r + 1] < l)
                chkmax(lb, l - suf[r + 1]);
            r += 2 * j + 2;
            if (l > a[n] - a[1]) break;
        }
        if (lb <= rb) {
            cout << i * i + lb - a[1] << endl;
            return 0;
        }
    }
    return 0;
}

} // namespace YangTY

signed main() {
    YangTY::main();
    return 0;
}