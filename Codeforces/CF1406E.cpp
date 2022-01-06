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
template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 1e5 + 5;
int vis[maxn], p[maxn], tot, n;

int ask(int a, char c) {
    cout << c << ' ' << a << endl << flush;
    int x; cin >> x;
    return x;
}

int main() {
    cin >> n;
    FOR(i, 2, n) {
        if (!vis[i]) p[++tot] = i;
        for (int j = 1; i * p[j] <= n; ++j) {
            vis[i * p[j]] = 1;
            if (i % p[j] == 0) break;
        }
    }
    int B = (int)ceil(sqrt(1e5)), ans = 1, i;
    for (i = 1; i <= tot && p[i] <= B; ++i) {
        ask(p[i], 'B');
        int tmp = p[i], flag = ask(p[i], 'A');
        while (flag && (tmp *= p[i]) <= n) flag = ask(tmp, 'A');
        ans *= tmp / p[i];
    }
    for (i; i <= tot; i += 98) {
        int cnt0 = ask(1, 'A'), r = min(i + 97, tot);
        FOR(j, i, r) cnt0 -= ask(p[j], 'B');
        int cnt1 = ask(1, 'A');
        if (cnt0 != cnt1) {
            FOR(j, i, r) {
                if (ask(p[j], 'A')) {
                    ans *= p[j];
                    break;
                }
            }
            break;
        }
    }
    cout << "C " << ans << endl << flush;
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}