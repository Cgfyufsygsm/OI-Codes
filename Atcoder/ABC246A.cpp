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

pair<int, int> p[5];

int main() {
    FOR(i, 1, 3) cin >> p[i].first >> p[i].second;
    sort(p + 1, p + 4);
    if (p[1].first == p[2].first) {
        if (p[3].second == p[1].second) cout << p[3].first << ' ' << p[2].second << endl;
        else cout << p[3].first << ' ' << p[1].second << endl;
    } else {
        if (p[1].second == p[2].second) cout << p[1].first << ' ' << p[3].second << endl;
        else cout << p[1].first << ' ' << p[2].second << endl;
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}