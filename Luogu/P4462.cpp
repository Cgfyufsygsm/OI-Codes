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
const int maxn = 1e5 + 5;
int n, m, k, a[maxn], block;
ll cnt[maxn], ans[maxn], tmp;

struct Query {
    int l, r, id;
} q[maxn];

il void add(int id) {
    ++cnt[a[id]];
    tmp += cnt[a[id] ^ k];
    return;
}

il void del(int id) {
    --cnt[a[id]];
    tmp -= cnt[a[id] ^ k];
    return;
}

int main() {
    is >> n >> m >> k;
    block = n / (sqrt(m * 2.0 / 3.0) + 1) + 1;
    FOR(i, 1, n) is >> a[i], a[i] ^= a[i - 1];
    FOR(i, 1, m) is >> q[i].l >> q[i].r, q[i].id = i, --q[i].l;
    sort(q + 1, q + m + 1, [](const Query &a, const Query &b) {return ((a.l / block) ^ (b.l / block)) ? a.l < b.l : (((a.l / block) & 1) ? a.r < b.r : a.r > b.r);});
    int l = 0, r = -1;
    FOR(i, 1, m) {
        while (q[i].l < l) add(--l);
        while (q[i].r > r) add(++r);
        while (q[i].l > l) del(l++);
        while (q[i].r < r) del(r--);
        ans[q[i].id] = tmp;
    }
    FOR(i, 1, m) os << ans[i] << '\n';
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}