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
using ll = long long;
const int maxn = 50005;
int n, m, a[maxn], tot, block;
ll cnt1[maxn], cnt2[maxn], ans[maxn], tmp;

struct Query {
    int r1, r2, sgn, id;
} q[maxn << 2];

int main() {
    is >> n;
    FOR(i, 1, n) is >> a[i];
    is >> m;
    FOR(i, 1, m) {
        int l1, r1, l2, r2;
        is >> l1 >> r1 >> l2 >> r2;
        q[++tot] = {r1, r2, 1, i};
        q[++tot] = {l1 - 1, r2, -1, i};
        q[++tot] = {r1, l2 - 1, -1, i};
        q[++tot] = {l1 - 1, l2 - 1, 1, i};
    }
    block = n / sqrt(tot) + 1;
    sort(q + 1, q + tot + 1, [](const Query &a, const Query &b) {return ((a.r1 / block) ^ (b.r1 / block)) ? a.r1 < b.r1 : (((a.r1 / block) & 1) ? a.r2 > b.r2 : a.r2 < b.r2);});
    int r1 = 0, r2 = 0;
    FOR(i, 1, tot) {
        while (r1 < q[i].r1) {
            tmp += cnt2[a[++r1]];
            ++cnt1[a[r1]];
        }
        while (r2 < q[i].r2) {
            tmp += cnt1[a[++r2]];
            ++cnt2[a[r2]];
        }
        while (r1 > q[i].r1) {
            --cnt1[a[r1]];
            tmp -= cnt2[a[r1--]];
        }
        while (r2 > q[i].r2) {
            --cnt2[a[r2]];
            tmp -= cnt1[a[r2--]];
        }
        ans[q[i].id] += q[i].sgn * tmp;
    }
    FOR(i, 1, m) os << ans[i] << '\n';
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}