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

const int maxn = 2005;
char s[maxn];
int n, k, buc[27];

int main() {
    cin >> n >> k;
    cin >> s + 1;
    FOR(ans, 1, n) if (n % ans == 0) {
        int cur = 0;
        FOR(j, 1, ans) {
            memset(buc, 0, sizeof buc);
            FOR(i, 1, n / ans) ++buc[s[(i - 1) * ans + j] - 'a'];
            int tmp = 1e9;
            FOR(i, 0, 26) chkmin(tmp, n / ans - buc[i]);
            cur += tmp;
        }
        if (cur <= k) return printf("%d\n", ans);
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}