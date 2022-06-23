#include <bits/stdc++.h>
#include <poly.hpp>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define VEC(i, v) for (int i = 0; i < (int)v.size(); ++i)
#define il inline
#define clr(f, n) memset(f, 0, (sizeof(int)) * (n))
#define cpy(f, g, n) memcpy(f, g, (sizeof(int)) * (n))
#define szof(a) ((int) (a).size())

using namespace std;

namespace YangTY {

template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

using ll = long long;
using ull = unsigned long long;
using poly = polynomial::Poly<998244353>;
const int mod = 998244353;
int n, d;

il void work(poly &f, poly g) {
    f = f * g;
    FOR(i, d, szof(f) - 1) f[i % d] = (f[i % d] + f[i]) % mod;
    f.resize(d);
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> d;
    poly f;
    f.push_back(1), f.push_back(1);
    poly ans(1, 1);
    for (; n; n >>= 1, work(f, f))
        if (n & 1) work(ans, f);
    ans.resize(d);
    FOR(i, 0, d - 1) cout << ans[i] << ' ';
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}