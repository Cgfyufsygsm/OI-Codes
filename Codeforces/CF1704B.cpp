#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

template<typename T> il T chkmax(T &a, const T &b) {return a = (b > a ? b : a);}
template<typename T> il T chkmin(T &a, const T &b) {return a = (b < a ? b : a);}

const int maxn = 2e5 + 5;
int n, a[maxn], x;

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> n >> x;
        FOR(i, 1, n) cin >> a[i];
        int minv = a[1], maxv = a[1], ans = 0;
        FOR(i, 2, n) {
            chkmin(minv, a[i]), chkmax(maxv, a[i]);
            if (maxv - minv > 2 * x) {
                ++ans;
                maxv = minv = a[i];
            }
        }
        cout << ans << '\n';
    }
    return 0;
}