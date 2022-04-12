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

const int maxn = 4e5 + 5;

struct Node {
    int ch[2], mx;
    Node() {mx = -1e9;}
} t[maxn * 50];
int tot, root;

#define ls(u) t[u].ch[0]
#define rs(u) t[u].ch[1]
#define M ((i + j) >> 1)

void modify(int &k, int i, int j, int x, int v) {
    if (!k) k = ++tot;
    if (i == j) return t[k].mx = v, void();
    if (x <= M) modify(ls(k), i, M, x, v);
    else modify(rs(k), M + 1, j, x, v);
    t[k].mx = max(t[ls(k)].mx, t[rs(k)].mx);
    return;
}

int query(int k, int i, int j, int x, int y) {
    if (!k || x > y) return -1e9;
    if (x <= i && y >= j) return t[k].mx;
    int ret = -1e9;
    if (x <= M) chkmax(ret, query(ls(k), i, M, x, y));
    if (y > M) chkmax(ret, query(rs(k), M + 1, j, x, y));
    return ret;
}

int n, k, a[maxn];

int main() {
    cin >> n >> k;
    FOR(i, 1, k) {
        cin >> a[i];
        modify(root, 1, 1e9, a[i], i);
    }
    int ans = 1e9;
    FOR(i, k + 1, n) {
        cin >> a[i];
        chkmin(ans, i - query(root, 1, 1e9, 1, a[i] - 1));
    }
    if (ans > n) ans = -1;
    cout << ans << endl;
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}