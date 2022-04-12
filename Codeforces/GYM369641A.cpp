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

const int maxn = 3e5 + 5;
int f[maxn], a[maxn], d[maxn], n;
map<int, int> g[maxn];

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        FOR(i, 1, n) {
            cin >> a[i];
            g[i].clear();
        }
        FOR(i, 1, n - 1) d[i] = a[i + 1] - a[i];
        f[0] = 1;
        FOR(i, 1, n - 1) {
            g[i][d[i]] = i - 1;
            f[i] = f[i - 1] + 1;
            for (int x = d[i]; g[g[i][x]].count(x); x <<= 1) {
                g[i][x << 1] = g[g[i][x]][x];
                chkmin(f[i], f[g[i][x << 1]] + 1);
            }
        }
        cout << f[n - 1] << endl;
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}