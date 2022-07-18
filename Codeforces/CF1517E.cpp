#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using namespace YangTY::fastIO;
const int maxn = 2e5 + 5, mod = 998244353;
using ll = long long;
int n, ans;
ll a[maxn], sum[maxn], sum2[maxn];

template<class T1, class T2> il void add(T1 &x, const T2 &y) {
    (x += y) >= mod ? x -= mod : (0-0);
}

void solve(int t1, int t2) {
    ll p = 0, c = 0;
    if (t1) p += a[1];
    if (t2) c += a[n];
    FOR(i, 1 + t1, n - 1 - t2) {
        c += a[i];
        int l = 0, r = (n - i - 1 - t2) / 2 + 1, res = -1;
        while (l < r) {
            int mid = (l + r) >> 1, len = mid << 1;
            if (c + sum2[i + len] - sum2[i] < p + sum[n - t2] - sum[i + len] + sum2[i + len - 1] - sum2[i - 1])
                res = mid, l = mid + 1;
            else r = mid;
        }
        add(ans, res + 1);
    }
    return;
}

int main() {
    int T; is >> T;
    while (T--) {
        is >> n, ans = 0;
        FOR(i, 1, n) is >> a[i], sum[i] = a[i] + sum[i - 1], sum2[i] = sum2[max(i - 2, 0)] + a[i];
        FOR(i, 1, n) if (sum[i] * 2 > sum[n]) ++ans;
        FOR(i, 0, 1) FOR(j, 0, 1) solve(i, j);
        os << ans << '\n';
    }
    return 0;
}