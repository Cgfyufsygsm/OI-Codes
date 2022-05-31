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
const int maxn = 5e4 + 5;
int n, m, type[maxn], ans[maxn];

struct Node {
    ll sum, tag;
} t[maxn << 2];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void pushDown(int i, int j, int k) {
    if (!t[k].tag) return;
    t[L].tag += t[k].tag, t[R].tag += t[k].tag;
    t[L].sum += (M - i + 1) * t[k].tag, t[R].sum += (j - M) * t[k].tag;
    t[k].tag = 0;
    return;
}

void pushUp(int k) {
    t[k].sum = t[L].sum + t[R].sum;
    return;
}

void modify(int i, int j, int k, int x, int y, ll v) {
    if (x <= i && y >= j) {
        t[k].tag += v;
        t[k].sum += (j - i + 1) * v;
        return;
    }
    pushDown(i, j, k);
    if (x <= M) modify(i, M, L, x, y, v);
    if (y > M) modify(M + 1, j, R, x, y, v);
    pushUp(k);
    return;
}

ll query(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return t[k].sum;
    pushDown(i, j, k);
    ll ret = 0;
    if (x <= M) ret += query(i, M, L, x, y);
    if (y > M) ret += query(M + 1, j, R, x, y);
    return ret;
}

struct Query {
    int type, l, r, id;
    ll k;
} q[maxn << 1], q1[maxn << 1], q2[maxn << 1];

void solve(int l, int r, int ql, int qr) {
    if (l > r || ql > qr) return;
    if (l == r) {
        FOR(i, ql, qr) if (q[i].type == 2) ans[q[i].id] = l;
        return;
    }
    int mid = (l + r) >> 1, cnt1 = 0, cnt2 = 0;
    FOR(i, ql, qr) {
        if (q[i].type == 1) {
            if (q[i].k > mid) {
                modify(1, n, 1, q[i].l, q[i].r, 1);
                q2[++cnt2] = q[i];
            } else q1[++cnt1] = q[i];
        } else {
            ll res = query(1, n, 1, q[i].l, q[i].r);
            if (q[i].k <= res) q2[++cnt2] = q[i];
            else {
                q[i].k -= res;
                q1[++cnt1] = q[i];
            }
        }
    }
    FOR(i, 1, cnt2) if (q2[i].type == 1) modify(1, n, 1, q2[i].l, q2[i].r, -1);
    FOR(i, 1, cnt1) q[ql + i - 1] = q1[i];
    FOR(i, 1, cnt2) q[ql + cnt1 + i - 1] = q2[i];
    solve(l, mid, ql, ql + cnt1 - 1);
    solve(mid + 1, r, ql + cnt1, qr);
    return;
}

int main() {
    is >> n >> m;
    FOR(i, 1, m) {
        is >> q[i].type >> q[i].l >> q[i].r >> q[i].k;
        q[i].id = i;
        type[i] = q[i].type;
    }
    solve(-n, n, 1, m);
    FOR(i, 1, m) if (type[i] == 2) os << ans[i] << '\n';
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}