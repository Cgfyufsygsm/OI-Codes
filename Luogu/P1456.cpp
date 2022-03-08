#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

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

const int maxn = 100000 + 5;

struct node {
    int val, ch[2], rt;
} t[maxn];

#define ls(x) t[x].ch[0]
#define rs(x) t[x].ch[1]

mt19937 rnd(20041031);

int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (t[x].val < t[y].val) swap(x, y);
    if (rnd() & 1) swap(ls(x), rs(x));
    rs(x) = merge(rs(x), y);
    t[rs(x)].rt = x;
    return x;
}

int find(int x) {return t[x].rt == x ? x : t[x].rt = find(t[x].rt);}

int weaken(int x) {
    t[x].val >>= 1;
    t[ls(x)].rt = ls(x), t[rs(x)].rt = rs(x);
    int rt = merge(ls(x), rs(x));
    ls(x) = rs(x) = 0, t[x].rt = x;
    rt = merge(rt, x);
    return rt;
}

void solve(int n) {
    FOR(i, 1, n) cin >> t[i].val, t[i].rt = i, t[i].ch[0] = t[i].ch[1] = 0;
    int m; cin >> m;
    while (m--) {
        int x, y; cin >> x >> y;
        x = find(x), y = find(y);
        if (x == y) {
            cout << "-1\n";
            continue;
        }
        x = weaken(x), y = weaken(y);
        int rt = merge(x, y);
        cout << t[rt].val << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    int n;
    while (cin >> n) solve(n);
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}