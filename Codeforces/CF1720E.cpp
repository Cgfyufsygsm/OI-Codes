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

const int maxn = 505, maxk = 2.5e5 + 5;
int n, k, a[maxn][maxn], vis[maxk], m;
int minx[maxk], maxx[maxk], miny[maxk], maxy[maxk];
int d[maxn][maxn];

int main() {
    cin >> n >> k;
    FOR(i, 1, n * n) minx[i] = miny[i] = 1e9;
    FOR(i, 1, n) FOR(j, 1, n) {
        cin >> a[i][j];
        if (!vis[a[i][j]]++) ++m;
        chkmin(minx[a[i][j]], i), chkmax(maxx[a[i][j]], i);
        chkmin(miny[a[i][j]], j), chkmax(maxy[a[i][j]], j);
    }
    if (k >= m) return cout << k - m << endl, 0;
    FOR(L, 1, n) {
        FOR(i, 1, n * n) if (vis[i]) {
            
        }
    }
    cout << 2 << endl;
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}