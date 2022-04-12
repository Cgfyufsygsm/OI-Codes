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

vector<int> S[18];
bool vis[18];

void print(vector<int> &v) {
    for (auto &x : v) cout << x << ' ';
    return;
}

void print(int n) {
    if (vis[n]) return print(S[n]);
    if (n == 1) {
        S[1].push_back(1);
        vis[1] = 1;
        return print(S[1]);
    }
    print(n - 1), cout << n << ' ', print(n - 1);
    vis[n] = 1;
    S[n] = S[n - 1];
    S[n].push_back(n);
    for (auto &x : S[n - 1]) S[n].push_back(x);
    return;
}

int main() {
    int n; cin >> n;
    print(n);
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}