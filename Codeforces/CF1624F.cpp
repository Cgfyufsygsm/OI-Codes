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

int add(int x) {
    cout << "+ " << x << endl;
    int res; cin >> res;
    return res;
}

int main() {
    int n; cin >> n;
    int l = 1, r = n;
    while (l < r - 1) {
        int mid = (l + r) >> 1;
        int a = n - mid % n;
        int res = add(a);
        l += a, r += a, mid += a;
        if (res == l / n) r = mid;
        else l = mid; 
    }
    cout << "! " << l << endl;
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}