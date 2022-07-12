#include <bits/stdc++.h>
#include <fastio.hpp>
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

using fastIO::is;
using fastIO::os;
const int maxn = 1e5 + 5, blk = 505;
int f[blk][blk], g[blk][maxn];
int n, c, m, a[maxn], bl[maxn], block;
int buc[maxn];

il int cnt(int l, int r, int x) {
    return g[l][x] - g[r + 1][x];
}

int query(int l, int r) {
    int ret = 0;
    if (bl[l] + 1 >= bl[r]) {
        FOR(i, l, r) {
            ++buc[a[i]];
            if (!(buc[a[i]] & 1)) ++ret;
            else if (buc[a[i]] != 1) --ret;
        }
        FOR(i, l, r) --buc[a[i]];
    } else {
        ret = f[bl[l] + 1][bl[r] - 1];
        FOR(i, l, bl[l] * block) {
            ++buc[a[i]];
            int tmp = buc[a[i]] + cnt(bl[l] + 1, bl[r] - 1, a[i]);
            if (!(tmp & 1)) ++ret;
            else if (tmp != 1) --ret;
        }
        FOR(i, (bl[r] - 1) * block + 1, r) {
            ++buc[a[i]];
            int tmp = buc[a[i]] + cnt(bl[l] + 1, bl[r] - 1, a[i]);
            if (!(tmp & 1)) ++ret;
            else if (tmp != 1) --ret;
        }
        FOR(i, l, bl[l] * block) --buc[a[i]];
        FOR(i, (bl[r] - 1) * block + 1, r) --buc[a[i]];
    }
    return ret;
}

int main() {
    is >> n >> c >> m;
    block = 350;
    FOR(i, 1, n) {
        is >> a[i];
        bl[i] = (i - 1) / block + 1;
    }
    FOR(i, 1, bl[n]) {
        int cur = 0;
        FOR(j, (i - 1) * block + 1, n) {
            ++g[i][a[j]];
            (g[i][a[j]] & 1) ? ((g[i][a[j]] > 1) ? --cur : 0) : ++cur;
            if (bl[j] != bl[j + 1]) f[i][bl[j]] = cur;
        }
    }
    int last = 0;
    while (m--) {
        int l, r; is >> l >> r;
        l = (l + last) % n + 1, r = (r + last) % n + 1;
        if (l > r) swap(l, r);
        os << (last = query(l, r)) << '\n';
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}