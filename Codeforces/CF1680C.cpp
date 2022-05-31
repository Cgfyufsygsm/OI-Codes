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
int n, sum[2][maxn];

bool check(int mid) {
    int l = 1, r = 0, l0 = 0, r1 = sum[1][n];
    for (; r <= n; ++r, s[r] == '1' ? --r1 : ++l0) {
        if (max(l0, r1) <= mid) return 1;
        while (l <= r && l0 > mid) ++l, s[l - 1] == '1' ? ++r1 : --l0;
    }
    return 0;
}

int main() {
    freopen("data.in", "r", stdin);
    int T; cin >> T;
    while (T--) {
        cin >> s + 1;
        n = strlen(s + 1);
        FOR(k, 0, 1) FOR(i, 1, n) sum[k][i] = sum[k][i - 1] + (s[i] == k + '0');
        int l = 0, r = n, ans;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (check(mid)) r = mid, ans = mid;
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