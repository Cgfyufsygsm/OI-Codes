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
int a[maxn], n, tag;
deque<int> q;

void delZero(deque<int> &q) {
    while (!q.empty() && ((q.back() ^ tag) == 0)) q.pop_back();
    return;
}

int main() {
    cin >> n;
    FOR(i, 1, n) cin >> a[i], q.push_back(a[i]);
    while (true) {
        delZero(q);
        if (q.empty()) break;
        if (q.front() ^ tag) return puts("No"), 0;
        else {
            q.pop_front(), tag ^= 1;
        }
    }
    return puts("Yes"), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}