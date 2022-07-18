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
const int maxn = 60005;
int n, m, block;
char s[maxn];
int a[maxn];
unsigned short t[1 << 26 | 5];
ll ans[maxn], cur;

struct Query {
    int l, r, id;
} q[maxn];

void add(int id) {
    cur += t[a[id]]++;
    FOR(i, 0, 25) cur += t[a[id] ^ (1 << i)];
    return;
}

void del(int id) {
    cur -= --t[a[id]];
    FOR(i, 0, 25) cur -= t[a[id] ^ (1 << i)];
    return;
}

int main() {
    is >> n >> m;
    is >> (s + 1);
    FOR(i, 1, n) a[i] = (1 << (s[i] - 'a')) ^ a[i - 1];
    block = n / (sqrt(2 * m / 3) + 1) + 1;
    FOR(i, 1, m) is >> q[i].l >> q[i].r, q[i].id = i, --q[i].l;
    sort(q + 1, q + m + 1, [](const Query &a, const Query &b) {
        return ((a.l / block) ^ (b.l / block)) ? a.l < b.l : (((a.l / block) & 1) ? a.r > b.r : a.r < b.r);
    });
    int l = 0, r = -1;
    FOR(i, 1, m) {
        while (r < q[i].r) add(++r);
        while (l > q[i].l) add(--l);
        while (r > q[i].r) del(r--);
        while (l < q[i].l) del(l++);
        ans[q[i].id] = cur;
    }
    FOR(i, 1, m) os << ans[i] << '\n';
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}