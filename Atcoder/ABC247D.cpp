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

using ll = long long;
deque<pair<int, ll>> q;

int main() {
    int n; cin >> n;
    while (n--) {
        int op, x, c; cin >> op;
        if (op == 1) {
            cin >> x >> c;
            q.push_back({c, x});
        } else {
            cin >> c;
            int cnt = 0; ll sum = 0;
            while (cnt < c) {
                auto now = q.front(); q.pop_front();
                int delta = min(now.first, c - cnt);
                cnt += delta, sum += delta * now.second;
                if (delta != now.first) q.push_front({now.first - delta, now.second});
            }
            cout << sum << endl;
        }
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}