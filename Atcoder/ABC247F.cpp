#include <bits/stdc++.h>
#include <atcoder/modint>
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

using mint = atcoder::modint998244353;
const int maxn = 2e5 + 5;
int p[maxn], q[maxn], n;
mint f[maxn][2][2];

struct UnionFind {
    int fa[maxn << 1], size[maxn << 1];
    void init() {
        FOR(i, 1, n << 1) fa[i] = i, size[i] = 1;
        return;
    }
    int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}
    void uni(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        fa[x] = y, size[y] += size[x];
        return;
    }
} ufs;

il mint calc(int x) {return f[x][1][0] + f[x][0][1] + f[x][1][1];}

int main() {
    cin >> n;
    f[1][0][0] = f[1][1][1] = 1;
    FOR(i, 2, n) FOR(k, 0, 1) {
        f[i][0][k] += f[i - 1][1][k];
        f[i][1][k] += f[i - 1][0][k] + f[i - 1][1][k];
    }
    FOR(i, 1, n) cin >> p[i];
    FOR(i, 1, n) cin >> q[i];
    ufs.init();
    FOR(i, 1, n) ufs.uni(p[i], i + n), ufs.uni(q[i], i + n);
    mint ans = 1;
    FOR(i, 1, n << 1) if (ufs.fa[i] == i) ans *= calc(ufs.size[i] >> 1);
    cout << ans.val() << endl;
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}