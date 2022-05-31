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

const int maxn = 6;
char s[maxn][maxn];
int n, m;

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n >> m;
        FOR(i, 1, n) cin >> s[i] + 1;
        int minr = 0, col;
        FOR(i, 1, n) {
            FOR(j, 1, m) {
                if (s[i][j] == 'R') {
                    minr = i, col = j;
                    break;
                }
            }
            if (minr) break;
        }
        bool flg = 1;
        FOR(i, minr + 1, n) FOR(j, 1, m) if (s[i][j] == 'R' && j < col) flg = 0;
        cout << (flg ? "YES" : "NO") << endl;
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}