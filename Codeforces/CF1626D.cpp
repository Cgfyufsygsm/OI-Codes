#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
using namespace std;
const int maxn = 2e5 + 5;
int n, a[maxn], buc[maxn], pre[maxn];

il int toUp(int x) {return x ? 1 << (31 - __builtin_clz(x) + (__builtin_popcount(x) > 1)) : 1;}
template<typename T> il T chkmin(T &a, const T &b) {return a = (b < a ? b : a);}

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        FOR(i, 1, n) buc[i] = 0, pre[i] = 0;
        FOR(i, 1, n) {
            int x; cin >> x;
            ++buc[x], pre[x] = x;
        }
        FOR(i, 1, n) {
            buc[i] += buc[i - 1];
            if (!pre[i]) pre[i] = pre[i - 1];
        }
        int ans = 1e9;
        FOR(x, 0, n) {
            int tmp = toUp(buc[x]);
            int i = 0;
            do {
                if (i) i <<= 1;
                else i = 1;
                int l = x + 1, r = n, y = -1;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (buc[mid] - buc[x] <= i) y = mid, l = mid + 1;
                    else r = mid - 1;
                }
                if (y == -1) continue;
                chkmin(ans, tmp + i + toUp(buc[n] - buc[y]) - n);
            } while (buc[x] + i <= n);
        }
        cout << ans << '\n';
    }
    return 0;
}