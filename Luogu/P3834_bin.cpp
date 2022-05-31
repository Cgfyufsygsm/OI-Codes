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

const int maxn = 2e5 + 5;
const int INF = 1e9;
int n, m, totv, totq, a0[maxn], a[maxn], ans[maxn];
using fastIO::is;
using fastIO::os;

struct Query {
    int l, r, k, id, type;
} q[maxn << 1], q1[maxn << 1], q2[maxn << 1];

int t[maxn];

void add(int x, int v) {
    for (; x <= n; x += lowbit(x)) t[x] += v;
    return;
}

int sum(int x) {
    int res = 0;
    for (; x; x  -= lowbit(x)) res += t[x];
    return res;
}

void solve(int l, int r, int ql, int qr) {
    if (ql > qr) return;
    if (l == r) {
        FOR(i, ql, qr) if (q[i].type == 2) ans[q[i].id] = l;
        return;
    }
    int mid = (l + r) >> 1;
    int p1 = 0, p2 = 0;
    FOR(i, ql, qr) {
        if (q[i].type == 1) {
            if (q[i].l <= mid) {
                add(q[i].id, 1);
                q1[++p1] = q[i];
            } else q2[++p2] = q[i];
        } else {
            int res = sum(q[i].r) - sum(q[i].l - 1);
            if (res >= q[i].k) q1[++p1] = q[i];
            else {
                q[i].k -= res;
                q2[++p2] = q[i];
            }
        }
    }
    FOR(i, 1, p1) if (q1[i].type == 1) add(q1[i].id, -1);
    FOR(i, 1, p1) q[ql + i - 1] = q1[i];
    FOR(i, 1, p2) q[ql + p1 + i - 1] = q2[i];
    solve(l, mid, ql, ql + p1 - 1);
    solve(mid + 1, r, ql + p1, qr);
    return;
}

int main() {
    is >> n >> m;
    FOR(i, 1, n) is >> a0[i], a[i] = a0[i];
    sort(a0 + 1, a0 + n + 1);
    totv = unique(a0 + 1, a0 + n + 1) - a0 - 1;
    FOR(i, 1, n) a[i] = lower_bound(a0 + 1, a0 + totv + 1, a[i]) - a0, q[++totq] = {a[i], -1, -1, i, 1};
    FOR(i, 1, m) {
        int x, y, k; is >> x >> y >> k;
        q[++totq] = {x, y, k, i, 2};
    }
    solve(1, totv, 1, totq);
    FOR(i, 1, m) os << a0[ans[i]] << '\n';
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}