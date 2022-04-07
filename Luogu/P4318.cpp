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

using ll = long long;
const int maxn = 1e5 + 5, N = 1e5;
int vis[maxn], p[maxn], tot, mu[maxn];
ll n;

void sieve() {
    mu[1] = 1;
    FOR(i, 2, N) {
        if (!vis[i]) p[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && i * p[j] <= N; ++j) {
            vis[i * p[j]] = 1;
            if (!(i % p[j])) break;
            mu[i * p[j]] = -mu[i];
        }
    }
    return;
}

ll calc(ll n) {
    ll ret = 0;
    for (ll i = 1; i * i <= n; ++i) ret += mu[i] * (n / (i * i));
    return ret;
}

int main() {
    sieve();
    int T; cin >> T;
    while (T--) {
        cin >> n;
        ll l = 1, r = 1e10, ans;
        while (l <= r) {
            ll mid = (l + r) >> 1;
            //printf("%d %d\n", l, r);
            if (calc(mid) >= n) r = mid - 1, ans = mid;
            else l = mid + 1;
        }
        cout << ans << endl;
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}