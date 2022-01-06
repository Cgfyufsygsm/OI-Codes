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

const int maxn = 1e4 + 5;
int n, vis[maxn], ans[maxn];

int ask(int i) {
    cout << "? " << i << endl;
    int x; cin >> x;
    return x;
}

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        FOR(i, 1, n) vis[i] = 0;
        FOR(i, 1, n) {
            if (vis[i]) continue;
            vector<int> vec;
            int st = ask(i);
            vec.push_back(st);
            int u;
            do {
                u = ask(i);
                vec.push_back(u);
            } while (u != st);
            FOR(j, 0, (int)vec.size() - 2) {
                ans[vec[j]] = vec[j + 1];
                vis[vec[j]] = 1;
            }
        }
        cout << "! ";
        FOR(i, 1, n) cout << ans[i] << ' ';
        cout << endl;
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}