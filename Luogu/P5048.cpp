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
const int maxn = 5e5 + 5, B = 709, block = 707;
int n, a0[maxn], a[maxn], bl[maxn], m;
int mode[B][B];
vector<int> vec[maxn];
int at[maxn], buc[maxn];

int query(int l, int r) {
    int ans = 0;
    if (bl[l] + 1 >= bl[r]) {
        FOR(i, l, r) buc[a[i]] = 0;
        FOR(i, l, r) chkmax(ans, ++buc[a[i]]);
    } else {
        ans = mode[bl[l] + 1][bl[r] - 1];
        FOR(i, l, bl[l] * block) {
            int p = at[i];
            while (p + ans < vec[a[i]].size() && vec[a[i]][p + ans] <= r) ++ans;
        }
        FOR(i, (bl[r] - 1) * block + 1, r) {
            int p = at[i];
            while (p - ans >= 0 && vec[a[i]][p - ans] >= l) ++ans;
        }
    }
    return ans;
}

int main() {
    is >> n >> m;
    FOR(i, 1, n) is >> a[i], a0[i] = a[i];
    sort(a0 + 1, a0 + n + 1);
    int tot = unique(a0 + 1, a0 + n + 1) - a0 - 1;
    FOR(i, 1, n) {
        bl[i] = (i - 1) / block + 1;
        a[i] = lower_bound(a0 + 1, a0 + tot + 1, a[i]) - a0;
        vec[a[i]].push_back(i);
        at[i] = vec[a[i]].size() - 1;
    }
    FOR(i, 1, bl[n]) {
        memset(buc, 0, sizeof buc);
        FOR(j, i, bl[n]) {
            mode[i][j] = mode[i][j - 1];
            FOR(k, (j - 1) * block + 1, min(j * block, n))
                chkmax(mode[i][j], ++buc[a[k]]);
        }
    }
    int las = 0;
    while (m--) {
        int l, r; is >> l >> r;
        l ^= las, r ^= las;
        os << (las = query(l, r)) << '\n';
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}