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

using YangTY::fastIO::is;
using YangTY::fastIO::os;
const int maxn = 2e5 + 5;
int n, a[maxn], a0[maxn], m;
int bl[maxn], block, ans[maxn];
int cnt[maxn], cnt1[maxn];

struct Query {
    int l, r, id;
} q[maxn];

il void add(int id, int &cur) {chkmax(cur, ++cnt[a[id]]);}
il void del(int id) {--cnt[a[id]];}

int main() {
    is >> n >> m;
    block = n / sqrt(m) + 1;
    FOR(i, 1, n) is >> a[i], a0[i] = a[i];
    sort(a0 + 1, a0 + n + 1);
    int tota = unique(a0 + 1, a0 + n + 1) - a0 - 1;
    FOR(i, 1, n) {
        a[i] = lower_bound(a0 + 1, a0 + tota + 1, a[i]) - a0;
        bl[i] = (i - 1) / block + 1;
    }
    FOR(i, 1, m) is >> q[i].l >> q[i].r, q[i].id = i;
    sort(q + 1, q + m + 1, [](const Query &a, const Query &b) {return (bl[a.l] != bl[b.l]) ? a.l < b.l : a.r < b.r;});
    int l = 1, r = 0, lasBlk = 0, cur = 0;
    FOR(i, 1, m) {
        if (bl[q[i].l] == bl[q[i].r]) {
            FOR(j, q[i].l, q[i].r) chkmax(ans[q[i].id], ++cnt1[a[j]]);
            FOR(j, q[i].l, q[i].r) --cnt1[a[j]];
            continue;
        }
        if (lasBlk != bl[q[i].l]) {
            r = min(bl[q[i].l] * block, n), l = r + 1;
            memset(cnt, 0, sizeof cnt), cur = 0;
            lasBlk = bl[q[i].l];
        }
        while (r < q[i].r) add(++r, cur);
        int _l = l, tmp = cur;
        while (_l > q[i].l) add(--_l, tmp);
        ans[q[i].id] = tmp;
        while (_l < l) del(_l++);
    }
    FOR(i, 1, m) os << -ans[i] << '\n';
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}