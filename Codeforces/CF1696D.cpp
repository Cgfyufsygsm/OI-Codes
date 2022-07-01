#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 2.5e5 + 5, LG = 19;
int n, a[maxn], mx[LG][maxn], mn[LG][maxn], lg[maxn];

int queryMn(int l, int r) {
    int &s = lg[r - l + 1];
    return min(mn[s][l], mn[s][r - (1 << s) + 1]);
}

int queryMx(int l, int r) {
    int &s = lg[r - l + 1];
    return max(mx[s][l], mx[s][r - (1 << s) + 1]);
}

bool check(int l, int r) {
    int x = queryMn(l, r), y = queryMx(l, r);
    return min(a[l], a[r]) == x && max(a[l], a[r]) == y;
}

int to(int now) {
    // 钦定 a[now] = min
    int l, r, ret, ans = 0;
    l = now + 1, r = n, ret = now;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (queryMn(now, mid) == a[now]) ret = mid, l = mid + 1;
        else r = mid - 1;
    }
    if (ret != now) {
        int mxv = queryMx(now, ret);
        l = now + 1, r = ret, ret = now + 1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (mxv == queryMx(now, mid)) ret = mid, r = mid - 1;
            else l = mid + 1;
        }
        ans = max(ans, ret);
    }
    l = now + 1, r = n, ret = now;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (queryMx(now, mid) == a[now]) ret = mid, l = mid + 1;
        else r = mid - 1;
    }
    if (ret != now) {
        int mnv = queryMn(now, ret);
        l = now + 1, r = ret, ret = now + 1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (queryMn(now, mid) == mnv) r = mid - 1, ret = mid;
            else l = mid + 1;
        }
        ans = max(ans, ret);
    }
    return ans;
}

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        FOR(i, 1, n) cin >> a[i], mx[0][i] = mn[0][i] = a[i];
        lg[1] = 0; lg[0] = -1;
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;//造log
        for (int j = 1; j < LG; j++)
            for (int i = 1; i + (1 << j) - 1 <= n; i++)
                mx[j][i] = max(mx[j - 1][i], mx[j - 1][i + (1 << (j - 1))]),
                mn[j][i] = min(mn[j - 1][i], mn[j - 1][i + (1 << (j - 1))]);
        int now = 1, ans = 0;
        while (now != n)
            now = to(now), ++ans;
        cout << ans << '\n';
    }
    return 0;
}