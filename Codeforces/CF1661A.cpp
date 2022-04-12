#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
template<typename T> il T chkmin(T &a, const T &b) {return a = (b < a ? b : a);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}

const int maxn = 30;
using ll = long long;
ll a[maxn][2], f[maxn][2], n;

ll calc(int i, int j, int k) {
    ll ret = 0;
    if (j != k) ret += myabs(a[i - 1][0] - a[i][1]) + myabs(a[i - 1][1] - a[i][0]);
    else ret += myabs(a[i - 1][0] - a[i][0]) + myabs(a[i - 1][1] - a[i][1]);
    return ret;
}

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        FOR(i, 1, n) cin >> a[i][0];
        FOR(i, 1, n) cin >> a[i][1];
        memset(f, 0x3f, sizeof f);
        f[1][0] = f[1][1] = 0;
        FOR(i, 2, n) FOR(j, 0, 1) FOR(k, 0, 1) {
            chkmin(f[i][j], f[i - 1][k] + calc(i, j, k));
        }
        cout << min(f[n][0], f[n][1]) << endl;
    }
    return 0;
}