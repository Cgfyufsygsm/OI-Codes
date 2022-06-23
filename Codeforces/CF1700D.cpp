#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int maxn = 2e5 + 5;
using ll = long long;
using namespace std;
int n, q;
ll v[maxn], pre[maxn], suf[maxn], maxv;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    FOR(i, 1, n) cin >> v[i], maxv = max(maxv, v[i]), pre[i] = v[i] + pre[i - 1];
    DEC(i, n, 1) suf[i] = v[i] + suf[i + 1];
    cin >> q;
    int ddl = maxv, l = 1, r = maxv;
    while (l <= r) {
        int mid = (l + r) >> 1;
        ll tmp = 0; bool flg = 1;
        FOR(i, 1, n) {
            if (tmp + mid < v[i]) flg = 0;
            tmp = tmp + mid - v[i];
        }
        if (flg) ddl = mid, r = mid - 1;
        else l = mid + 1;
    }
    while (q--) {
        int x; cin >> x;
        if (x < ddl) {
            cout << "-1\n";
            continue;
        }
        int l = 1, r = n, ans = -1;
        while (l <= r) {
            ll mid = (l + r) >> 1;
            if (mid * x - pre[mid] >= suf[mid + 1]) ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        cout << ans << '\n';
    }
    return 0;
}