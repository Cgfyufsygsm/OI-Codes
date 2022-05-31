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

const int maxn = 3e5 + 5;
using ll = long long;
int a[maxn], n;
ll f[maxn][2][2];

int main() {
    cin >> n;
    FOR(i, 1, n) cin >> a[i];
    memset(f, 0x3f, sizeof f);
    f[1][0][0] = 0;
    f[1][1][1] = a[1];
    FOR(i, 2, n) {
        FOR(j, 0, 1) {
            f[i][0][j] = f[i - 1][1][j];
            f[i][1][j] = min(f[i - 1][0][j], f[i - 1][1][j]) + a[i];
        }
    }
    cout << min(f[n][0][1], f[n][1][1], f[n][1][0]);
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}