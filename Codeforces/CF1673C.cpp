#include <bits/stdc++.h>
#include <modint.hpp>
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

using mint = modint1000000007;

const int maxn = 40005;
int tot, p[500];
mint f[500][maxn];

il bool check(int n) {
    int a[10], top = 0;
    while (n) a[++top] = n % 10, n /= 10;
    FOR(i, 1, top) if (a[i] != a[top - i + 1]) return false;
    return true;
}

int main() {
    FOR(i, 1, 40000) if (check(i)) p[++tot] = i;
    f[0][0] = 1;
    FOR(i, 1, tot) FOR(j, 0, 40000) {
        f[i][j] += f[i - 1][j];
        if (p[i] <= j) f[i][j] += f[i][j - p[i]];
    }
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        cout << f[tot][n].val << endl;
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}