#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define szof(a) ((int) (a).size())
#define debug(...) fprintf(stderr, __VA_ARGS__)
// #define debug(...) 1
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
const int maxn = 1e5 + 5;
int n, m;
int a[maxn], bl[maxn], block, tag[maxn], pos[maxn];
int lpos[maxn], rpos[maxn];

void modify(int L, int R, int l, int r, int k) {
    static int c1[maxn], c2[maxn], t1, t2;
    t1 = t2 = 0;
    FOR(i, L, R) (l <= pos[i] && pos[i] <= r) ? a[c1[++t1] = pos[i]] += k : c2[++t2] = pos[i];
    while (t1 && t2) pos[R--] = (a[c1[t1]] > a[c2[t2]]) ? c1[t1--] : c2[t2--];
    while (t1) pos[R--] = c1[t1--];
    while (t2) pos[R--] = c2[t2--];
    return;
}

void modify(int l, int r, int k) {
    modify(lpos[bl[l]], rpos[bl[l]], l, min(rpos[bl[l]], r), k);
    if (bl[l] != bl[r]) modify(lpos[bl[r]], rpos[bl[r]], lpos[bl[r]], r, k);
    FOR(i, bl[l] + 1, bl[r] - 1) tag[i] += k;
    return;
}

int c[maxn], tot;

int query(int l, int r, int k) {
    if (r - l + 1 < k) return -1;
    tot = 0;
    FOR(i, l, min(rpos[bl[l]], r)) c[++tot] = a[i] + tag[bl[l]];
    if (bl[l] != bl[r]) FOR(i, lpos[bl[r]], r) c[++tot] = a[i] + tag[bl[r]];
    sort(c + 1, c + tot + 1);
    int L = c[1], R = c[tot], ans = 0;
    FOR(i, bl[l] + 1, bl[r] - 1) chkmin(L, a[pos[lpos[i]]] + tag[i]), chkmax(R, a[pos[rpos[i]]] + tag[i]);
    while (L <= R) {
        int mid = (0ll + L + R) / 2;
        int cur = upper_bound(c + 1, c + tot + 1, mid) - c - 1;
        FOR(i, bl[l] + 1, bl[r] - 1) {
            if (mid < a[pos[lpos[i]]] + tag[i]) continue;
            if (a[pos[rpos[i]]] + tag[i] <= mid) {
                cur += rpos[i] - rpos[i - 1];
                continue;
            }
            int x = 1, y = rpos[i] - rpos[i - 1], tmp = 0;
            while (x <= y) {
                int M = (x + y) >> 1;
                if (a[pos[rpos[i - 1] + M]] + tag[i] <= mid)
                    tmp = M, x = M + 1;
                    else y = M - 1;
            }
            cur += tmp;
        }
        if (cur >= k) ans = mid, R = mid - 1;
        else L = mid + 1;
    }
    return ans;
}

int main() {
    is >> n >> m;
    block = 300;
    FOR(i, 1, n) {
        is >> a[i], pos[i] = i;
        bl[i] = (i - 1) / block + 1;
    }
    FOR(i, 1, bl[n]) {
        lpos[i] = (i - 1) * block + 1, rpos[i] = min(n, i * block);
        sort(pos + lpos[i], pos + rpos[i] + 1, [](const int &x, const int &y) {return a[x] < a[y];});
    }
    while (m--) {
        int op, l, r, k;
        is >> op >> l >> r >> k;
        if (op == 1) os << query(l, r, k) << '\n';
        else modify(l, r, k);
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}