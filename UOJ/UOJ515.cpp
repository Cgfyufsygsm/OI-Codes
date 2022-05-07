#include <bits/stdc++.h>
#include <fastio.hpp>
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

using fastIO::is;
using fastIO::os;
const int maxn = 1e6 + 5;
int n, m, a[maxn], ans[maxn];
vector<pair<int, int> > ch[maxn];
vector<int> q[maxn];

struct Node {
    int tag, val, mx, se;
    Node() {mx = 2e9, se = -1, tag = -1, val = 0;}
} t[maxn << 2];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void pushUp(int k) {
    if (t[L].mx == t[R].mx) {
        t[k].mx = t[L].mx;
        t[k].se = max(t[L].se, t[R].se);
    } else if (t[L].mx > t[R].mx) {
        t[k].mx = t[L].mx;
        t[k].se = max(t[R].mx, t[L].se);
    } else if (t[L].mx < t[R].mx) {
        t[k].mx = t[R].mx;
        t[k].se = max(t[L].mx, t[R].se);
    }
    return;
}

void pushTag(int k, int v, int add) {
    if (v < t[k].mx) {
        t[k].mx = t[k].tag = v;
        t[k].val += add;
    }
    return;
}

void pushDown(int k) {
    if (~t[k].tag) {
        pushTag(L, t[k].tag, t[k].val);
        pushTag(R, t[k].tag, t[k].val);
        t[k].tag = -1, t[k].val = 0;
    }
    return;
}

void toMin(int i, int j, int k, int l, int r, int v) {
    if (t[k].mx <= v) return;
    if (l <= i && j <= r && v > t[k].se) {
        pushTag(k, v, 1);
        return;
    }
    pushDown(k);
    if (l <= M) toMin(i, M, L, l, r, v);
    if (r > M) toMin(M + 1, j, R, l, r, v);
    pushUp(k);
    return;
}

int query(int i, int j, int k, int x) {
    if (i == j) return t[k].val;
    pushDown(k);
    if (x <= M) return query(i, M, L, x);
    else return query(M + 1, j, R, x);
}

int main() {
    is >> n >> m;
    FOR(i, 1, n) {
        is >> a[i];
        ch[i].push_back({0, a[i]});
    }
    FOR(i, 1, m) {
        int op, x, v; is >> op >> x;
        if (op == 1) {
            is >> v;
            ch[x].push_back({i, v});
        } else {
            q[x].push_back(i);
        }
        ans[i] = -1;
    }
    DEC(pos, n, 1) {
        for (int i = 0; i < (int)ch[pos].size(); ++i) {
            int l = ch[pos][i].first, r = (i == (int)ch[pos].size() - 1 ? m : ch[pos][i + 1].first - 1);
            toMin(0, m, 1, l, r, ch[pos][i].second);
        }
        for (auto &p : q[pos]) ans[p] = query(0, m, 1, p);
    }
    FOR(i, 1, m) if (~ans[i]) os << ans[i] << '\n';
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}