#include <bits/stdc++.h>
#include <atcoder/modint>
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

using mint = atcoder::modint998244353;

mint qPow(mint base, int exp) {
    mint ret = 1;
    for (; exp; exp >>= 1, base *= base)
        if (exp & 1) ret *= base;
    return ret;
}

bitset<26> S[18];
int n, l;

int main() {
    cin >> n >> l;
    FOR(i, 0, n - 1) {
        string s; cin >> s;
        for (const auto &c : s) S[i].set(c - 'a');
    }
    bitset<26> now;
    mint ans = 0;
    FOR(i, 1, (1 << n) - 1) {
        now.set();
        int cnt = 0;
        FOR(j, 0, n - 1) if ((1 << j) & i) now &= S[j], ++cnt;
        ans += ((cnt & 1) ? 1 : -1) * qPow(now.count(), l);
    }
    cout << ans.val() << endl;
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}