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
using ll = long long;
const int maxn = 3e5 + 5;
int n, m, K, ans[maxn], totq;
vector<int> pos[maxn];
struct Query {
    int type, id, x, y; ll k;
} q[maxn << 2], q1[maxn << 2], q2[maxn << 2];

ll t[maxn];

void add(int x, ll v) {
    for (; x <= m; x += lowbit(x)) t[x] += v;
    return;
}

ll query(int x) {
    ll ret = 0;
    for (; x; x -= lowbit(x)) ret += t[x];
    return ret;
}

il void add(int x, int y, ll v) {
    return add(x, v), add(y + 1, -v);
}

void solve(int l, int r, int ql, int qr) {
    if (l > r || ql > qr || l > K) return;
    if (l == r) {
        FOR(i, ql, qr) if (q[i].type == 2) ans[q[i].id] = l;
        return;
    }
    int mid = (l + r) >> 1, cnt1 = 0, cnt2 = 0;
    FOR(i, ql, qr) {
        if (q[i].type == 1) {
            if (q[i].id <= mid) {
                add(q[i].x, q[i].y, q[i].k);
                q1[++cnt1] = q[i];
            } else q2[++cnt2] = q[i];
        } else {
            int res = 0;
            for (auto x : pos[q[i].id]) {
                res += query(x);
                if (res > q[i].k) break;
            }
            if (q[i].k <= res) q1[++cnt1] = q[i];
            else {
                q[i].k -= res;
                q2[++cnt2] = q[i];
            }
        }
    }
    FOR(i, 1, cnt1) if (q1[i].type == 1) add(q1[i].x, q1[i].y, -q1[i].k);
    FOR(i, 1, cnt1) q[ql + i - 1] = q1[i];
    FOR(i, 1, cnt2) q[ql + cnt1 + i - 1] = q2[i];
    solve(l, mid, ql, ql + cnt1 - 1);
    solve(mid + 1, r, ql + cnt1, qr);
    return;
}

int main() {
    is >> n >> m;
    FOR(i, 1, m) {
        int o; is >> o;
        pos[o].push_back(i);
    }
    FOR(i, 1, n) is >> q1[i].k, q1[i].id = i, q1[i].type = 2;
    is >> K;
    FOR(i, 1, K) {
        int x, y, k;
        is >> x >> y >> k;
        if (x <= y) q[++totq] = {1, i, x, y, k};
        else q[++totq] = {1, i, x, m, k}, q[++totq] = {1, i, 1, y, k};
    }
    FOR(i, 1, n) q[++totq] = q1[i];
    memset(ans, -1, sizeof ans);
    solve(1, K + 1, 1, totq);
    FOR(i, 1, n) {
        if (~ans[i]) os << ans[i] << '\n';
        else os << "NIE\n";
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}