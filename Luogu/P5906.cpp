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
const int maxn = 2e5 + 5;
int n, m, a[maxn], a0[maxn], block, bel[maxn], lpos[maxn], rpos[maxn];

struct Node {
    int l, r, id;
} q[maxn], stk[maxn];
int minp[maxn], maxp[maxn], top, ans[maxn];

int add(int x, int op, int sb = 1) {
    if (op) stk[++top] = {minp[a[x]], maxp[a[x]], a[x]};
    chkmax(maxp[a[x]], x), chkmin(minp[a[x]], x);
    return max(x - minp[a[x]], maxp[a[x]] - x);
}

void rollBack() {
    while (top) {
        minp[stk[top].id] = stk[top].l;
        maxp[stk[top].id] = stk[top].r;
        --top;
    }
    return;
}

int main() {
    is >> n;
    FOR(i, 1, n) is >> a[i], a0[i] = a[i];
    is >> m;
    sort(a0 + 1, a0 + n + 1);
    int tota = unique(a0 + 1, a0 + n + 1) - a0 - 1;
    block = n / (sqrt(m * 2 / 3) + 1) + 1;
    FOR(i, 1, n) {
        a[i] = lower_bound(a0 + 1, a0 + tota + 1, a[i]) - a0;
        bel[i] = (i - 1) / block + 1;
    }
    FOR(i, 1, bel[n]) lpos[i] = (i - 1) * block + 1, rpos[i] = (i == bel[n]) ? n : block * i;
    memset(minp, 0x3f, sizeof minp), memset(maxp, 0, sizeof maxp);
    FOR(i, 1, m) {
        is >> q[i].l >> q[i].r, q[i].id = i;
        if (bel[q[i].l] == bel[q[i].r]) {
            FOR(j, q[i].l, q[i].r) chkmax(ans[q[i].id], add(j, 1));
            rollBack();
        }
    }
    sort(q + 1, q + m + 1, [](const Node &a, const Node &b) {return (bel[a.l] ^ bel[b.l]) ? a.l < b.l : a.r < b.r;});
    int nowBlk = 0, l = 1, r = 0, cur = 0;
    FOR(i, 1, m) {
        if (nowBlk != bel[q[i].l]) {
            l = rpos[bel[q[i].l]] + 1, r = rpos[bel[q[i].l]], cur = 0;
            memset(minp, 0x3f, sizeof minp), memset(maxp, 0, sizeof maxp);
            nowBlk = bel[q[i].l];
        }
        if (bel[q[i].l] != bel[q[i].r]) {
            while (r < q[i].r) chkmax(cur, add(++r, 0));
            int tmp = cur, _l = l;
            while (_l > q[i].l) chkmax(cur, add(--_l, 1));
            ans[q[i].id] = cur, cur = tmp, rollBack();
        }
    }
    FOR(i, 1, m) os << ans[i] << '\n';
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}