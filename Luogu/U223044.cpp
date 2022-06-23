#include <bits/stdc++.h>
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

const int maxn = 32768 | 5, mod = 999292927;
using ll = long long;
struct Edge {
    int u, v; ll w;
} e[maxn];
int n, m, fa[maxn], col[maxn];

int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}

int main() {
    cin >> n >> m;
    if (m < n - 1) return puts("ERROR"), 0;
    FOR(i, 1, n) fa[i] = i;
    int tot = n;
    FOR(i, 1, m) {
        cin >> e[i].u >> e[i].v >> e[i].w;
        int x = find(e[i].u), y = find(e[i].v);
        if (x != y) fa[x] = y, --tot;
    }
    sort(e + 1, e + m + 1, [](const Edge &a, const Edge &b) {return a.w < b.w;});
    int cnt = 0;
    FOR(i, 1, n) if (find(i) == i) {
        col[i] = ++cnt;
    }
    FOR(i, 1, n) col[i] = col[find(i)];
    FOR(i, 1, n) fa[i] = i;
    multiset<int> S;
    ll ans = 0;
    FOR(i, 1, m) {
        int x = find(e[i].u), y = find(e[i].v);
        if (x == y) S.insert(e[i].w);
        else ans += e[i].w, fa[x] = y;
    }
    FOR(i, 1, tot - 1) ans += *S.begin(), S.erase(S.begin());
    cout << tot - 1 << ' ' << m - n + 1 << ' ' << (ans % mod + mod) % mod << endl;
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}