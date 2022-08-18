#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

const int maxn = 1e5 + 5;
int n, k, a[maxn], a0[maxn], cnt[maxn], tota;

bool check(int mid) {
    int tmp = cnt[lower_bound(a0 + 1, a0 + tota + 1, (mid + 1) >> 1) - a0 - 1];
    int cur = 1e9;
    FOR(i, 2, n) {
        auto f = [&](int x) ->bool {return x < mid && x >= (mid + 1) / 2;};
        cur = min(cur, f(a[i]) + f(a[i - 1]));
    }
    return cur + tmp <= k;
}

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n >> k;
        FOR(i, 1, n) cin >> a[i], a0[i] = a[i], cnt[i] = 0;
        sort(a0 + 1, a0 + n + 1);
        tota = unique(a0 + 1, a0 + n + 1) - a0 - 1;
        FOR(i, 1, n) ++cnt[lower_bound(a0 + 1, a0 + tota + 1, a[i]) - a0];
        FOR(i, 1, n) cnt[i] += cnt[i - 1];
        int l = 1, r = 1e9, ans;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) l = mid + 1, ans = mid;
            else r = mid - 1;
        }
        cout << ans << '\n';
    }
    return 0;
}