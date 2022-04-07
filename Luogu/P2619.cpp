#include <bits/stdc++.h>
#include <fastio.hpp>
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

using fastIO::is;
using fastIO::os;

const int maxn = 5e4 + 5, maxm = 1e5 + 5;
struct Edge {
    int u, v, w, c;
    il bool operator<(const Edge &rhs) const {return w < rhs.w;}
} e[maxm];
int n, m, need, cntw = 1, fa[maxn];

int find(int u) {return fa[u] == u ? u : fa[u] = find(fa[u]);}

bool add(int i) {
    int u = find(e[i].u), v = find(e[i].v);
    if (u == v) return false;
    else return fa[u] = v, true;
}

int main() {
    is >> n >> m >> need;
    FOR(i, 1, m) {
        is >> e[i].u >> e[i].v >> e[i].w >> e[i].c;
        ++e[i].u, ++e[i].v;
        if (!e[i].c) swap(e[cntw++], e[i]);
    }
    sort(e + 1, e + cntw), sort(e + cntw, e + m + 1);
    int l = -100, r = 101, ans = 0;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        FOR(i, 1, n) fa[i] = i;
        int chosen = 0, val = 0;
        int i = 1, j = cntw;
        while (i < cntw && j <= m) {
            if (e[i].w + mid <= e[j].w) {
                if (add(i)) val += e[i].w + mid, ++chosen;
                ++i;
            } else val += e[j].w * add(j), ++j;
        }
        for (; i < cntw; ++i) if (add(i)) val += (e[i].w + mid), ++chosen;
        for (; j <= m; ++j) val += add(j) * e[j].w;
        if (chosen >= need) ans = val - mid * need, l = mid;
        else r = mid;
    }
    os << ans << '\n';
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}