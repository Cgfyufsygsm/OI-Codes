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

const int maxn = 1e6 + 5;
int a[maxn], bl[maxn], tag[maxn], block, n, m;
vector<int> val[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    block = sqrt(n * log2(n));
    FOR(i, 1, n) cin >> a[i], bl[i] = (i - 1) / block + 1;
    auto rebuild = [](int id) {
        vector<int>().swap(val[id]);
        FOR(i, (id - 1) * block + 1, min(id * block, n)) val[id].push_back(a[i]);
        sort(val[id].begin(), val[id].end());
    };
    FOR(i, 1, bl[n]) rebuild(i);
    while (m--) {
        char op; int l, r, w;
        cin >> op >> l >> r >> w;
        if (op == 'M') {
            FOR(i, l, min(r, bl[l] * block)) a[i] += w;
            rebuild(bl[l]);
            if (bl[l] != bl[r]) {
                FOR(i, (bl[r] - 1) * block + 1, r) a[i] += w;
                rebuild(bl[r]);
            }
            FOR(i, bl[l] + 1, bl[r] - 1) tag[i] += w;
        } else {
            int ans = 0;
            FOR(i, l, min(r, bl[l] * block)) ans += ((a[i] + tag[bl[l]]) >= w);
            if (bl[l] != bl[r]) FOR(i, (bl[r] - 1) * block + 1, r) ans += ((a[i] + tag[bl[r]]) >= w);
            FOR(i, bl[l] + 1, bl[r] - 1) ans += val[i].end() - lower_bound(val[i].begin(), val[i].end(), w - tag[i]);
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