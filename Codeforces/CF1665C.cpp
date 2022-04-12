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

void process(vector<int> &vec, int &ans) {
    if (vec.empty()) return;
    int n = vec.size();
    int las = 0;
    FOR(i, 0, n - 1) {
        if (vec[i] == vec[0]) las = i;
        else break;
    }
    --vec[las], ++ans;
    FOR(i, 0, n - 1) --vec[i];
    while (!vec.empty() && vec.back() <= 0) vec.pop_back();
    return process(vec, ans);
}

int main() {
    int T; cin >> T;
    while (T--) {
        vector<int> vec;
        int n, ans = 0; cin >> n, vec.resize(n + 1);
        FOR(i, 2, n) {
            int x; cin >> x;
            ++vec[x];
        }
        vec.emplace_back(1);
        sort(vec.rbegin(), vec.rend());
        while (!vec.back()) vec.pop_back();
        n = vec.size();
        FOR(i, 0, n - 1) {
            vec[i] = vec[i] - (n - i);
            ++ans;
        }
        sort(vec.rbegin(), vec.rend());
        while (!vec.empty() && vec.back() <= 0) vec.pop_back();
        process(vec, ans);
        cout << ans << endl;
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}