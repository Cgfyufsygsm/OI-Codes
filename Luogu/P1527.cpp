#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define lowbit(x) (x & -x)

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
const int maxn = 505, maxq = 4e5 + 5;
int a[maxn][maxn], n, m, totq, ans[maxq];

struct Query {
    int type, id, x1, y1, x2, y2, k;
} q[maxq], q1[maxq], q2[maxq];

int t[maxn][maxn];

void add(int x, int y, int v) {
    // debug("added (%x, %d) %d\n", x, y, v);
    for (int xx = x; xx <= n; xx += lowbit(xx))
        for (int yy = y; yy <= n; yy += lowbit(yy))
            t[xx][yy] += v;
    return;
}

int query(int x, int y) {
    int ret = 0;
    for (int xx = x; xx; xx -= lowbit(xx))
        for (int yy = y; yy; yy -= lowbit(yy))
            ret += t[xx][yy];
    return ret;
}

il int query(int x1, int y1, int x2, int y2) {
    return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
}

void solve(int l, int r, int ql, int qr) {
    if (l > r || ql > qr) return;
    if (l == r) {
        FOR(i, ql, qr) if (q[i].type == 2) ans[q[i].id] = l;
        return;
    }
    int cnt1 = 0, cnt2 = 0, mid = (l + r) >> 1;
    FOR(i, ql, qr) {
        if (q[i].type == 1) {
            if (q[i].k <= mid) {
                add(q[i].x1, q[i].y1, 1);
                q1[++cnt1] = q[i];
            } else q2[++cnt2] = q[i];
        } else {
            int res = query(q[i].x1, q[i].y1, q[i].x2, q[i].y2);
            if (q[i].k <= res) q1[++cnt1] = q[i];
            else {
                q[i].k -= res;
                q2[++cnt2] = q[i];
            }
        }
    }
    FOR(i, 1, cnt1) if (q1[i].type == 1) add(q1[i].x1, q1[i].y1, -1);
    FOR(i, 1, cnt1) q[ql + i - 1] = q1[i];
    FOR(i, 1, cnt2) q[ql + cnt1 + i - 1] = q2[i];
    solve(l, mid, ql, ql + cnt1 - 1);
    solve(mid + 1, r, ql + cnt1, qr);
    return;
}

int main() {
    is >> n >> m;
    FOR(i, 1, n) FOR(j, 1, n) is >> a[i][j], q[++totq] = {1, -1, i, j, -1, -1, a[i][j]};
    FOR(i, 1, m) {
        int x1, y1, x2, y2, k;
        is >> x1 >> y1 >> x2 >> y2 >> k;
        q[++totq] = {2, i, x1, y1, x2, y2, k};
    }
    solve(0, 1e9, 1, totq);
    FOR(i, 1, m) os << ans[i] << '\n';
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}