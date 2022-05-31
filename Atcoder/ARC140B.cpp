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
int n;

multiset<int> S;

int main() {
    cin >> n;
    cin >> (s + 1);
    FOR(mid, 1, n) if (s[mid] == 'R') {
        int cnt = 0;
        while (s[mid - cnt - 1] == 'A' && s[mid + cnt + 1] == 'C') ++cnt;
        if (cnt) S.insert(cnt);
    }
    int ans = 0;
    while (!S.empty()) {
        int val = *S.rbegin();
        S.erase(prev(S.end()));
        ++ans, --val;
        if (val) S.insert(val);
        if (!S.empty()) {
            ++ans;
            S.erase(S.begin());
        }
    }
    cout << ans << endl;
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}