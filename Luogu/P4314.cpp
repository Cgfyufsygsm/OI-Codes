#include <bits/stdc++.h>
#include <fastio.hpp>
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

using fastIO::is;
using fastIO::os;
const int maxn = 1e5 + 5;

struct Node {
    int add, addh, cov, covh, vis, mx, mxh;
} t[maxn << 2];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void pushAdd(int k, int add, int addh) {
    if (t[k].vis) {
        chkmax(t[k].covh, t[k].cov + addh);
        chkmax(t[k].mxh, t[k].mx + addh);
        t[k].mx += add, t[k].cov += add;
    } else {
        chkmax(t[k].addh, t[k].add + addh);
        chkmax(t[k].mxh, t[k].mx + addh);
        t[k].mx += add, t[k].add += add;
    }
    return;
}

void pushCov(int k, int cov, int covh) {
    if (t[k].vis) chkmax(t[k].covh, covh);
    else t[k].vis = 1, t[k].covh = covh;
    t[k].mx = t[k].cov = cov;
    chkmax(t[k].mxh, covh);
    return;
}

void pushDown(int k) {
    pushAdd(L, t[k].add, t[k].addh);
    pushAdd(R, t[k].add, t[k].addh);
    t[k].add = t[k].addh = 0;
    if (t[k].vis) {
        pushCov(L, t[k].cov, t[k].covh);
        pushCov(R, t[k].cov, t[k].covh);
        t[k].vis = t[k].cov = t[k].covh = 0;
    }
    return;
}

void pushUp(int k) {
    t[k].mx = max(t[L].mx, t[R].mx);
    t[k].mxh = max(t[L].mxh, t[R].mxh);
    return;
}

void add(int i, int j, int k, int x, int y, int v) {
    if (x <= i && y >= j) {
        pushAdd(k, v, v);
        return;
    }
    pushDown(k);
    if (x <= M) add(i, M, L, x, y, v);
    if (y > M) add(M + 1, j, R, x, y, v);
    return pushUp(k);
}

void cover(int i, int j, int k, int x, int y, int v) {
    if (x <= i && y >= j) {
        pushCov(k, v, v);
        return;
    }
    pushDown(k);
    if (x <= M) cover(i, M, L, x, y, v);
    if (y > M) cover(M + 1, j, R, x, y, v);
    return pushUp(k);
}

int query(int i, int j, int k, int x, int y, int op) {
    if (x <= i && y >= j) return op ? t[k].mxh : t[k].mx;
    pushDown(k);
    int ret = -2e9;
    if (x <= M) chkmax(ret, query(i, M, L, x, y, op));
    if (y > M) chkmax(ret, query(M + 1, j, R, x, y, op));
    return ret;
}

void build(int i, int j, int k) {
    if (i == j) {
        int x; is >> x;
        t[k].mx = t[k].mxh = x;
        return;
    }
    build(i, M, L), build(M + 1, j, R);
    return pushUp(k);
}

int n, m;
char s[2];

int main() {
    is >> n;
    build(1, n, 1);
    is >> m;
    while (m--) {
        int x, y, z;
        is >> s >> x >> y;
        if (s[0] == 'Q') os << query(1, n, 1, x, y, 0) << '\n';
        else if (s[0] == 'A') os << query(1, n, 1, x, y, 1) << '\n';
        else {
            is >> z;
            if (s[0] == 'P') add(1, n, 1, x, y, z);
            else cover(1, n, 1, x, y, z);
        }
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}