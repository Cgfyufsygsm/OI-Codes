#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
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

const int maxn = 5e5 + 5, m = 3;
using fastIO::is;
using fastIO::os;

int n, fa[20], b[20];
char a[4][maxn];

int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}

int merge(int x, int y) {
    int xx = find(x), yy = find(y);
    if (xx != yy) return fa[xx] = yy, 1;
    return 0;
}

struct Node {
    int l[4], r[4], lc[4], rc[4], sum;
    void init(int pos) {
        FOR(i, 1, m) lc[i] = rc[i] = a[i][pos] - '0', sum += lc[i], fa[i] = i;
        FOR(i, 1, m - 1) if (lc[i] == lc[i + 1] && lc[i]) sum -= merge(i, i + 1);
        FOR(i, 1, m) l[i] = r[i] = find(i);
    }
} t[maxn << 2], tmp;

Node merge(const Node &l, const Node &r) {
    tmp.sum = l.sum + r.sum;
    FOR(i, 1, m) tmp.lc[i] = l.lc[i], tmp.rc[i] = r.rc[i];
    FOR(i, 1, m) tmp.l[i] = tmp.r[i] = 0;

    FOR(i, 1, m * 4) fa[i] = i;
    FOR(i, 1, m) {
        merge(i, l.l[i]), merge(i + m, l.r[i]);
        merge(i + 2 * m, r.l[i] + 2 * m), merge(i + 3 * m, r.r[i] + m * 2);
    }
    FOR(i, 1, m) if (l.rc[i] == r.lc[i] && l.rc[i]) 
        tmp.sum -= merge(i + m, i + m * 2);
    memset(b, 0, sizeof b);
    FOR(i, 1, m) {
        if (!b[find(i)]) b[find(i)] = i;
        tmp.l[i] = b[find(i)];
    }
    FOR(i, m * 3 + 1, m * 4) {
        if (!b[find(i)]) b[find(i)] = i - 2 * m;
        tmp.r[i - m * 3] = b[find(i)];
    }
    return tmp;
}

il Node operator+(const Node &a, const Node &b) {return merge(a, b);}

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void build(int i, int j, int k) {
    if (i == j) {
        t[k].init(i);
        return;
    }
    build(i, M, L), build(M + 1, j, R);
    t[k] = t[L] + t[R];
    return;
}

Node query(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return t[k];
    if (y <= M) return query(i, M, L, x, y);
    if (x > M) return query(M + 1, j, R, x, y);
    return query(i, M, L, x, M) + query(M + 1, j, R, M + 1, y);
}

int main() {
    is >> n;
    FOR(i, 1, 3) is >> a[i] + 1;
    build(1, n, 1);
    int q; is >> q;
    while (q--) {
        int l, r; is >> l >> r;
        os << query(1, n, 1, l, r).sum << '\n';
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}