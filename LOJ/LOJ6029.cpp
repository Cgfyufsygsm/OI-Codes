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
using ll = long long;
const int maxn = 1e5 + 5;

struct Node {
    ll mn, mx, add, sum;
} t[maxn << 2];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void pushUp(int k) {
    t[k].sum = t[L].sum + t[R].sum;
    t[k].mn = min(t[L].mn, t[R].mn);
    t[k].mx = max(t[L].mx, t[R].mx);
    return;
}

void pushTag(int i, int j, int k, ll v) {
    t[k].sum += (j - i + 1) * v;
    t[k].mn += v, t[k].mx += v;
    t[k].add += v;
    return;
}

void pushDown(int i, int j, int k) {
    if (t[k].add) {
        pushTag(i, M, L, t[k].add);
        pushTag(M + 1, j, R, t[k].add);
        t[k].add = 0;
    }
    return;
}

void add(int i, int j, int k, int x, int y, ll v) {
    if (x <= i && y >= j) {
        pushTag(i, j, k, v);
        return;
    }
    pushDown(i, j, k);
    if (x <= M) add(i, M, L, x, y, v);
    if (y > M) add(M + 1, j, R, x, y, v);
    pushUp(k);
    return;
}

ll div(ll a, ll b) {
    if (a % b == 0) return a / b;
    else if (a > 0) return a / b;
    else return a / b - 1;
}

void div(int i, int j, int k, int x, int y, ll v) {
    bool flg = (t[k].mx - t[k].mn == 0);
    flg |= (t[k].mx - t[k].mn == 1 && div(t[k].mx, v) - div(t[k].mn, v) == 1);
    if (x <= i && y >= j && flg) {
        pushTag(i, j, k, div(t[k].mn, v) - t[k].mn);
        return;
    }
    pushDown(i, j, k);
    if (x <= M) div(i, M, L, x, y, v);
    if (y > M) div(M + 1, j, R, x, y, v);
    pushUp(k);
    return;
}

ll querySum(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return t[k].sum;
    pushDown(i, j, k);
    ll ret = 0;
    if (x <= M) ret += querySum(i, M, L, x, y);
    if (y > M) ret += querySum(M + 1, j, R, x, y);
    return ret;
}

ll queryMin(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return t[k].mn;
    pushDown(i, j, k);
    ll ret = 1e18;
    if (x <= M) chkmin(ret, queryMin(i, M, L, x, y));
    if (y > M) chkmin(ret, queryMin(M + 1, j, R, x, y));
    return ret;
}

void build(int i, int j, int k) {
    if (i == j) {
        int x; is >> x;
        t[k].mn = t[k].mx = t[k].sum = x;
        return;
    }
    build(i, M, L), build(M + 1, j, R);
    pushUp(k);
    return;
}

int n, m;

int main() {
    is >> n >> m;
    build(0, n - 1, 1);
    while (m--) {
        int op, l, r, x;
        is >> op >> l >> r;
        if (op <= 2) is >> x;
        if (op == 1) add(0, n - 1, 1, l, r, x);
        else if (op == 2) div(0, n - 1, 1, l, r, x);
        else if (op == 3) os << queryMin(0, n - 1, 1, l, r) << '\n';
        else os << querySum(0, n - 1, 1, l, r) << '\n';
        // print();
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}