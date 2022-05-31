#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define lowbit(x) (x & -x)
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
const int maxn = 1e5 + 5, INF = 1e9;

struct Query {
    int l, r, k, id, type;
} q[maxn << 2], q1[maxn << 2], q2[maxn << 2]; 
int n, m, a[maxn], totq, ans[maxn];

int t[maxn];

void add(int x, int v) {
    for (; x <= n; x += lowbit(x)) t[x] += v;
    return;
}

int sum(int x) {
    int res = 0;
    for (; x; x -= lowbit(x)) res += t[x];
    return res;
}

void solve(int l, int r, int ql, int qr) {
    if (ql > qr || l > r) return;
    if (l == r) {
        FOR(i, ql, qr) if (q[i].type == 2) ans[q[i].id] = l;
        return;
    }
    int p1 = 0, p2 = 0, mid = (l + r) >> 1;
    FOR(i, ql, qr) {
        if (q[i].type == 2) {
            int res = sum(q[i].r) - sum(q[i].l - 1);
            if (q[i].k <= res) q1[++p1] = q[i];
            else {
                q[i].k -= res;
                q2[++p2] = q[i];
            }
        } else {
            if (q[i].l <= mid) {
                add(q[i].id, q[i].type);
                q1[++p1] = q[i];
            } else q2[++p2] = q[i];
        }
    }
    FOR(i, 1, p1) if (q1[i].type != 2) add(q1[i].id, -q1[i].type);
    FOR(i, 1, p1) q[ql + i - 1] = q1[i];
    FOR(i, 1, p2) q[ql + p1 + i - 1] = q2[i];
    solve(l, mid, ql, ql + p1 - 1);
    solve(mid + 1, r, ql + p1, qr);
    return;
}

int main() {
    is >> n >> m;
    FOR(i, 1, n) {
        is >> a[i];
        q[++totq] = {a[i], -1, -1, i, 1};
    }
    FOR(i, 1, m) {
        char s[2]; is >> s;
        if (s[0] == 'Q') {
            int l, r, k; is >> l >> r >> k;
            q[++totq] = {l, r, k, i, 2};
        } else {
            int x, y; is >> x >> y;
            q[++totq] = {a[x], -1, -1, x, -1};
            a[x] = y;
            q[++totq] = {a[x], -1, -1, x, 1};
        }
    }
    memset(ans, -1, sizeof ans);
    solve(0, INF, 1, totq);
    FOR(i, 1, m) if (~ans[i]) os << ans[i] << '\n';
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}