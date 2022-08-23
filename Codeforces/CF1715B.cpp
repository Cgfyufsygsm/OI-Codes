#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define szof(a) ((int) (a).size())
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define fileIn(s) freopen(s, "r", stdin)
#define fileOut(s) freopen(s, "w", stdout)
#define clr(f, n) memset(f, 0, (sizeof(int)) * (n))
#define cpy(f, g, n) memcpy(f, g, (sizeof(int)) * (n))

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
ll n, k, b, s, a[maxn];

int main() {
    // fileIn("data.in");
    int T; cin >> T;
    while (T--) {
        cin >> n >> k >> b >> s;
        a[n] = b * k + k - 1;
        if (s < a[n] && s >= b * k) a[n] = s;
        if ((k - 1) * (n - 1) < s - a[n] || s < a[n]) {
            puts("-1");
            continue;
        }
        s -= a[n];
        FOR(i, 1, n - 1) {
            a[i] = min(s, k - 1);
            s -= a[i];
        }
        FOR(i, 1, n) printf("%lld%c", a[i], " \n"[i == n]);
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}