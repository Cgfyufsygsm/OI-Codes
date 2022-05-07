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

const int maxn = 2e5 + 5;
char s[maxn];
int cnt[26], n;

bool check() {
    if (n == 1) return true;
    int period = n;
    FOR(i, 2, n) if (s[i] == s[1]) {
        period = i - 1;
        break;
    }
    memset(cnt, 0, sizeof cnt);
    FOR(i, 1, period) {
        cnt[s[i] - 'a']++;
        if (cnt[s[i] - 'a'] > 1) return false;
    }
    if (period == n) return true;
    FOR(i, period + 1, n) if (s[i] != s[i - period]) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> s + 1;
        n = strlen(s + 1);
        puts(check() ? "YES" : "NO");
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}