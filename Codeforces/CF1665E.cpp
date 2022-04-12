#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
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

const int maxn = 1e5 + 5;

struct Node {
    int size, v[32];
} t[maxn << 2];

int n, a[maxn];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

Node operator+(const Node &a, const Node &b) {
    Node ret;
    ret.size = min(a.size + b.size, 31);
    int i = 1, j = 1, k = 1;
    while (k <= ret.size && i <= a.size && j <= b.size) {
        if (a.v[i] < b.v[j]) ret.v[k++] = a.v[i++];
        else ret.v[k++] = b.v[j++];
    }
    while (k <= ret.size && i <= a.size) ret.v[k++] = a.v[i++];
    while (k <= ret.size && j <= b.size) ret.v[k++] = b.v[j++];
    return ret;
}

void build(int i, int j, int k) {
    if (i == j) {
        t[k].size = 1;
        t[k].v[1] = a[i];
        return;
    }
    build(i, M, L), build(M + 1, j, R);
    t[k] = t[L] + t[R];
    return;
}

Node query(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return t[k];
    if (y <= M) return query(i, M, L, x, y);
    if (x > M) return query(M + 1, j, R, x, y);
    return query(i, M, L, x, M) + query(M + 1, j, R, M + 1, y);
}

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> n;
        FOR(i, 1, n) cin >> a[i];
        build(1, n, 1);
        int q; cin >> q;
        while (q--) {
            int l, r; cin >> l >> r;
            auto now = query(1, n, 1, l, r);
            int ans = 2e9;
            FOR(i, 1, now.size) FOR(j, i + 1, now.size) chkmin(ans, now.v[i] | now.v[j]);
            cout << ans << '\n';
        }
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}