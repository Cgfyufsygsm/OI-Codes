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

constexpr int maxn = 1e6 + 5;
constexpr int base = 37;
constexpr int mod[2] = {998244353, (int)1e9 + 7};

int n, pw[2][maxn], sum[2][maxn], ans[maxn];
char s[maxn];

void hash(const int& k) {
    int *sum = YangTY::sum[k], *pw = YangTY::pw[k];
    const int mod = YangTY::mod[k];
    pw[0] = 1;
    FOR(i, 1, n) {
        pw[i] = 1ll * pw[i - 1] * base % mod;
        sum[i] = (1ll * sum[i - 1] * base % mod + s[i] - 'a' + 1) % mod;
    }
    return;
}

il int getHash(int l, int r, int k) {
    int *sum = YangTY::sum[k], *pw = YangTY::pw[k];
    const int mod = YangTY::mod[k];
    return (sum[r] - 1ll * sum[l - 1] * pw[r - l + 1] % mod + mod) % mod;
}

il bool check(int l1, int r1, int l2, int r2) {
    return getHash(l1, r1, 0) == getHash(l2, r2, 0) && getHash(l1, r1, 1) == getHash(l2, r2, 1);
}

int main() {
    cin >> n >> s + 1;
    hash(0), hash(1);
    int cnt = (n + 1) >> 1, l, r;
    if (n & 1) ans[cnt] = -1, l = r = cnt;
    else {
        l = n >> 1, r = l + 1;
        if (s[l] == s[r]) ans[cnt] = 1;
        else ans[cnt] = -1;
    }
    DEC(i, cnt - 1, 1) {
        --l, ++r;
        for (int j = ans[i + 1] + 2; j >= -1; j -= 2) {
            if (check(l, l + j - 1, r - j + 1, r) || j == -1) {
                ans[i] = j;
                break;
            }
        }
    }
    FOR(i, 1, cnt) cout << ans[i] << ' ';
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}