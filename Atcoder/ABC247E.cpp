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
const int maxn = 2e5 + 5;
int a[maxn], x, y, n, mn[19][maxn], mx[19][maxn], lg[maxn];

int queryMx(int l, int r) {
    int s = lg[r - l + 1];
    return max(mx[s][l], mx[s][r - (1 << s) + 1]);
}

int queryMn(int l, int r) {
    int s = lg[r - l + 1];
    return min(mn[s][l], mn[s][r - (1 << s) + 1]);
}

int main() {
    cin >> n >> x >> y;
    lg[0] = -1;
    FOR(i, 1, n) cin >> a[i], mn[0][i] = a[i], mx[0][i] = a[i], lg[i] = lg[i >> 1] + 1;
    FOR(j, 1, 18) {
        FOR(i, 1, n - (1 << j) + 1) {
            mn[j][i] = min(mn[j - 1][i], mn[j - 1][i + (1 << (j - 1))]);
            mx[j][i] = max(mx[j - 1][i], mx[j - 1][i + (1 << (j - 1))]);
        }
    }
    ll ans = 0;
    FOR(l0, 1, n) {
        if (a[l0] < y || a[l0] > x) continue;
        // x 是最大，y 是最小
        int r0mx = -1, r1mx = n + 1, r0mn = -1, r1mn = n + 1;
        // r0mx 是第一个 x，r1mx 是第一个大于 x
        int l, r;
        for (l = l0, r = n + 1; l < r;) {
            int mid = (l + r) >> 1;
            int res = queryMx(l0, mid);
            if (res == x) r0mx = mid;
            if (res >= x) r = mid;
            else l = mid + 1;
        }
        for (l = l0, r = n + 1; l < r;) {
            int mid = (l + r) >> 1;
            int res = queryMx(l0, mid);
            if (res > x) r1mx = mid, r = mid;
            else l = mid + 1;
        }
        for (l = l0, r = n + 1; l < r;) {
            int mid = (l + r) >> 1;
            int res = queryMn(l0, mid);
            if (res == y) r0mn = mid;
            if (res <= y) r = mid;
            else l = mid + 1;
        }
        for (l = l0, r = n + 1; l < r;) {
            int mid = (l + r) >> 1;
            int res = queryMn(l0, mid);
            if (res < y) r1mn = mid, r = mid;
            else l = mid + 1;
        }
        if (r0mx == -1 || r0mn == -1) continue;
        l = max(r0mx, r0mn), r = min(r1mx, r1mn);
        if (l > r) continue;
        ans += r - l;
    }
    cout << ans << endl;
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}