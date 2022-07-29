#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

template<typename T> il T chkmin(T &a, const T &b) {return a = (b < a ? b : a);}
using namespace std;
using namespace YangTY::fastIO;
const int maxn = 2e5 + 5;
int n, m1, m2, c1, c2, p, a[maxn];

int f(int x) {
    int ret = x * p;
    deque<pair<int, int>> qs, qn, qf;
    FOR(i, 1, n) {
        while (!qn.empty() && qn.front().first <= i - m1)
            qf.emplace_back(qn.front()), qn.pop_front();
        while (!qf.empty() && qf.front().first <= i - m2)
            qs.emplace_back(qf.front()), qf.pop_front();
        int need = a[i], mn = min(need, x);
        need -= mn, x -= mn;
        while (need && !qs.empty()) {
            mn = min(need, qs.back().second);
            ret += mn * c2, need -= mn;
            if (mn == qs.back().second) qs.pop_back();
            else qs.back().second -= mn;
        }
        while (need && !qf.empty()) {
            mn = min(need, qf.back().second);
            ret += mn * c1, need -= mn;
            if (mn == qf.back().second) qf.pop_back();
            else qf.back().second -= mn;
        }
        if (need) return 2e9;
        qn.emplace_back(i, a[i]);
    }
    return ret;
}

int main() {
    is >> n >> m1 >> m2 >> c1 >> c2 >> p;
    if (m1 > m2) swap(m1, m2), swap(c1, c2);
    if (c1 < c2) c2 = c1, m2 = m1;
    int l = 0, r = 1, ans = 2e9;
    FOR(i, 1, n) is >> a[i], r += a[i];
    while (l + 2 < r) {
        int k = (r - l) / 3;
        int mid1 = l + k, mid2 = r - k;
        f(mid1) < f(mid2) ? r = mid2 : l = mid1;
    }
    FOR(i, l, r) chkmin(ans, f(i));
    os << ans << '\n';
    return 0;
}